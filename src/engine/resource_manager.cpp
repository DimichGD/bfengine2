#include "resource_manager.hpp"
#include "core/log.hpp"
#include "io/file.hpp"
#include <SDL3_image/SDL_image.h>
#include <filesystem>

BF_BEGIN_NAMESPACE

ResourceManager::ResourceManager(RenderDevice *device, FileSystem *fs)
{
	this->device = device;
	this->fs = fs;

	std::string material_name = "wall/gotbwall4";
	Texture tex_d = LoadTexture(material_name + "_d.png");
	Texture tex_n = LoadTexture(material_name + "_local.png");
	Texture tex_s = LoadTexture(material_name + "_s.png");
	materials[material_name] = std::make_shared<PhongMaterial>(tex_d, tex_n, tex_s);

	material_name = "floor/diafloor";
	tex_d = LoadTexture(material_name + "_d.png");
	tex_n = LoadTexture(material_name + "_local.png");
	tex_s = LoadTexture(material_name + "_s.png");
	materials[material_name] = std::make_shared<PhongMaterial>(tex_d, tex_n, tex_s);

	material_name = "red.png";
	tex_d = LoadTexture(material_name);
	materials[material_name] = std::make_shared<Material>(tex_d);
}


ResourceManager::~ResourceManager()
{
	//IMG_Quit();
}

Texture ResourceManager::LoadTexture(std::string_view filename)
{
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

	Texture::Format format = Texture::Format::RGB8;
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

	if (filename.contains("_local") || filename.contains("_s"))
		format = Texture::Format::RGBA8;

	//Log() << "Color space srgb" << (SDL_GetSurfaceColorspace(surf) == SDL_COLORSPACE_SRGB);

	TextureDesc desc
	{
		.width = uint32_t(surf->w),
		.height = uint32_t(surf->h),
		.format = format,
		.usage = Texture::Usage::SHADER_READ,
		.levels = 1,
		.pixels = surf->pixels,
		.generate_mipmaps = false,
	};

	Texture result = device->CreateTexture(std::string(filename), desc);
	//device2->SetDebugName(result, std::string(filename).c_str());
	SDL_DestroySurface(surf);

	return result;
}

/*Shader ResourceManager::LoadShader(Shader::Type type, const std::string &filename)
{
	File file(fs->GetDataPath() + "shaders/" + filename);
	file.Open();

	return device ? device->CreateShader(type, file.Read()) : device2->CreateShader(filename, type, file.Read());
}*/

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
			surfaces[i] = { { vertex_start, vertex_count }, LoadMaterial(material_name), 0 };
		}

		if (version == 3)
		{
			/*Texture tex_d = LoadTexture(material_name + "_d.png");
			Texture tex_n = LoadTexture(material_name + "_local.png");
			Texture tex_s = LoadTexture(material_name + "_s.png");
			PhongMaterial *mat = new PhongMaterial(tex_d, tex_n, tex_s);*/
			//Log() << material_name;
			surfaces[i] = { { vertex_start, vertex_count }, LoadMaterial(material_name), 0 };
		}
	}

	uint32_t vertex_stride, vertex_count;
	mesh_file.Read(&vertex_stride);
	mesh_file.Read(&vertex_count);

	std::vector<char> verts(vertex_count * vertex_stride);
	mesh_file.Read(verts.data(), vertex_count * vertex_stride);

	GPUBuffer cubes_vbo = device->CreateBuffer(GPUBuffer::VERTEX, verts);
	return { .surfaces = surfaces, .vbo = cubes_vbo, .matrix_index = 0 };
}

std::shared_ptr<IMaterial> ResourceManager::LoadMaterial(const std::string &name)
{
	auto it = materials.find(name);
	if (it == materials.end())
		return nullptr; // Load material

	return it->second;
}

BF_END_NAMESPACE
