//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: Target of the tools' input bindings (editor apps, sessions, tool widgets)
//
//===========================================================================//

#ifndef IBINDTARGET_H
#define IBINDTARGET_H
#ifdef _WIN32
#pragma once
#endif

#include "tier0/platform.h"

class CBaseBindTargetDescriptor;

abstract_class IBindTarget
{
public:
	virtual ~IBindTarget() = 0;
	virtual void unk101() = 0;
	virtual void unk102() = 0;
	virtual void unk103() = 0;
	virtual int unk104() = 0;
	// AMNOTE: Returns the class's static descriptor of its bindable commands
	virtual CBaseBindTargetDescriptor *unk105() = 0;
	virtual IBindTarget *unk106() = 0;
	virtual IBindTarget *unk107() = 0;
	// AMNOTE: Returns m_unk001, computed on the first call
	virtual int unk108() = 0;

public:
	// AMNOTE: -1 until unk108 computes it
	int m_unk001;
};

#endif // IBINDTARGET_H
