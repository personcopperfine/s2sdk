//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: A view the Workshop Tools render a scene into
//
//===========================================================================//

#ifndef ITOOLRENDERABLEVIEWHOST_H
#define ITOOLRENDERABLEVIEWHOST_H
#ifdef _WIN32
#pragma once
#endif

#include "mathlib/camera.h"
#include "tier0/platform.h"

// AMNOTE: Placeholder name; the camera of a view. Starts with 80 bytes of its own (among them the viewport width and height, both int)
struct ToolCameraUnk_t
{
	uint8 m_unk001[80];
	CFrustum m_Frustum;
};

// AMNOTE: Placeholder for an 8-byte value returned by IToolRenderableViewHost::unk101
struct ToolRenderableViewHostUnk8_t
{
	uint64 m_unk001;
};

abstract_class IToolRenderableViewHost
{
public:
	virtual void *unk001() = 0;
	// AMNOTE: Returns the same as unk001
	virtual void *unk002() = 0;
	virtual int unk003() = 0;
	virtual bool unk004() = 0;
	virtual bool unk005() = 0;
	// AMNOTE: Returns the same as GetCamera
	virtual ToolCameraUnk_t *unk006() = 0;
	virtual ToolCameraUnk_t *GetCamera() = 0;
	// AMNOTE: Projects a world position to the view
	virtual bool unk101( float *, void * ) = 0;
	virtual void unk102() = 0;
	// AMNOTE: Writes the viewport rectangle
	virtual void unk103( int * ) = 0;
	virtual ToolRenderableViewHostUnk8_t unk104() = 0;
	virtual void unk105( void *, void * ) = 0;
	virtual void unk106( void *, void * ) = 0;
	virtual int unk107( float *, int *, int, int, int * ) = 0;
	// AMNOTE: Copies 208 bytes to the second argument on success
	virtual bool unk108( void *, void * ) = 0;
	// AMNOTE: nTag is an 8-character tag ("tagvis", "viewport")
	virtual bool unk109( uint64 nTag, void *pOut ) = 0;
	virtual int unk1010() = 0;
	virtual void *unk1011() = 0;
};

#endif // ITOOLRENDERABLEVIEWHOST_H
