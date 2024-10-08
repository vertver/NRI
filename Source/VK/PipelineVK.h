// © 2021 NVIDIA Corporation

#pragma once

namespace nri {

struct DeviceVK;
struct PipelineLayoutVK;

struct PipelineVK {
    inline PipelineVK(DeviceVK& device)
        : m_Device(device) {
    }

    inline operator VkPipeline() const {
        return m_Handle;
    }

    inline DeviceVK& GetDevice() const {
        return m_Device;
    }

    inline VkPipelineBindPoint GetBindPoint() const {
        return m_BindPoint;
    }

    inline const DepthBiasDesc& GetDepthBias() const {
        return m_DepthBias;
    }

    ~PipelineVK();

    Result Create(const GraphicsPipelineDesc& graphicsPipelineDesc);
    Result Create(const ComputePipelineDesc& computePipelineDesc);
    Result Create(const RayTracingPipelineDesc& rayTracingPipelineDesc);
    Result Create(VkPipelineBindPoint bindPoint, VKNonDispatchableHandle vkPipeline);

    //================================================================================================================
    // NRI
    //================================================================================================================

    void SetDebugName(const char* name);
    Result WriteShaderGroupIdentifiers(uint32_t baseShaderGroupIndex, uint32_t shaderGroupNum, void* buffer) const;

private:
    Result SetupShaderStage(VkPipelineShaderStageCreateInfo& stage, const ShaderDesc& shaderDesc, VkShaderModule& module);

private:
    DeviceVK& m_Device;
    VkPipeline m_Handle = VK_NULL_HANDLE;
    VkPipelineBindPoint m_BindPoint = (VkPipelineBindPoint)0;
    DepthBiasDesc m_DepthBias = {};
    bool m_OwnsNativeObjects = true;
};

} // namespace nri