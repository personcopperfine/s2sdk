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

#include "mathlib/vector2d.h"
#include "tier0/platform.h"

abstract_class IBindableCameraScene
{
public:
	virtual void unk001() = 0;
	virtual void unk002() = 0;
	virtual void unk003() = 0;
	virtual void unk004( float ) = 0;
	virtual bool unk005( float * ) = 0;
	virtual bool unk006( void *, void *, void * ) = 0;
	virtual bool unk007() = 0;
	virtual bool unk008() = 0;
	// AMNOTE: Slots unk009-unk0016 have default bodies in the interface (unk009 returns ( 2, 2 ))
	virtual Vector2D unk009() = 0;
	virtual float unk0010() = 0;
	virtual int unk0011() = 0;
	virtual int unk0012() = 0;
	virtual float unk0013() = 0;
	virtual float unk0014() = 0;
	virtual float unk0015() = 0;
	virtual float unk0016() = 0;
	virtual void *unk0017() = 0;
	virtual void *unk0018() = 0;
};

#endif // IBINDABLECAMERASCENE_H
