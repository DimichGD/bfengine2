#include "graphics/vulkan/vk_shader_reflection.hpp"
#include "core/log.hpp"
#include "graphics/vulkan/convert_enum_vk.hpp"
#include "utils/hash.hpp"
#include <glm/common.hpp>
#include <shaderc/shaderc.h>
#include <spirv_cross.hpp>
//#include <spirv_reflect.hpp>

BF_BEGIN_NAMESPACE
BF_BEGIN_VK_NAMESPACE

ShaderReflectionData GetShaderReflection(const std::string &name, Shader::Type type, const uint32_t *spirv, size_t word_count)
{
	std::vector<Constant> constants;
	std::array<std::vector<Descriptor2>, 4> sets;

	spirv_cross::Compiler compiler(spirv, word_count);
	spirv_cross::ShaderResources resources = compiler.get_shader_resources();

	//Log() << "------------------------------------------";
	uint32_t max_set = 0;

	for (auto &resource: resources.uniform_buffers)
	{
		uint32_t array_size = 1;
		uint32_t set = compiler.get_decoration(resource.id, spirv_cross::DecorationDescriptorSet);
		uint32_t binding = compiler.get_decoration(resource.id, spirv_cross::DecorationBinding);

		const spirv_cross::SPIRType &spirv_type = compiler.get_type(resource.type_id);
		if (!spirv_type.array.empty())
			array_size = spirv_type.array[0];

		//descriptors.emplace_back(set, binding, Descriptor2::Type::UNIFORM_BUFFER, 1, type);
		max_set = glm::max(max_set, set);
		// TODO: assert set count
		sets[set].emplace_back(set, binding, Descriptor2::Type::UNIFORM_BUFFER, array_size);
		//Log() << "Uniform buffer" << set << binding;
	}

	for (auto &resource: resources.storage_buffers)
	{
		uint32_t array_size = 1;
		uint32_t set = compiler.get_decoration(resource.id, spirv_cross::DecorationDescriptorSet);
		uint32_t binding = compiler.get_decoration(resource.id, spirv_cross::DecorationBinding);

		const spirv_cross::SPIRType &spirv_type = compiler.get_type(resource.type_id);
		if (!spirv_type.array.empty())
			array_size = spirv_type.array[0];

		//descriptors.emplace_back(set, binding, Descriptor2::Type::STORAGE_BUFFER, 1, type);
		max_set = glm::max(max_set, set);
		sets[set].emplace_back(set, binding, Descriptor2::Type::STORAGE_BUFFER, array_size);
		//Log() << "Storage buffer" << set << binding;
	}

	for (auto &resource: resources.sampled_images)
	{
		uint32_t array_size = 1;
		uint32_t set = compiler.get_decoration(resource.id, spirv_cross::DecorationDescriptorSet);
		uint32_t binding = compiler.get_decoration(resource.id, spirv_cross::DecorationBinding);

		const spirv_cross::SPIRType &spirv_type = compiler.get_type(resource.type_id);
		if (!spirv_type.array.empty())
			array_size = spirv_type.array[0];

		//descriptors.emplace_back(set, binding, Descriptor2::Type::TEXTURE, array_size, type);
		max_set = glm::max(max_set, set);
		sets[set].emplace_back(set, binding, Descriptor2::Type::TEXTURE, array_size);

		//Log() << "Texture" << set << binding << array_size;
	}

	for (auto &resource: resources.push_constant_buffers)
	{
		for (auto &range: compiler.get_active_buffer_ranges(resource.id))
		{
			const spirv_cross::SPIRType &spirv_type = compiler.get_type(resource.type_id);
			Constant::Type type = Constant::Type::INT;
			if (spirv_type.basetype == spirv_cross::SPIRType::BaseType::Float)
				type = Constant::Type::FLOAT;

			constants.emplace_back(range.offset, range.range, type);
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

	return { name, max_set, type, std::move(constants), std::move(sets) };
}

std::vector<uint32_t> CompileShader(const std::string &name, const std::vector<char> &source)
{
	shaderc_compiler_t compiler = shaderc_compiler_initialize();
	shaderc_compile_options_t options = shaderc_compile_options_initialize();

	shaderc_compile_options_set_optimization_level(options, shaderc_optimization_level_performance);
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

VkPipelineLayout CreatePipelineLayout(VkDevice device,
									  std::map<uint32_t, VkDescriptorSetLayout> &global_descriptor_set_layouts,
									  const std::vector<ShaderReflectionData *> &reflection_data,
									  std::vector<VkDescriptorSetLayout> &decriptor_set_layouts,
									  VkPipelineLayoutCreateFlags flags)
{
	std::vector<VkPushConstantRange> push_constant_ranges;

	// TODO: overlapping ranges
	for (const ShaderReflectionData *data: reflection_data)
	{
		for (auto &desc: data->constants)
		{
			VkPushConstantRange push_constant_range
			{
				.stageFlags = vk::ConvertEnum(data->stage),
				.offset = desc.offset,
				.size = desc.size, //const_sizes_map[desc.type],
			};

			push_constant_ranges.push_back(push_constant_range);
		}
	}

	//
	/*Log() << "--------------------------";
	for (const ShaderReflectionData *data: reflection_data)
		Log() << data->name;*/

	std::map<Descriptor2::Type, std::string> type_name
	{
		{ Descriptor2::Type::UNIFORM_BUFFER, "UNIFORM_BUFFER" },
		{ Descriptor2::Type::STORAGE_BUFFER, "STORAGE_BUFFER" },
		{ Descriptor2::Type::TEXTURE, "TEXTURE" },
	};

	std::map<VkShaderStageFlagBits, std::string> stage_name
	{
		{ VK_SHADER_STAGE_VERTEX_BIT, "VERTEX" },
		{ VK_SHADER_STAGE_FRAGMENT_BIT, "FRAGMENT" },
	};

	// merge reflection data

	struct StageDescriptor
	{
		Descriptor2 descriptor;
		VkShaderStageFlags stage_flags = 0;
	};

	/*struct StageConstant
	{
		Constant constant;
		VkShaderStageFlags stage_flags = 0;
	};*/

	std::array<std::vector<StageDescriptor>, 4> combined_descriptors;
	//std::vector<StageConstant> combined_constants;

	for (const ShaderReflectionData *data: reflection_data)
	{
		for (size_t i = 0; i < data->sets.size(); i++)
		{
			for (auto &desc: data->sets[i])
			{
				auto it = std::find_if(combined_descriptors[i].begin(), combined_descriptors[i].end(),
									   [&desc](const StageDescriptor &other){ return other.descriptor == desc; });

				if (it != combined_descriptors[i].end())
					it->stage_flags |= vk::ConvertEnum(data->stage);

				else
					combined_descriptors[i].push_back({ desc, vk::ConvertEnum(data->stage) });
			}
		}

		/*for (auto &constant: data->constants)
		{
			auto it = std::find_if(combined_constants.begin(), combined_constants.end(),
								   [&constant](const StageConstant &other){ return other.constant == constant; });

			if (it != combined_constants.end())
				it->stage_flags |= vk::ConvertEnum(data->stage);

			else
				combined_constants.push_back({ constant, vk::ConvertEnum(data->stage) });
		}*/
	}

	// sort descriptors by binding

	for (auto &descriptors: combined_descriptors)
	{
		if (descriptors.empty())
			continue;

		std::sort(descriptors.begin(), descriptors.end(),
				  [](const StageDescriptor &a, const StageDescriptor &b){ return a.descriptor.binding < b.descriptor.binding; });
	}

	// create set layout

	for (auto &set: combined_descriptors)
	{
		if (set.empty())
			continue; // FIXME: deal with empty sets

		std::vector<VkDescriptorSetLayoutBinding> bindigns;
		bindigns.reserve(set.size());

		uint32_t set_hash = set.size(); // better seed?

		for (auto &desc: set)
		{
			VkDescriptorSetLayoutBinding binding
			{
				.binding = desc.descriptor.binding,
				.descriptorType = vk::ConvertEnum(desc.descriptor.type),
				.descriptorCount = desc.descriptor.array_size,
				.stageFlags = desc.stage_flags,
				.pImmutableSamplers = nullptr,
			};

			bindigns.push_back(binding);
			set_hash = hash(set_hash, desc.descriptor.Hash());
			set_hash = hash(set_hash, desc.stage_flags);
			//Log() << uint32_t(desc.descriptor.set) << uint32_t(desc.descriptor.binding)
			//	  << type_name[desc.descriptor.type] << desc.stage_flags;
		}

		if (set_hash == 0)
			throw std::runtime_error("Descriptor set hash cannot be zero");

		auto it = global_descriptor_set_layouts.find(set_hash);
		if (it != global_descriptor_set_layouts.end())
		{
			//Log() << it->first << "Found in global_descriptor_set_layouts";
			decriptor_set_layouts.push_back(it->second);
			continue;
		}

		//if (!set.empty())
		//	Log() << "hash" << set_hash;


		/*std::vector<VkDescriptorBindingFlags> flags(bindigns.size());
		for (uint32_t i = 0; i < set.size(); i++)
			flags[i] = (bindigns.at(i).descriptorCount > 1) ? VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT : 0;

		VkDescriptorSetLayoutBindingFlagsCreateInfo flags_ci
		{
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO,
			.pNext = nullptr,
			.bindingCount = uint32_t(flags.size()),
			.pBindingFlags = flags.data(),
		};*/

		VkDescriptorSetLayoutCreateInfo descriptor_set_layout_ci
		{
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.bindingCount = uint32_t(bindigns.size()),
			.pBindings = bindigns.data(),
		};

		VkDescriptorSetLayout decriptor_set_layout;
		vkCreateDescriptorSetLayout(device, &descriptor_set_layout_ci, nullptr, &decriptor_set_layout);

		decriptor_set_layouts.push_back(decriptor_set_layout);
		global_descriptor_set_layouts[set_hash] = decriptor_set_layout;
	}

	// push constant ranges

	/*std::vector<VkPushConstantRange> push_constant_ranges;
	push_constant_ranges.reserve(combined_constants.size());

	for (auto &constant: combined_constants)
	{
		VkPushConstantRange range
		{
			.stageFlags = constant.stage_flags,
			.offset = constant.constant.offset,
			.size = constant.constant.size,
		};

		push_constant_ranges.push_back(range);
	}*/

	// create pipeline layout

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
