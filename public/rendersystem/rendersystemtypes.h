//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose:
//
// $NoKeywords: $
//
//===========================================================================//

#ifndef RENDERSYSTEMTYPES_H
#define RENDERSYSTEMTYPES_H

#ifdef _WIN32
#pragma once
#endif

#include "tier0/platform.h"
#include "tier0/basetypes.h"

enum RenderMultisampleType_t : uint8
{
	RENDER_MULTISAMPLE_INVALID = 0xFF,
	RENDER_MULTISAMPLE_NONE = 0,
	RENDER_MULTISAMPLE_2X,
	RENDER_MULTISAMPLE_4X,
	RENDER_MULTISAMPLE_6X,
	RENDER_MULTISAMPLE_8X,
	RENDER_MULTISAMPLE_16X,
	RENDER_MULTISAMPLE_TYPE_COUNT
};

DECLARE_POINTER_HANDLE(SwapChainHandle_t);
DECLARE_POINTER_HANDLE(VertexBufferHandle_t);
DECLARE_POINTER_HANDLE(IndexBufferHandle_t);
DECLARE_POINTER_HANDLE(OsSpecificWindowHandle_t);
DECLARE_POINTER_HANDLE(RenderQueryHandle_t);
DECLARE_POINTER_HANDLE(RsRasterizerStateHandle_t);
DECLARE_POINTER_HANDLE(RsDepthStencilStateHandle_t);
DECLARE_POINTER_HANDLE(RsBlendStateHandle_t);
DECLARE_POINTER_HANDLE(RenderInputLayout_t);
DECLARE_POINTER_HANDLE(RenderResourceHandle_t);
DECLARE_POINTER_HANDLE(RenderBufferHandle_t);
DECLARE_POINTER_HANDLE(PooledIndexBufferHandle_t);
DECLARE_POINTER_HANDLE(ConstantBufferHandle_t);
DECLARE_POINTER_HANDLE(RenderShaderHandle_t);
DECLARE_POINTER_HANDLE(RenderSemaphoreHandle_t);
DECLARE_POINTER_HANDLE(RenderDescriptorSetHandle_t);
DECLARE_POINTER_HANDLE(SamplerStateHandle_t);
DECLARE_POINTER_HANDLE(RenderBLASHandle_t);
DECLARE_POINTER_HANDLE(RenderTLASHandle_t);
DECLARE_POINTER_HANDLE(RenderRayTracePipelineHandle_t);

// AMNOTE: Weak handle to a resource binding; must stay trivially copyable.
class HRenderTexture
{
public:
	const void *m_pBinding;
};

struct RenderViewport_t
{
	int m_nVersion;
	int m_nTopLeftX;
	int m_nTopLeftY;
	int m_nWidth;
	int m_nHeight;
	float m_flMinZ;
	float m_flMaxZ;
};

#endif // RENDERSYSTEMTYPES_H
