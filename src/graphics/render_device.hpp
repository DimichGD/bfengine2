#pragma once
#include "core/defines.hpp"
#include "graphics/shader_description.hpp"
#include "graphics/types.hpp"
#include <vector>

struct SDL_Window;

BF_BEGIN_NAMESPACE

class RenderDevice
{
public:
	virtual ~RenderDevice() = default;

	virtual bool Create(SDL_Window *window_handle) = 0;
	virtual void Destroy() = 0;
	virtual void BeginRenderPass(FramebufferID framebuffer_id, RenderPass::Clear clear_flags) = 0;
	virtual void EndRenderPass(FramebufferID framebuffer_id) = 0;

	virtual PipelineID CreatePipeline(const std::string &name, const PipelineDesc &desc) = 0;
	virtual void BindPipeline(PipelineID pipeline_id) = 0;
	virtual void BindVertexBuffer(GPUBuffer buffer) = 0;
	virtual void BindIndexBuffer(GPUBuffer buffer) = 0;

	virtual Shader LoadShader(Shader::Type type, const std::string &name) = 0;
	virtual FramebufferID CreateFramebuffer(const FramebufferDesc &desc) = 0;

	virtual void SetCullMode(uint32_t mode) = 0;
	virtual void LayoutTransition(Texture texture, ImageLayout from, ImageLayout to) = 0;
	virtual void BeginFrame() = 0;
	virtual void EndFrame() = 0;
	virtual DescriptorSet CreateDescriptorSet(PipelineID pipeline, Descriptor2::Set set) = 0;
	virtual void WriteDescriptor(DescriptorSet set, uint32_t binding, GPUBuffer value) = 0;
	virtual void WriteDescriptor(DescriptorSet set, uint32_t binding, Texture value, uint32_t index = 0) = 0;
	virtual void BindDescriptorSet(Descriptor2::Set index, DescriptorSet descriptor_set) = 0;
	//virtual void Push(Shader::Type type, uint32_t offset, int value) = 0;
	virtual void PushConstant(EngineConstants slot, int value) = 0;
	virtual void PushConstant(EngineConstants slot, float value) = 0;

	template<typename T>
	GPUBuffer CreateBuffer(GPUBuffer::Type type, const std::vector<T> &vector)
		{ return CreateBuffer(type, vector.size() * sizeof(T), vector.data()); }

	template<typename T>
	void UpdateBuffer(GPUBuffer buffer, const std::vector<T> &vector)
		{ return UpdateBuffer(buffer, vector.size() * sizeof(T), vector.data()); }

	template<typename T>
	std::span<T> MapBuffer(GPUBuffer buffer)
	{
		T *t = reinterpret_cast<T*>(MapBuffer(buffer));
		return { t, size_t(buffer.size / sizeof(T)) };
	}

	virtual GPUBuffer CreateBuffer(GPUBuffer::Type type, uint32_t size, const void *data = nullptr) = 0;
	virtual void UpdateBuffer(GPUBuffer buffer, uint32_t size, const void *data, uint32_t offset = 0) = 0;
	virtual void *MapBuffer(GPUBuffer buffer) = 0;
	virtual void UnMapBuffer(GPUBuffer buffer) = 0;

	virtual Texture CreateTexture(const std::string &name, const TextureDesc &desc) = 0;

	virtual void Draw(uint32_t first, uint32_t count) = 0;
	virtual void DrawIndexed(uint32_t first, uint32_t count) = 0;
};

BF_END_NAMESPACE
