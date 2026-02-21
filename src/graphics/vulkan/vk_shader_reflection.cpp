#include "graphics/vulkan/vk_shader_reflection.hpp"
#include "core/log.hpp"
#include "graphics/vulkan/convert_enum_vk.hpp"
#include <glm/common.hpp>
#include <shaderc/shaderc.h>
#include <spirv_cross.hpp>
//#include <spirv_reflect.hpp>

BF_BEGIN_NAMESPACE
BF_BEGIN_VK_NAMESPACE

ShaderReflectionData GetShaderReflection(Shader::Type type, const uint32_t *spirv, size_t word_count)
{
	std::vector<Descriptor2> descriptors;
	std::vector<Constant> constants;

	spirv_cross::Compiler compiler(spirv, word_count);
	spirv_cross::ShaderResources resources = compiler.get_shader_resources();

	//Log() << "------------------------------------------";
	uint32_t max_set = 0;

	for (auto &resource: resources.uniform_buffers)
	{
		uint32_t set = compiler.get_decoration(resource.id, spirv_cross::DecorationDescriptorSet);
		uint32_t binding = compiler.get_decoration(resource.id, spirv_cross::DecorationBinding);
		descriptors.emplace_back(set, binding, Descriptor2::Type::UNIFORM_BUFFER, 1);
		max_set = glm::max(max_set, set);
		//Log() << "Uniform buffer" << set << binding;
	}

	for (auto &resource: resources.storage_buffers)
	{
		uint32_t set = compiler.get_decoration(resource.id, spirv_cross::DecorationDescriptorSet);
		uint32_t binding = compiler.get_decoration(resource.id, spirv_cross::DecorationBinding);
		descriptors.emplace_back(set, binding, Descriptor2::Type::STORAGE_BUFFER, 1);
		max_set = glm::max(max_set, set);
		//Log() << "Storage buffer" << set << binding;
	}

	for (auto &resource: resources.sampled_images)
	{
		uint32_t array_size = 1;
		uint32_t set = compiler.get_decoration(resource.id, spirv_cross::DecorationDescriptorSet);
		uint32_t binding = compiler.get_decoration(resource.id, spirv_cross::DecorationBinding);

		const spirv_cross::SPIRType &type = compiler.get_type(resource.type_id);
		if (!type.array.empty())
			array_size = type.array[0];

		descriptors.emplace_back(set, binding, Descriptor2::Type::TEXTURE, array_size);
		max_set = glm::max(max_set, set);

		//Log() << "Texture" << set << binding << array_size;
	}

	for (auto &resource: resources.push_constant_buffers)
	{
		for (auto &range: compiler.get_active_buffer_ranges(resource.id))
		{
			constants.emplace_back(range.offset, range.range, Constant::Type::INT);
		}

		/*spirv_cross::SPIRType type = compiler.get_type(resource.base_type_id);
		//Log() << "Push constant buffer" << compiler.get_declared_struct_size(compiler.get_type(resource.base_type_id));

		//constants.emplace_back(0, compiler.get_declared_struct_size(type), Constant::Type::INT);
		//continue;

		for (uint32_t i = 0; i < type.member_types.size(); ++i)
		{
			//const spirv_cross::SPIRType &member_type = compiler.get_type(type.member_types[i]);
			uint32_t offset = compiler.get_member_decoration(type.self, i, spirv_cross::DecorationOffset);
			Constant::Type type = Constant::Type::INT;
			constants.emplace_back(offset, sizeof(int), type);

			//Log() << compiler.get_member_name(type.self, i)
			//	  << compiler.get_member_decoration(type.self, i, spirv_cross::DecorationOffset)
			//	  << member_type.basetype << member_type.vecsize;
		}*/
	}

	return { std::move(descriptors), std::move(constants), max_set, type };
}

std::vector<uint32_t> CompileShader(const std::string &name, const std::vector<char> &source)
{
	shaderc_compiler_t compiler = shaderc_compiler_initialize();
	shaderc_compile_options_t options = shaderc_compile_options_initialize();

	//shaderc_compile_options_set_optimization_level(options, shaderc_optimization_level_performance);
	shaderc_compile_options_set_target_env(options, shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_4);
	shaderc_compilation_result_t compilation_result = shaderc_compile_into_spv(compiler, source.data(), source.size(),
													shaderc_glsl_infer_from_source, name.c_str(), "main", options);

	if (shaderc_result_get_compilation_status(compilation_result) != shaderc_compilation_status_success)
	{
		Error() << shaderc_result_get_compilation_status(compilation_result)
				<< shaderc_result_get_error_message(compilation_result);
		return {};
	}

	const char *data_pointer = shaderc_result_get_bytes(compilation_result);
	size_t data_size = shaderc_result_get_length(compilation_result);
	std::vector<uint32_t> binary(data_size / sizeof(uint32_t));
	memcpy(binary.data(), data_pointer, data_size);
	//std::vector<uint32_t> binary(data_pointer, data_pointer + (data_size / sizeof(uint32_t)));

	shaderc_result_release(compilation_result);
	shaderc_compile_options_release(options);
	shaderc_compiler_release(compiler);

	return binary;
}

uint32_t hash(size_t seed, uint32_t x)
{
	x = ((x >> 16) ^ x) * 0x45d9f3bu;
	x = ((x >> 16) ^ x) * 0x45d9f3bu;
	x = (x >> 16) ^ x;
	seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	return seed;
}

VkPipelineLayout CreatePipelineLayout(VkDevice device,
									  const std::vector<ShaderReflectionData *> &reflection_data,
									  std::vector<VkDescriptorSetLayout> &decriptor_set_layouts,
									  VkPipelineLayoutCreateFlags flags)
{
	std::map<uint32_t, std::vector<VkDescriptorSetLayoutBinding>> bindings;
	std::map<uint32_t, uint32_t> hashes;
	std::vector<VkPushConstantRange> push_constant_ranges;
	//std::vector<VkDescriptorSetLayout> decriptor_set_layouts;

	//for (uint32_t i = 0; i < reflection_data.max_set; i++)
	//	bindings[i] = {};

	for (const ShaderReflectionData *data: reflection_data)
	{
		for (uint32_t i = 0; i < data->max_set; i++)
		{
			bindings[i] = {};
			hashes[i] = data->decriptors.size();
		}
	}

	for (const ShaderReflectionData *data: reflection_data)
	{
		for (auto &desc: data->decriptors)
		{
			VkDescriptorSetLayoutBinding binding
			{
				.binding = desc.binding,
				.descriptorType = vk::ConvertEnum(desc.type),
				.descriptorCount = desc.array_size,
				.stageFlags = vk::ConvertEnum(data->type),
				.pImmutableSamplers = nullptr,
			};

			bool found = false;
			for (auto &temp: bindings[desc.set])
			{
				if (temp.binding == binding.binding
						&& temp.descriptorType == binding.descriptorType
						&& temp.descriptorCount == binding.descriptorCount)
				{
					temp.stageFlags |= vk::ConvertEnum(data->type);
					found = true;
				}
			}

			if (!found)
				bindings[desc.set].push_back(binding);
			/*hashes[desc.set] = hash(hashes[desc.set], binding.binding);
			hashes[desc.set] = hash(hashes[desc.set], binding.descriptorType);
			hashes[desc.set] = hash(hashes[desc.set], binding.descriptorCount);
			hashes[desc.set] = hash(hashes[desc.set], binding.stageFlags);*/

			/*flat_descriptors_info.push_back(uint8_t(desc.type));
			flat_descriptors_info.push_back(uint8_t(desc.set));
			flat_descriptors_info.push_back(uint8_t(desc.binding));

			Log() << names_map[desc.type] << desc.set << desc.binding;*/
		}

		for (auto &desc: data->constants)
		{
			VkPushConstantRange push_constant_range
			{
				.stageFlags = vk::ConvertEnum(data->type),
				.offset = desc.offset,
				.size = desc.size, //const_sizes_map[desc.type],
			};

			//Log() << int(shader.type) << desc.offset << desc.size;

			push_constant_ranges.push_back(push_constant_range);
		}
	}

	/*std::vector<uint8_t> flat_descriptors_info;
	for (auto &set: bindings)
	{
		//Log() << set.first;
	}*/

	//std::vector<VkDescriptorSetLayout> layouts;
	for (auto &set: bindings)
	{
		std::vector<VkDescriptorBindingFlags> flags(set.second.size());
		for (uint32_t i = 0; i < set.second.size(); i++)
			flags[i] = (set.second.at(i).descriptorCount > 1) ? VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT : 0;

		VkDescriptorSetLayoutBindingFlagsCreateInfo flags_ci
		{
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO,
			.pNext = nullptr,
			.bindingCount = uint32_t(flags.size()),
			.pBindingFlags = flags.data(),
		};

		VkDescriptorSetLayoutCreateInfo descriptor_set_layout_ci
		{
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
			.pNext = &flags_ci,
			.flags = 0,
			.bindingCount = uint32_t(set.second.size()),
			.pBindings = set.second.data(),
		};

		/*Log() << "--------------------------";
		Log() << "Hash =" << hashes[set.first];
		for (auto b: set.second)
		{
			Log() << "binding =" << b.binding
				  << "descriptorCount =" << b.descriptorCount
				  << "descriptorType =" << b.descriptorType
				  << "stageFlags =" << b.stageFlags;
		}*/

		//VkDescriptorSetLayout descriptor_set_layout;
		//vkCreateDescriptorSetLayout(vk->device, &descriptor_set_layout_ci, nullptr, &descriptor_set_layout);
		//assert(set.first <= 3);
		VkDescriptorSetLayout decriptor_set_layout;
		vkCreateDescriptorSetLayout(device, &descriptor_set_layout_ci, nullptr, &decriptor_set_layout);

		decriptor_set_layouts.push_back(decriptor_set_layout);

		//layouts.push_back(descriptor_set_layout);
		//store->descriptor_layouts.push_back(descriptor_set_layout);
	}

	/*VkPushConstantRange push_constant_range
	{
		.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
		.offset = 0,
		.size = sizeof(float) * 4,
	};*/

	VkPipelineLayoutCreateInfo pipeline_layout_ci =
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
		.pNext = nullptr,
		.flags = flags,
		.setLayoutCount = uint32_t(decriptor_set_layouts.size()),
		.pSetLayouts = decriptor_set_layouts.data(),
		.pushConstantRangeCount = uint32_t(push_constant_ranges.size()),
		.pPushConstantRanges = push_constant_ranges.data(),
	};

	VkPipelineLayout layout;
	vkCreatePipelineLayout(device, &pipeline_layout_ci, nullptr, &layout);

	return layout;
}


BF_END_VK_NAMESPACE
BF_END_NAMESPACE
