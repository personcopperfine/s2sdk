//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: Handle of an element of the datamodel
//
//===========================================================================//

#ifndef DMELEMENTHANDLE_H
#define DMELEMENTHANDLE_H
#ifdef _WIN32
#pragma once
#endif

#include "tier0/platform.h"

// AMNOTE: 23-bit index into the datamodel's handle table, the upper 9 bits are the slot's serial
enum DmElementHandle_t : uint32
{
	DMELEMENT_HANDLE_INVALID = 0xffffffff
};

#endif // DMELEMENTHANDLE_H
