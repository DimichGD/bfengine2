#include "resource_manager.hpp"
#include "core/log.hpp"
#include "io/file.hpp"
#include "utils/lexer.hpp"
#include <SDL3_image/SDL_image.h>

BF_BEGIN_NAMESPACE

ResourceManager::ResourceManager(RenderDevice *device, FileSystem *fs)
{
	this->device = device;
	this->fs = fs;

	/*File def_file(fs->GetDataPath() + "materials/definitions.txt");
	def_file.Open();

	auto buffer = def_file.Read();
	Lexer lexer(buffer);
	lexer.Parse();
	auto it = lexer.Tokens().begin();*/


	material_descriptions["doom_static"] = {
		{ EngineDescriptor::CAMERA_MATRICES, EngineDescriptor::MODEL_MATRICES },
		{ EngineConstants::OBJECT_INDEX },
		{
			{ "diffuse_map", { Texture::Format::SRGBA8 } },
			{ "normal_map", { Texture::Format::RGBA8 } },
			{ "specular_map", { Texture::Format::RGBA8 } },
		},
		device->LoadShader(Shader::Type::VERTEX, "deferred/vk_texture"),
		device->LoadShader(Shader::Type::FRAGMENT, "deferred/vk_texture"),
	};

	std::string material_name = "wall/gotbwall4";
	Texture tex_d = LoadTexture(material_name + "_d.ktx", Texture::Format::SRGBA8);
	Texture tex_n = LoadTexture(material_name + "_local.ktx", Texture::Format::RGBA8);
	Texture tex_s = LoadTexture(material_name + "_s.ktx", Texture::Format::RGBA8);
	//materials[material_name] = std::make_shared<PhongMaterial>(tex_d, tex_n, tex_s);
	materials[material_name] = std::make_shared<CustomMaterial>(material_name, &material_descriptions["doom_static"],
																std::vector<Texture> { tex_d, tex_n, tex_s });

	material_name = "floor/diafloor";
	tex_d = LoadTexture(material_name + "_d.ktx", Texture::Format::SRGBA8);
	tex_n = LoadTexture(material_name + "_local.ktx", Texture::Format::RGBA8);
	tex_s = LoadTexture(material_name + "_s.ktx", Texture::Format::RGBA8);
	//materials[material_name] = std::make_shared<PhongMaterial>(tex_d, tex_n, tex_s);
	materials[material_name] = std::make_shared<CustomMaterial>(material_name, &material_descriptions["doom_static"],
																std::vector<Texture> { tex_d, tex_n, tex_s });

	material_name = "red.png";
	tex_d = LoadTexture(material_name);
	materials[material_name] = std::make_shared<Material>(tex_d);
}


ResourceManager::~ResourceManager()
{
	//IMG_Quit();
}

Texture ResourceManager::LoadKTX2(std::string_view filename, Texture::Format format)
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

	uint32_t bytes_read = 0;
	std::vector<char> pixels(total_bytes);
	for (auto &level: levels)
	{
		file.Seek(level.byte_offset);
		file.Read(&pixels[bytes_read], level.byte_length);

		bytes_read += level.byte_length;
	}

	//if (filename.contains("_local") || filename.contains("_s"))
	//	format = Texture::Format::RGBA8;

	//Log() << filename << vk_format;

	TextureDesc desc
	{
		.width = width,
		.height = height,
		.format = format,
		.usage = Texture::Usage::SHADER_READ,
		.levels = level_count,
		.pixels = pixels.data(),
		.generate_mipmaps = false,
	};

	//Log() << vk_format << type_size << width << height << depth << layer_count << face_count << level_count << supercompression;
	//Log() << dfd_byte_offset << dfd_byte_length << kvd_byte_offset << kvd_byte_length << sgd_byte_offset << sgd_byte_length;

	return device->CreateTexture(std::string(filename), desc);
}

Texture ResourceManager::LoadTexture(std::string_view filename, Texture::Format format)
{
	if (filename.contains(".ktx"))
		return LoadKTX2(filename, format);

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

	TextureDesc desc
	{
		.width = uint32_t(surf->w),
		.height = uint32_t(surf->h),
		.format = format,
		.usage = Texture::Usage::SHADER_READ,
		.levels = 1,
		.pixels = surf->pixels,
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
		return nullptr; // Load material

	return it->second;
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
			surfaces[i] = { { vertex_start, vertex_count }, LoadMaterial(material_name), 0, {} };
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
