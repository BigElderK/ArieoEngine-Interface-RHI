#pragma once
#include "interface/window/window.h"
#include "interface/rhi/rhi_enums.h"
namespace Arieo::Interface::RHI
{
    class IRenderDevice;

    class IFence
    {
    public:
        virtual void wait() = 0;
        virtual void reset() = 0;
    };

    class ISemaphore
    {
    public:
    };

    class IRenderSurface
    {
    public:
        virtual Base::InteropOld<Interface::Window::IWindow> getAttachedWindow() = 0;
    };

    class IRenderInstance
    {
    public:
        virtual std::vector<std::string>& getHardwareInfomations() = 0;
        virtual Base::InteropOld<IRenderSurface> createSurface(Base::InteropOld<Interface::Window::IWindowManager> window_manager, Base::InteropOld<Interface::Window::IWindow> window) = 0;
        virtual void destroySurface(Base::InteropOld<IRenderSurface> surface) = 0;

        virtual Base::InteropOld<IRenderDevice> createDevice(size_t hardware_index, Base::InteropOld<IRenderSurface> surface) = 0;
        virtual void destroyDevice(Base::InteropOld<IRenderDevice> device) = 0;
    };

    class IFramebuffer
    {

    };

    class IBuffer
    {
    public:
        virtual void* mapMemory(size_t offset, size_t size) = 0;
        virtual void unmapMemory() = 0;
    };

    class IPipeline
    {

    };

    class IImageView
    {

    };

    class IImageSampler
    {

    };

    class ISwapchain
    {
    public:
        virtual Base::Math::Rect<size_t>& getExtent() = 0;
        virtual std::vector<Base::InteropOld<IImageView>>& getImageViews() = 0;
        virtual std::uint32_t acquireNextImageIndex(Base::InteropOld<ISemaphore>) = 0;
        virtual bool isLost() = 0;
    };

    class IImage
    {
    public:
        virtual size_t getMemorySize() = 0;
        virtual Base::InteropOld<IImageView> getImageView() = 0;
        virtual Base::InteropOld<IImageSampler> getImageSampler() = 0;
    };

    class IShader
    {

    };

    class IDescriptorSet
    {
    public:
        virtual void bindBuffer(size_t bind_index, Base::InteropOld<IBuffer>, size_t offset, size_t size) = 0;
        virtual void bindImage(size_t bind_index, Base::InteropOld<IImage>) = 0;
    };

    class IDescriptorPool
    {
    public:
        virtual Base::InteropOld<IDescriptorSet> allocateDescriptorSet(Base::InteropOld<IPipeline> pipeline) = 0;
        virtual void freeDescriptorSet(Base::InteropOld<IDescriptorSet>) = 0;
    };

        class ICommandBuffer
    {
    public:
        virtual void reset() = 0;

        virtual void begin() = 0;
        virtual void end() = 0;

        virtual void beginRenderPass(Base::InteropOld<IPipeline>, Base::InteropOld<IFramebuffer>) = 0;
        virtual void endRenderPass() = 0;

        virtual void bindVertexBuffer(Base::InteropOld<IBuffer>, uint32_t offset) = 0;
        virtual void bindIndexBuffer(Base::InteropOld<IBuffer>, uint32_t offset) = 0;

        virtual void bindPipeline(Base::InteropOld<IPipeline>) = 0;

        virtual void draw(std::uint32_t vertex_count, std::uint32_t instance_count, std::uint32_t first_vertex, std::uint32_t first_instance) = 0;
        virtual void drawIndexed(uint32_t index_count, uint32_t instance_count, uint32_t first_index, int32_t vertex_offset, uint32_t first_instance) = 0;

        virtual void bindDescriptorSets(Base::InteropOld<IPipeline>, Base::InteropOld<IDescriptorSet>) = 0;

        virtual void copyBuffer(Base::InteropOld<IBuffer>, Base::InteropOld<IBuffer>, std::uint32_t) = 0;
        virtual void copyBufferToImage(Base::InteropOld<IBuffer>, Base::InteropOld<IImage>) = 0;
        virtual void prepareDepthImage(Base::InteropOld<IImage> depth_image) = 0;
    };

    class ICommandPool
    {
    public:
        virtual Base::InteropOld<ICommandBuffer> allocateCommandBuffer() = 0;
        virtual void freeCommandBuffer(Base::InteropOld<ICommandBuffer>) = 0;
    };

    class ICommandQueue
    {
    public:
        virtual Base::InteropOld<ICommandPool> createCommandPool() = 0;
        virtual void destroyCommandPool(Base::InteropOld<ICommandPool>) = 0;
        virtual void waitIdle() = 0;
    };

    class IRenderCommandQueue
        : public ICommandQueue
    {
    public:
        virtual void submitCommand(Base::InteropOld<ICommandBuffer>, Base::InteropOld<IFence>, Base::InteropOld<ISemaphore> wait_semaphore, Base::InteropOld<ISemaphore> signal_semaphore) = 0;
        virtual void submitCommand(Base::InteropOld<ICommandBuffer>) = 0;
    };

    class IPresentCommandQueue
        : public ICommandQueue
    {
    public:
        virtual void present(Base::InteropOld<ISwapchain>, std::uint32_t swapchain_image_index, Base::InteropOld<IFramebuffer>, Base::InteropOld<ISemaphore> signal_semaphore) = 0;
    };

    class IRenderDevice
    {
    public:
        virtual Format findSupportedFormat(const std::vector<Format>& candidate_formats, ImageTiling, FormatFeatureFlags) = 0;

        virtual Base::InteropOld<IRenderCommandQueue> getGraphicsCommandQueue() = 0;
        virtual Base::InteropOld<IPresentCommandQueue> getPresentCommandQueue() = 0;

        virtual Base::InteropOld<ISwapchain> createSwapchain(Base::InteropOld<IRenderSurface>) = 0;
        virtual void destroySwapchain(Base::InteropOld<ISwapchain>) = 0;

        virtual Base::InteropOld<IImage> createImage(std::uint32_t width, std::uint32_t height, Format format, ImageAspectFlags aspect, ImageTiling tiling, ImageUsageFlags usage, MemoryUsage memory_usage) = 0;
        virtual void destroyImage(Base::InteropOld<IImage>) = 0;

        virtual Base::InteropOld<IFramebuffer> createFramebuffer(Base::InteropOld<IPipeline>, Base::InteropOld<ISwapchain>, std::vector<Base::InteropOld<IImageView>>& attachment_array) = 0;
        virtual void destroyFramebuffer(Base::InteropOld<IFramebuffer>) = 0;

        virtual Base::InteropOld<IShader> createShader(void* buf, size_t buf_size) = 0;
        virtual void destroyShader(Base::InteropOld<IShader>) = 0; 

        //TODO: remove target_image_view from here
        virtual Base::InteropOld<IPipeline> createPipeline(Base::InteropOld<IShader> vert_shader, Base::InteropOld<IShader> frag_shader, Base::InteropOld<IImageView> target_color_attachment, Base::InteropOld<IImageView> target_dept_attachment) = 0;
        virtual void destroyPipeline(Base::InteropOld<IPipeline>) = 0;

        virtual Base::InteropOld<IFence> createFence() = 0;
        virtual void destroyFence(Base::InteropOld<IFence>) = 0;

        virtual Base::InteropOld<ISemaphore> createSemaphore() = 0;
        virtual void destroySemaphore(Base::InteropOld<ISemaphore>) = 0;

        virtual Base::InteropOld<IBuffer> createBuffer(size_t size, BufferUsageBitFlags buffer_usage, BufferAllocationFlags allocation_flag, MemoryUsage memory_usage) = 0;
        virtual void destroyBuffer(Base::InteropOld<IBuffer>) = 0;

        virtual Base::InteropOld<IDescriptorPool> createDescriptorPool(size_t capacity) = 0;
        virtual void destroyDescriptorPool(Base::InteropOld<IDescriptorPool>) = 0;

        virtual void waitIdle() = 0;
    };
}