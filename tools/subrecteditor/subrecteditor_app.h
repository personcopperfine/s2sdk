//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The subrect editor application (ToolSystem2_001): one window per open .rect
//
//===========================================================================//

#ifndef SUBRECTEDITOR_APP_H
#define SUBRECTEDITOR_APP_H
#ifdef _WIN32
#pragma once
#endif

#include "tier0/platform.h"
#include "toolutils2/baseeditorapp.h"
#include "subrecteditor/subrecteditor_session.h"

// AMNOTE: Incomplete class, it adds no virtual of its own
class CSubrectEditorApp : public CBaseEditorSeparateWindowApp
{
public:
	// AMNOTE: The event target the sessions post their events to after their own (CSubrectEditorSession::m_unk022)
	void *m_unk021;
	// AMNOTE: A CUtlVector of the preview material of each file: pairs of CUtlString, the .rect path and the material path
	uint8 m_unk022[24];
};

#endif // SUBRECTEDITOR_APP_H
