#include "resource_manager.hpp"
#include "core/log.hpp"
#include "io/file.hpp"
#include "utils/lexer.hpp"
#include "utils/parser.hpp"
#include <SDL3_image/SDL_image.h>
#include <fmt/format.h>

BF_BEGIN_NAMESPACE

ResourceManager::ResourceManager(RenderDevice *device, FileSystem *fs)
{
	this->device = device;
	this->fs = fs;

	File def_file(fs->GetDataPath() + "shaders/shaders.def");
	def_file.Open();

	auto buffer = def_file.Read();
	Parser parser(buffer);
	shader_descriptions.merge(parser.DoStuff()); // TODO: check if parser result map has remaining items

	File mat_file(fs->GetDataPath() + "materials/materials.def");
	mat_file.Open();

	buffer = mat_file.Read();
	Parser parser2(buffer);
	//material_defs.merge(parser2.DoStuff2());
	uint32_t mat_index = 0;
	for (auto mat: parser2.DoStuff2())
	{
		std::vector<Texture> textures;

		for (auto tex: mat.second)
			textures.push_back(LoadTexture(tex.first, tex.second));

		materials[mat.first] = std::make_shared<CustomMaterial>(mat.first, std::move(textures), mat_index);

		mat_index += 3;
	}

	std::string material_name = "red.png";
	Texture tex_d = LoadTexture(material_name);
	materials[material_name] = std::make_shared<Material>(tex_d);
}


ResourceManager::~ResourceManager()
{
	//IMG_Quit();
}

Texture ResourceManager::LoadKTX2(std::string_view filename)
{
	File file(fs->GetDataPath() + "textures/" + filename);
	if (!file.Open())
		return {};

	char magic[12];
	uint32_t vk_format;
	uint32_t type_size;
	uint32_t width;
	uint32_t height;
	uint32_t depth;
	uint32_t layer_count;
	uint32_t face_count;
	uint32_t level_count;
	uint32_t supercompression;

	uint32_t dfd_byte_offset;
	uint32_t dfd_byte_length;
	uint32_t kvd_byte_offset;
	uint32_t kvd_byte_length;
	uint64_t sgd_byte_offset;
	uint64_t sgd_byte_length;

	file.Read(magic, 12);
	file.Read(&vk_format);
	file.Read(&type_size);
	file.Read(&width);
	file.Read(&height);
	file.Read(&depth);
	file.Read(&layer_count);
	file.Read(&face_count);
	file.Read(&level_count);
	file.Read(&supercompression);

	file.Read(&dfd_byte_offset);
	file.Read(&dfd_byte_length);
	file.Read(&kvd_byte_offset);
	file.Read(&kvd_byte_length);
	file.Read(&sgd_byte_offset);
	file.Read(&sgd_byte_length);

	struct Level
	{
		uint64_t byte_offset;
		uint64_t byte_length;
		uint64_t uncompressed_byte_length;
	};

	uint32_t total_bytes = 0;
	std::vector<Level> levels(level_count);

	for (uint32_t i = 0; i < level_count; i++)
	{
		file.Read(&levels[i].byte_offset);
		file.Read(&levels[i].byte_length);
		file.Read(&levels[i].uncompressed_byte_length);

		total_bytes += levels[i].byte_length;
		//Log() << level.byte_offset << level.byte_length << level.uncompressed_byte_length;
	}

	Texture::Format format;
	switch (vk_format)
	{
		case 37:
			format = Texture::Format::RGBA8;
			break;

		case 43:
			format = Texture::Format::SRGBA8;
			break;

		default:
			throw std::runtime_error("Unknown texture format");
	}

	uint32_t bytes_read = 0;
	std::vector<char> pixels(total_bytes);
	for (auto &level: levels)
	{
		file.Seek(level.byte_offset);
		file.Read(&pixels[bytes_read], level.byte_length);

		bytes_read += level.byte_length;
	}

	//Log() << filename << vk_format;

	TextureDesc desc
	{
		.width = width,
		.height = height,
		.format = format,
		.usage = Texture::Usage::SHADER_READ,
		.levels = level_count,
		.pixels = std::move(pixels),
		.generate_mipmaps = false,
	};

	//Log() << vk_format << type_size << width << height << depth << layer_count << face_count << level_count << supercompression;
	//Log() << dfd_byte_offset << dfd_byte_length << kvd_byte_offset << kvd_byte_length << sgd_byte_offset << sgd_byte_length;

	return device->CreateTexture(std::string(filename), desc);
}

Texture ResourceManager::LoadTexture(std::string_view filename, Texture::Format format)
{
	if (filename.ends_with(".ktx"))
		return LoadKTX2(filename);

	File file(fs->GetDataPath() + "textures/" + filename);
	if (!file.Open())
		return {};

	auto buffer = file.Read();
	//SDL_RWops *rw_ops = SDL_RWFromConstMem(buffer.data(), buffer.size());
	//SDL_Surface *surf = IMG_Load_RW(rw_ops, 0);
	SDL_Surface *surf = IMG_Load_IO(SDL_IOFromConstMem(buffer.data(), buffer.size()), false);
	if (surf == nullptr)
	{
		Log() << "IMG_Load_RW failed" << SDL_GetError();
		return {};
	}

	//Texture::Format format = Texture::Format::RGB8;
	switch (surf->format)
	{
		case SDL_PIXELFORMAT_INDEX8:
			format = Texture::Format::R8;
			break;

		case SDL_PIXELFORMAT_RGB24:
		case SDL_PIXELFORMAT_BGR24:
			Log() << "RGB8 is not supported";
			break;

		case SDL_PIXELFORMAT_RGBA32:
			format = Texture::Format::RGBA8;
			break;

		default:
			Log("ResourceManager::LoadTexture") << filename << "Unsupported image format" << SDL_GetPixelFormatName(surf->format);
	}

	if (surf->format == SDL_PIXELFORMAT_RGBA32 && SDL_GetSurfaceColorspace(surf) == SDL_COLORSPACE_SRGB)
		format = Texture::Format::SRGBA8;

	//if (filename.contains("_local") || filename.contains("_s"))
	//	format = Texture::Format::RGBA8;

	//Log() << "Color space srgb" << (SDL_GetSurfaceColorspace(surf) == SDL_COLORSPACE_SRGB);

	std::vector<char> pixels(surf->pitch * surf->h);
	std::memcpy(pixels.data(), surf->pixels, pixels.size());

	TextureDesc desc
	{
		.width = uint32_t(surf->w),
		.height = uint32_t(surf->h),
		.format = format,
		.usage = Texture::Usage::SHADER_READ,
		.levels = 1,
		.pixels = std::move(pixels),
		.generate_mipmaps = true,
	};

	Texture result = device->CreateTexture(std::string(filename), desc);
	SDL_DestroySurface(surf);

	return result;
}

std::shared_ptr<IMaterial> ResourceManager::LoadMaterial(const std::string &name)
{
	auto it = materials.find(name);
	if (it == materials.end())
		throw std::runtime_error(fmt::format("material {} not found", name));

	return it->second;
}

Shader ResourceManager::LoadShader(const std::string &name)
{
	auto cache_it = shader_cache.find(name);
	if (cache_it != shader_cache.end())
		return cache_it->second;

	RenderDeviceVK *vk_device = static_cast<RenderDeviceVK *>(device);
	std::string cache_name = name + ".spv";
	std::replace(cache_name.begin(), cache_name.end(), '/', '-');
	std::replace(cache_name.begin(), cache_name.end(), ' ', '-');

	auto desc_it = shader_descriptions.find(name);
	if (desc_it == shader_descriptions.end())
	{
		Error() << "Shader description" << name << "not found";
		return {};
	}

	File source_file(fs->GetDataPath() + "shaders/" + desc_it->second.filename);
	File cache_file(fs->GetDataPath() + "shaders/cache/" + cache_name);
	if (cache_file.Open() && cache_file.LastWriteTime() > source_file.LastWriteTime())
	{
		std::vector<uint32_t> binary(cache_file.Size() / sizeof(uint32_t));
		cache_file.Read(binary.data(), cache_file.Size());

		Shader shader = vk_device->LoadShader(cache_name, desc_it->second, binary);
		shader_cache[name] = shader;
		return shader;
	}

	return vk_device->LoadShader(cache_name, desc_it->second);
}

Mesh ResourceManager::LoadMesh(std::string_view filename)
{
	File mesh_file(fs->GetDataPath() + "models/" + filename);
	if (!mesh_file.Open())
		return {};

	uint32_t magic, version, surface_count;
	mesh_file.Read(&magic);
	mesh_file.Read(&version);
	mesh_file.Read(&surface_count);
	//Log() << version << FOUR_CC("BFMS");

	std::vector<Surface> surfaces(surface_count);

	for (uint32_t i = 0; i < surface_count; i++)
	{
		uint32_t vertex_start, vertex_count, name_length;
		std::string material_name;

		mesh_file.Read(&vertex_start);
		mesh_file.Read(&vertex_count);
		mesh_file.Read(&name_length);
		material_name.resize(name_length);
		mesh_file.Read(material_name.data(), name_length);

		if (version == 1)
		{
			Log("ResourceManager::LoadMesh") << "Version 1 unimplemented";
		}

		if (version == 2)
		{
			/*Texture tex_d = LoadTexture(material_name);
			Material *mat = new Material(tex_d);*/
			surfaces[i] = { { vertex_start, vertex_count }, LoadMaterial(material_name), 0, {} };
		}

		if (version == 3)
		{
			/*Texture tex_d = LoadTexture(material_name + "_d.png");
			Texture tex_n = LoadTexture(material_name + "_local.png");
			Texture tex_s = LoadTexture(material_name + "_s.png");
			PhongMaterial *mat = new PhongMaterial(tex_d, tex_n, tex_s);*/
			//Log() << material_name;
			auto material = std::static_pointer_cast<CustomMaterial>(LoadMaterial(material_name));
			surfaces[i] = { { vertex_start, vertex_count }, material, material->index, {} };
		}
	}

	uint32_t vertex_stride, vertex_count;
	mesh_file.Read(&vertex_stride);
	mesh_file.Read(&vertex_count);

	std::vector<char> verts(vertex_count * vertex_stride);
	mesh_file.Read(verts.data(), vertex_count * vertex_stride);

	GPUBuffer vbo = device->CreateBuffer(GPUBuffer::VERTEX, verts);
	return { .name = std::string(filename), .surfaces = surfaces, .vbo = vbo, .matrix_index = 0 };
}

BF_END_NAMESPACE
