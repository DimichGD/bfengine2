#pragma once
#include "graphics/render_device.hpp"
#include "core/config.hpp"
#include <glm/mat4x4.hpp>
#include <variant>
#include <vector>

BF_BEGIN_NAMESPACE

class RenderDeviceGL: public RenderDevice
{
public:
	struct DeviceLimits
	{
		int max_ubo_size = 0;
		int ubo_alignment = 0;
		int ssbo_alignmemt = 0;
	};

	RenderDeviceGL(Config *config);
	~RenderDeviceGL();

	BF_NON_COPYABLE(RenderDeviceGL)
	BF_NON_MOVABLE(RenderDeviceGL)

	const DeviceLimits &Limits() const { return limits; }

	void Create();
	void BeginRenderPass(glm::ivec4 viewport, RenderPass::Clear clear_flags);
	void EndRenderPass();

	Pipeline CreatePipeline(const PipelineDesc &desc);
	void BindPipeline(Pipeline pipeline);
	void BindVertexBuffer(GPUBuffer buffer);
	void BindIndexBuffer(GPUBuffer buffer);

	//Shader CreateShader(Shader::Type type, const std::string &source);
	Shader CreateShader(Shader::Type type, const std::vector<char> &source);
	void SetUniform(Uniform::Name name, int value);
	void SetUniform(Uniform::Name name, const glm::mat4 &value);
	void SetUniform(Uniform::Name name, const glm::vec4 &value);
	void SetUniform(Uniform::Texture name, const Texture &value);
	void SetUniform(Uniform::Buffer name, const GPUBuffer &value);
	//void WriteUniform(const Uniform &uniform);

	template<typename T>
	GPUBuffer CreateBuffer(GPUBuffer::Type type, const std::vector<T> &vector)
		{ return CreateBuffer(type, vector.size() * sizeof(T), vector.data()); }

	template<typename T>
	void UpdateBuffer(GPUBuffer buffer, const std::vector<T> &vector)
		{ return UpdateBuffer(buffer, vector.size() * sizeof(T), vector.data()); }

	template<typename T>
	T *MapBuffer(GPUBuffer buffer)
		{ return reinterpret_cast<T *>(MapBuffer(buffer)); }

	GPUBuffer CreateBuffer(GPUBuffer::Type type, uint32_t size, const void *data = nullptr);
	void UpdateBuffer(GPUBuffer buffer, uint32_t size, const void *data, uint32_t offset = 0);
	void *MapBuffer(GPUBuffer buffer);
	void UnmapBuffer(GPUBuffer buffer);

	Texture CreateTexture(const TextureDesc &desc, bool generate_mipmaps = false);

	void Draw(const std::vector<DrawCommand> &commands);
	void Draw(uint32_t first, uint32_t count);
	void DrawIndexed(uint32_t first, uint32_t count);

	void CreateDescriptor(Uniform::Texture name, Texture value)
	{
		//descriptors.push_back(DescriptorTexture { name, value });
		descriptors.push_back({ std::to_underlying(name), value });
	}

	void CreateDescriptor(Uniform::Name name, glm::vec4 value)
	{
		//descriptors.push_back(DescriptorVec4 { std::to_underlying(name), value });
		descriptors.push_back({ std::to_underlying(name), value });
	}

	void BindDescriptors(size_t index, size_t count);

protected:
	Program CreateProgram(const std::vector<Shader> &shaders);
	VertexLayout CreateVertexLayout(Vertex::Attrib attribs);

private:
	Config *config = nullptr;

	DeviceLimits limits;
	Pipeline current_pipeline {};

	struct Descriptor
	{
		int location = -1;
		std::variant<Texture, glm::vec4> value;
	};

	std::vector<Descriptor> descriptors;
};

BF_END_NAMESPACE
