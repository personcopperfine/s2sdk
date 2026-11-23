//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: A scene a bindable camera moves through
//
//===========================================================================//

#ifndef IBINDABLECAMERASCENE_H
#define IBINDABLECAMERASCENE_H
#ifdef _WIN32
#pragma once
#endif

#include "toolutils2/itoolrenderableviewhost.h"
#include "mathlib/vector2d.h"
#include "tier0/platform.h"

abstract_class IBindableCameraScene
{
public:
	virtual void unk001() = 0;
	virtual void unk002() {}
	virtual void unk003() {}
	virtual void unk004( float flUnk ) {}
	// AMNOTE: Writes the cursor position to pPos, true when it is inside the view
	virtual bool unk005( float *pPos ) { return false; }
	virtual bool unk006( void *pUnk, void *pUnk2, void *pUnk3 ) = 0;
	virtual bool unk007() { return false; }
	virtual bool unk008() { return true; }
	virtual Vector2D unk009() { return Vector2D( 2.0f, 2.0f ); }
	virtual float unk0010() { return 1.0f; }
	virtual int unk0011() { return 1000; }
	virtual int unk0012() { return 1000; }
	virtual float unk0013() { return 2.0f; }
	virtual float unk0014() { return 96.0f; }
	virtual float unk0015() { return 200.0f; }
	virtual float unk0016() { return 16384.0f; }
	virtual void *unk0017() { return NULL; }
	// AMNOTE: The view the scene belongs to
	virtual IToolRenderableViewHost *unk0018() { return NULL; }
};

#endif // IBINDABLECAMERASCENE_H
