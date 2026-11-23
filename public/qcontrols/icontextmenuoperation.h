//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The operation a tool's context menu item runs
//
//===========================================================================//

#ifndef ICONTEXTMENUOPERATION_H
#define ICONTEXTMENUOPERATION_H
#ifdef _WIN32
#pragma once
#endif

#include "tier0/platform.h"

//-----------------------------------------------------------------------------
// What a context menu item does when it is chosen. The menu's action owns the
// operation and deletes it with the action
//-----------------------------------------------------------------------------
abstract_class IContextMenuOperation
{
public:
	virtual ~IContextMenuOperation() {}
	// AMNOTE: Runs the operation; the action calls it when it is triggered
	virtual void unk101() = 0;
};

#endif // ICONTEXTMENUOPERATION_H
