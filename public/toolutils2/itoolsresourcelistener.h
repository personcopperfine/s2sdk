//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: Notified when tool resources change
//
//===========================================================================//

#ifndef ITOOLSRESOURCELISTENER_H
#define ITOOLSRESOURCELISTENER_H
#ifdef _WIN32
#pragma once
#endif

#include "tier0/platform.h"

abstract_class IToolsResourceListener
{
public:
	virtual int unk001() = 0;
	// AMNOTE: pResources points to an array of 32-byte entries and its 64-bit count
	virtual void unk002( const void *pResources ) = 0;
};

#endif // ITOOLSRESOURCELISTENER_H
