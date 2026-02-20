#pragma once
#include "core/defines.hpp"
#include "graphics/types.hpp"
#include <vector>

BF_BEGIN_NAMESPACE

class RenderDevice
{
public:
	virtual ~RenderDevice() = default;

	virtual void Create() = 0;
	virtual void BeginRenderPass(glm::ivec4 viewport, RenderPass::Clear clear_flags) = 0;
	virtual void EndRenderPass() = 0;

	virtual Pipeline CreatePipeline(const PipelineDesc &desc) = 0;
	virtual void BindPipeline(Pipeline pipeline) = 0;
	virtual void BindVertexBuffer(GPUBuffer buffer) = 0;
	virtual void BindIndexBuffer(GPUBuffer buffer) = 0;

	//Shader CreateShader(Shader::Type type, const std::string &source);
	virtual Shader CreateShader(Shader::Type type, const std::vector<char> &source) = 0;
	/*void SetUniform(Uniform::Name name, int value);
	void SetUniform(Uniform::Name name, const glm::mat4 &value);
	void SetUniform(Uniform::Name name, const glm::vec4 &value);
	void SetUniform(Uniform::Texture name, const Texture &value);
	void SetUniform(Uniform::Buffer name, const GPUBuffer &value);*/

	template<typename T>
	GPUBuffer CreateBuffer(GPUBuffer::Type type, const std::vector<T> &vector)
		{ return CreateBuffer(type, vector.size() * sizeof(T), vector.data()); }

	template<typename T>
	void UpdateBuffer(GPUBuffer buffer, const std::vector<T> &vector)
		{ return UpdateBuffer(buffer, vector.size() * sizeof(T), vector.data()); }

	/*template<typename T>
	T *MapBuffer(GPUBuffer buffer)
		{ return reinterpret_cast<T *>(MapBuffer(buffer)); }*/

	virtual GPUBuffer CreateBuffer(GPUBuffer::Type type, uint32_t size, const void *data = nullptr) = 0;
	virtual void UpdateBuffer(GPUBuffer buffer, uint32_t size, const void *data, uint32_t offset = 0) = 0;
	//void *MapBuffer(GPUBuffer buffer);
	//void UnmapBuffer(GPUBuffer buffer);

	virtual Texture CreateTexture(const TextureDesc &desc, bool generate_mipmaps = false) = 0;

	virtual void Draw(uint32_t first, uint32_t count) = 0;
	virtual void DrawIndexed(uint32_t first, uint32_t count) = 0;

	virtual void CreateDescriptor(Uniform::Texture name, Texture value) = 0;
	virtual void CreateDescriptor(Uniform::Name name, glm::vec4 value) = 0;
	virtual void BindDescriptors(size_t index, size_t count) = 0;
};

BF_END_NAMESPACE
