//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The post-processing editor application (ToolSystem2_001): one main window, one session per open .vpost
//
//===========================================================================//

#ifndef POSTPROCESSEDITORAPP_H
#define POSTPROCESSEDITORAPP_H
#ifdef _WIN32
#pragma once
#endif

#include "tier0/utlstring.h"
#include "tier0/platform.h"
#include "resourcesystem/resourcehandle.h"
#include "toolutils2/undoableeditorsession.h"
#include "postprocessingeditor/postprocesseditorsession.h"

class CPostProcessEditorMainWnd;
struct InfoForResourceTypeCModel;

// AMNOTE: Incomplete class, it adds no virtual of its own. The preview model and the light rig are put into every
// session's preview and are not saved in the .vpost
class CPostProcessEditorApp : public CEditorAppWithUndo< CPostProcessEditorSession, CPostProcessEditorMainWnd >
{
public:
	// AMNOTE: The name of the preview model ("models/dev/sphere.vmdl" by default) and the model, set by SetPreviewModel
	CUtlString m_unk041;
	CStrongHandle< InfoForResourceTypeCModel > m_unk042;
	// AMNOTE: The name of the preview's light rig
	CUtlString m_unk043;
};

#endif // POSTPROCESSEDITORAPP_H
