// © 2021 NVIDIA Corporation

// Goal: wrapping native WebGPU objects into NRI objects

#pragma once

#define NRI_WRAPPER_WEBGPU_H 1

#include "NRIDeviceCreation.h"

NonNriForwardStructPtr(WGPUDevice);
NonNriForwardStructPtr(WGPUSurface);
NonNriForwardStructPtr(WGPUTexture);
NonNriForwardStructPtr(WGPUTextureView);
NonNriForwardStructPtr(WGPUBuffer);
NonNriForwardStructPtr(WGPUCommandBuffer);
NonNriForwardStructPtr(WGPUCommandEncoder);
enum WGPUTextureFormat;

NriNamespaceBegin

NriStruct(DeviceCreationWebGPUDesc) {
    WGPUDevice webgpuDevice;
    NriOptional Nri(CallbackInterface) callbackInterface;
    NriOptional Nri(AllocationCallbacks) allocationCallbacks;

    // Switches (disabled by default)
    bool enableNRIValidation; // embedded validation layer, checks for NRI specifics};
};

NriStruct(CommandBufferWebGPUDesc) {
    WGPUCommandBuffer webgpuCommandBuffer;
    NriOptional WGPUCommandEncoder webgpuCommandEncoder;
};

NriStruct(BufferWebGPUDesc) {
    WGPUBuffer webgpuBuffer;
    const NriPtr(BufferDesc) desc;  // not all information can be retrieved from the resource if not provided
};

NriStruct(TextureWebGPUDesc) {
    WGPUTexture webgpuTexture;
    NriOptional WGPUTextureFormat format;  // must be provided "as a compatible typed format" if the resource is typeless
};

// Threadsafe: yes
NriStruct(WrapperWebGPUInterface) {
    Nri(Result) (NRI_CALL *CreateCommandBufferWebGPU)    (NriRef(Device) device, const NriRef(CommandBufferWebGPUDesc) commandBufferWebGPUDesc, NriOut NriRef(CommandBuffer*) commandBuffer);
    Nri(Result) (NRI_CALL *CreateBufferWebGPU)           (NriRef(Device) device, const NriRef(BufferWebGPUDesc) bufferWebGPUDesc, NriOut NriRef(Buffer*) buffer);
    Nri(Result) (NRI_CALL *CreateTextureWebGPU)          (NriRef(Device) device, const NriRef(TextureWebGPUDesc) textureWebGPUDesc, NriOut NriRef(Texture*) texture);
};

NRI_API Nri(Result) NRI_CALL nriCreateDeviceFromWebGPUDevice(const NriRef(DeviceCreationWebGPUDesc) deviceDesc, NriOut NriRef(Device*) device);

NriNamespaceEnd
