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
        virtual Base::Interop::RawRef<Interface::Window::IWindow> getAttachedWindow() = 0;
    };

    class IRenderInstance
    {
    public:
        virtual std::vector<std::string>& getHardwareInfomations() = 0;
        virtual Base::Interop::RawRef<IRenderSurface> createSurface(Base::Interop::RawRef<Interface::Window::IWindowManager> window_manager, Base::Interop::RawRef<Interface::Window::IWindow> window) = 0;
        virtual void destroySurface(Base::Interop::RawRef<IRenderSurface> surface) = 0;

        virtual Base::Interop::RawRef<IRenderDevice> createDevice(size_t hardware_index, Base::Interop::RawRef<IRenderSurface> surface) = 0;
        virtual void destroyDevice(Base::Interop::RawRef<IRenderDevice> device) = 0;
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
        virtual std::vector<Base::Interop::RawRef<IImageView>>& getImageViews() = 0;
        virtual std::uint32_t acquireNextImageIndex(Base::Interop::RawRef<ISemaphore>) = 0;
        virtual bool isLost() = 0;
    };

    class IImage
    {
    public:
        virtual size_t getMemorySize() = 0;
        virtual Base::Interop::RawRef<IImageView> getImageView() = 0;
        virtual Base::Interop::RawRef<IImageSampler> getImageSampler() = 0;
    };

    class IShader
    {

    };

    class IDescriptorSet
    {
    public:
        virtual void bindBuffer(size_t bind_index, Base::Interop::RawRef<IBuffer>, size_t offset, size_t size) = 0;
        virtual void bindImage(size_t bind_index, Base::Interop::RawRef<IImage>) = 0;
    };

    class IDescriptorPool
    {
    public:
        virtual Base::Interop::RawRef<IDescriptorSet> allocateDescriptorSet(Base::Interop::RawRef<IPipeline> pipeline) = 0;
        virtual void freeDescriptorSet(Base::Interop::RawRef<IDescriptorSet>) = 0;
    };

        class ICommandBuffer
    {
    public:
        virtual void reset() = 0;

        virtual void begin() = 0;
        virtual void end() = 0;

        virtual void beginRenderPass(Base::Interop::RawRef<IPipeline>, Base::Interop::RawRef<IFramebuffer>) = 0;
        virtual void endRenderPass() = 0;

        virtual void bindVertexBuffer(Base::Interop::RawRef<IBuffer>, uint32_t offset) = 0;
        virtual void bindIndexBuffer(Base::Interop::RawRef<IBuffer>, uint32_t offset) = 0;

        virtual void bindPipeline(Base::Interop::RawRef<IPipeline>) = 0;

        virtual void draw(std::uint32_t vertex_count, std::uint32_t instance_count, std::uint32_t first_vertex, std::uint32_t first_instance) = 0;
        virtual void drawIndexed(uint32_t index_count, uint32_t instance_count, uint32_t first_index, int32_t vertex_offset, uint32_t first_instance) = 0;

        virtual void bindDescriptorSets(Base::Interop::RawRef<IPipeline>, Base::Interop::RawRef<IDescriptorSet>) = 0;

        virtual void copyBuffer(Base::Interop::RawRef<IBuffer>, Base::Interop::RawRef<IBuffer>, std::uint32_t) = 0;
        virtual void copyBufferToImage(Base::Interop::RawRef<IBuffer>, Base::Interop::RawRef<IImage>) = 0;
        virtual void prepareDepthImage(Base::Interop::RawRef<IImage> depth_image) = 0;
    };

    class ICommandPool
    {
    public:
        virtual Base::Interop::RawRef<ICommandBuffer> allocateCommandBuffer() = 0;
        virtual void freeCommandBuffer(Base::Interop::RawRef<ICommandBuffer>) = 0;
    };

    class ICommandQueue
    {
    public:
        virtual Base::Interop::RawRef<ICommandPool> createCommandPool() = 0;
        virtual void destroyCommandPool(Base::Interop::RawRef<ICommandPool>) = 0;
        virtual void waitIdle() = 0;
    };

    class IRenderCommandQueue
        : public ICommandQueue
    {
    public:
        virtual void submitCommand(Base::Interop::RawRef<ICommandBuffer>, Base::Interop::RawRef<IFence>, Base::Interop::RawRef<ISemaphore> wait_semaphore, Base::Interop::RawRef<ISemaphore> signal_semaphore) = 0;
        virtual void submitCommand(Base::Interop::RawRef<ICommandBuffer>) = 0;
    };

    class IPresentCommandQueue
        : public ICommandQueue
    {
    public:
        virtual void present(Base::Interop::RawRef<ISwapchain>, std::uint32_t swapchain_image_index, Base::Interop::RawRef<IFramebuffer>, Base::Interop::RawRef<ISemaphore> signal_semaphore) = 0;
    };

    class IRenderDevice
    {
    public:
        virtual Format findSupportedFormat(const std::vector<Format>& candidate_formats, ImageTiling, FormatFeatureFlags) = 0;

        virtual Base::Interop::RawRef<IRenderCommandQueue> getGraphicsCommandQueue() = 0;
        virtual Base::Interop::RawRef<IPresentCommandQueue> getPresentCommandQueue() = 0;

        virtual Base::Interop::RawRef<ISwapchain> createSwapchain(Base::Interop::RawRef<IRenderSurface>) = 0;
        virtual void destroySwapchain(Base::Interop::RawRef<ISwapchain>) = 0;

        virtual Base::Interop::RawRef<IImage> createImage(std::uint32_t width, std::uint32_t height, Format format, ImageAspectFlags aspect, ImageTiling tiling, ImageUsageFlags usage, MemoryUsage memory_usage) = 0;
        virtual void destroyImage(Base::Interop::RawRef<IImage>) = 0;

        virtual Base::Interop::RawRef<IFramebuffer> createFramebuffer(Base::Interop::RawRef<IPipeline>, Base::Interop::RawRef<ISwapchain>, std::vector<Base::Interop::RawRef<IImageView>>& attachment_array) = 0;
        virtual void destroyFramebuffer(Base::Interop::RawRef<IFramebuffer>) = 0;

        virtual Base::Interop::RawRef<IShader> createShader(void* buf, size_t buf_size) = 0;
        virtual void destroyShader(Base::Interop::RawRef<IShader>) = 0; 

        //TODO: remove target_image_view from here
        virtual Base::Interop::RawRef<IPipeline> createPipeline(Base::Interop::RawRef<IShader> vert_shader, Base::Interop::RawRef<IShader> frag_shader, Base::Interop::RawRef<IImageView> target_color_attachment, Base::Interop::RawRef<IImageView> target_dept_attachment) = 0;
        virtual void destroyPipeline(Base::Interop::RawRef<IPipeline>) = 0;

        virtual Base::Interop::RawRef<IFence> createFence() = 0;
        virtual void destroyFence(Base::Interop::RawRef<IFence>) = 0;

        virtual Base::Interop::RawRef<ISemaphore> createSemaphore() = 0;
        virtual void destroySemaphore(Base::Interop::RawRef<ISemaphore>) = 0;

        virtual Base::Interop::RawRef<IBuffer> createBuffer(size_t size, BufferUsageBitFlags buffer_usage, BufferAllocationFlags allocation_flag, MemoryUsage memory_usage) = 0;
        virtual void destroyBuffer(Base::Interop::RawRef<IBuffer>) = 0;

        virtual Base::Interop::RawRef<IDescriptorPool> createDescriptorPool(size_t capacity) = 0;
        virtual void destroyDescriptorPool(Base::Interop::RawRef<IDescriptorPool>) = 0;

        virtual void waitIdle() = 0;
    };
}




