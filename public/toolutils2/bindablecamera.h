//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The camera of a tools view, the target of the Camera input bindings
//
//===========================================================================//

#ifndef BINDABLECAMERA_H
#define BINDABLECAMERA_H
#ifdef _WIN32
#pragma once
#endif

#include "toolutils2/ibindtarget.h"
#include "toolutils2/ibindablecamerascene.h"
#include "toolutils2/itoolrenderableviewhost.h"
#include "mathlib/camera.h"
#include "mathlib/vector2d.h"
#include "tier0/platform.h"

// AMNOTE: Incomplete class, only the camera, the scene and the movement state are known
class CBindableCamera : public IBindTarget
{
public:
	virtual ~CBindableCamera();
	// AMNOTE: The Camera command contexts, which differ for an orthographic camera
	virtual int unk104() override;
	virtual CBaseBindTargetDescriptor *unk105() override;

public:
	bool m_unk011;
	uint8 m_unk012;
	// AMNOTE: Set while a held mouse camera mode has the mouse, cleared when it ends
	bool m_unk013;
	// AMNOTE: Both 2 until a mouse camera mode starts, which writes the cursor position in view coordinates here
	Vector2D m_unk014;
	bool m_unk015;
	// AMNOTE: The move speed scale was changed from its default
	bool m_unk016;
	// AMNOTE: The move speed scale, 1 by default
	float m_unk017;
	float m_unk018;
	bool m_unk019;
	uint8 m_unk0110;
	// AMNOTE: The 3D mouse control is toggled on
	bool m_unk0111;
	bool m_unk0112;
	uint8 m_unk0113[20];
	CFrustum m_unk0114;
	CFrustum m_unk0115;
	int m_unk0116;
	int m_unk0117;
	int m_unk0118;
	uint8 m_unk0119[36];
	// AMNOTE: The camera the view renders with; a field of view of -1 in its frustum makes it orthographic
	ToolCameraUnk_t m_unk0120;
	// AMNOTE: The view the camera moves through
	IBindableCameraScene *m_pScene;
	uint8 m_unk111[85];
	// AMNOTE: Lock camera height
	bool m_unk112;
	uint8 m_unk113[34];
};

#endif // BINDABLECAMERA_H
