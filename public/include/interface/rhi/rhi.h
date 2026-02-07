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
        virtual Interface::Window::IWindow* getAttachedWindow() = 0;
    };

    class IRenderInstance
    {
    public:
        virtual std::vector<std::string>& getHardwareInfomations() = 0;
        virtual IRenderSurface* createSurface(Interface::Window::IWindow* window) = 0;
        virtual void destroySurface(IRenderSurface*) = 0;

        virtual IRenderDevice* createDevice(size_t hardware_index, IRenderSurface* surface) = 0;
        virtual void destroyDevice(IRenderDevice*) = 0;
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
        virtual std::vector<IImageView*>& getImageViews() = 0;
        virtual std::uint32_t acquireNextImageIndex(ISemaphore*) = 0;
        virtual bool isLost() = 0;
    };

    class IImage
    {
    public:
        virtual size_t getMemorySize() = 0;
        virtual IImageView* getImageView() = 0;
        virtual IImageSampler* getImageSampler() = 0;
    };

    class IShader
    {

    };

    class IDescriptorSet
    {
    public:
        virtual void bindBuffer(size_t bind_index, IBuffer*, size_t offset, size_t size) = 0;
        virtual void bindImage(size_t bind_index, IImage*) = 0;
    };

    class IDescriptorPool
    {
    public:
        virtual IDescriptorSet* allocateDescriptorSet(IPipeline* pipeline) = 0;
        virtual void freeDescriptorSet(IDescriptorSet*) = 0;
    };

        class ICommandBuffer
    {
    public:
        virtual void reset() = 0;

        virtual void begin() = 0;
        virtual void end() = 0;

        virtual void beginRenderPass(IPipeline*, IFramebuffer*) = 0;
        virtual void endRenderPass() = 0;

        virtual void bindVertexBuffer(IBuffer*, uint32_t offset) = 0;
        virtual void bindIndexBuffer(IBuffer*, uint32_t offset) = 0;

        virtual void bindPipeline(IPipeline*) = 0;

        virtual void draw(std::uint32_t vertex_count, std::uint32_t instance_count, std::uint32_t first_vertex, std::uint32_t first_instance) = 0;
        virtual void drawIndexed(uint32_t index_count, uint32_t instance_count, uint32_t first_index, int32_t vertex_offset, uint32_t first_instance) = 0;

        virtual void bindDescriptorSets(IPipeline*, IDescriptorSet*) = 0;

        virtual void copyBuffer(IBuffer*, IBuffer*, std::uint32_t) = 0;
        virtual void copyBufferToImage(IBuffer*, IImage*) = 0;
        virtual void prepareDepthImage(IImage* depth_image) = 0;
    };

    class ICommandPool
    {
    public:
        virtual ICommandBuffer* allocateCommandBuffer() = 0;
        virtual void freeCommandBuffer(ICommandBuffer*) = 0;
    };

    class ICommandQueue
    {
    public:
        virtual ICommandPool* createCommandPool() = 0;
        virtual void destroyCommandPool(ICommandPool*) = 0;
        virtual void waitIdle() = 0;
    };

    class IRenderCommandQueue
        : public ICommandQueue
    {
    public:
        virtual void submitCommand(ICommandBuffer*, IFence*, ISemaphore* wait_semaphore, ISemaphore* signal_semaphore) = 0;
        virtual void submitCommand(ICommandBuffer*) = 0;
    };

    class IPresentCommandQueue
        : public ICommandQueue
    {
    public:
        virtual void present(ISwapchain*, std::uint32_t swapchain_image_index, IFramebuffer*, ISemaphore* signal_semaphore) = 0;
    };

    class IRenderDevice
    {
    public:
        virtual Format findSupportedFormat(const std::vector<Format>& candidate_formats, ImageTiling, FormatFeatureFlags) = 0;

        virtual IRenderCommandQueue* getGraphicsCommandQueue() = 0;
        virtual IPresentCommandQueue* getPresentCommandQueue() = 0;

        virtual ISwapchain* createSwapchain(IRenderSurface*) = 0;
        virtual void destroySwapchain(ISwapchain*) = 0;

        virtual IImage* createImage(std::uint32_t width, std::uint32_t height, Format format, ImageAspectFlags aspect, ImageTiling tiling, ImageUsageFlags usage, MemoryUsage memory_usage) = 0;
        virtual void destroyImage(IImage*) = 0;

        virtual IFramebuffer* createFramebuffer(IPipeline*, ISwapchain*, const std::vector<IImageView*>& attachment_array) = 0;
        virtual void destroyFramebuffer(IFramebuffer*) = 0;

        virtual IShader* createShader(void* buf, size_t buf_size) = 0;
        virtual void destroyShader(IShader*) = 0; 

        //TODO: remove target_image_view from here
        virtual IPipeline* createPipeline(IShader* vert_shader, IShader* frag_shader, IImageView* target_color_attachment, IImageView* target_dept_attachment) = 0;
        virtual void destroyPipeline(IPipeline*) = 0;

        virtual IFence* createFence() = 0;
        virtual void destroyFence(IFence*) = 0;

        virtual ISemaphore* createSemaphore() = 0;
        virtual void destroySemaphore(ISemaphore*) = 0;

        virtual IBuffer* createBuffer(size_t size, BufferUsageBitFlags buffer_usage, BufferAllocationFlags allocation_flag, MemoryUsage memory_usage) = 0;
        virtual void destroyBuffer(IBuffer*) = 0;

        virtual IDescriptorPool* createDescriptorPool(size_t capacity) = 0;
        virtual void destroyDescriptorPool(IDescriptorPool*) = 0;

        virtual void waitIdle() = 0;
    };
}