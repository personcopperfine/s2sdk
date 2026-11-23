//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: An entry of the context menu a tool fills for the asset browser
//
//===========================================================================//

#ifndef TOOLCONTEXTMENUITEM_H
#define TOOLCONTEXTMENUITEM_H
#ifdef _WIN32
#pragma once
#endif

#include "tier0/utlstring.h"

class IBindTarget;
class IContextMenuOperation;

//-----------------------------------------------------------------------------
// One entry of a menu the tools build from a list of these. The list is read in
// order and the members that apply depend on the type
//-----------------------------------------------------------------------------
struct ToolContextMenuItem_t
{
	// AMNOTE: What the entry is: 1 an action that runs m_unk002 (the menu keeps and deletes it),
	// 2 an action with the text and no command, 3 a separator, 4 a submenu with the text that takes the
	// entries up to the matching 5, 5 the end of a submenu, anything else an action of the bind
	// command m_unk004 of the target m_unk003
	int m_unk001;
	IContextMenuOperation *m_unk002;
	IBindTarget *m_unk003;
	// AMNOTE: The command's hash
	uint32 m_unk004;
	// AMNOTE: The text of the entry
	CUtlString m_unk005;
	// AMNOTE: Whether the action can be checked
	bool m_unk006;
	// AMNOTE: Whether the action starts checked
	bool m_unk007;
	// AMNOTE: Whether the entry is enabled
	bool m_unk008;
};

#endif // TOOLCONTEXTMENUITEM_H
