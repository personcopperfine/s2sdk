//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The material system ("VMaterialSystem2_001")
//
//===========================================================================//

#ifndef IMATERIALSYSTEM2_H
#define IMATERIALSYSTEM2_H
#ifdef _WIN32
#pragma once
#endif

#include "tier0/platform.h"

// AMNOTE: Registered with the material system; called when the shaders are reloaded
abstract_class IShaderReloadListener
{
public:
	// AMNOTE: No caller is known, so their arguments are not known
	virtual void unk001() = 0;
	virtual void unk002() = 0;
};

#endif // IMATERIALSYSTEM2_H
