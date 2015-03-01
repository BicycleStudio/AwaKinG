#ifndef __ERROR_DEFINES_H
#define __ERROR_DEFINES_H

// Error Defines
#define ED_UNDEFINED "Undefined error"
#define ED_RENDER "Render error!"
#define ED_ENGINE "Engine error!"
#define ED_INPUT "Input error!"
#define ED_MAP "Map error!"

// Render defines
#define EDR_DEVICE_SWAP_CHAIN "Creation of device & swapChain failed"
#define EDR_GET_BACKBUFFER "Getting backbuffer of swapChain failed"
#define EDR_CREATE_RTV "Creation of RenderTargetView failed"
#define EDR_CREATE_DS "Creation of depth stencil texture failed"
#define EDR_CREATE_DSV "Creation of depth stencil view failed"
#define EDR_RESIZE_BUFFERS "ResizeBuffers error"
#define EDR_HLSL_PATH "Shader path error. File does not exist!"
#define EDR_CREATE_RS "Creation of RasterizerState failed"
#define EDR_CREATE_SS "Creation of SamplerState failed"
#define EDR_CREATE_CB "Creation of ConstantBuffer failed"
#define EDR_CREATE_VSHADER "Creation of VertexShader failed"
#define EDR_CREATE_PSHADER "Creation of PixelShader failed"
#define EDR_CREATE_GSHADER "Creation of GeometryShader failed"
#define EDR_CREATE_DSHADER "Creation of DomainShader failed"
#define EDR_CREATE_HSHADER "Creation of HullShader failed"
#define EDR_CREATE_CSHADER "Creation of ComputeShader failed"

#endif // __ERROR_DEFINES_H 