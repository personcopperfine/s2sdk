//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The model editor tool (ModelDoc): the base of the viewport tools
//
//===========================================================================//

#ifndef MODELDOC_EDITOR_TOOL_H
#define MODELDOC_EDITOR_TOOL_H
#ifdef _WIN32
#pragma once
#endif

#include "mapdoclib/mapnode.h"
#include "qcontrols/toolcontextmenuitem.h"
#include "toolutils2/ibindtarget.h"
#include "toolutils2/itoolrenderableviewhost.h"
#include "tier0/utlvector.h"
#include "tier0/platform.h"

class CModelDocEditorSession;
class QCursor;

// AMNOTE: Incomplete class, only the session and the active flag are known. The base of the viewport tools a session
// owns (selection, picker, vertex attachment and the game preview's grab, shoot and spawn tools); the session's active
// tool gets the viewport's input
class CBaseModelDocEditorTool : public IBindTarget, public IToolRenderCallbacks
{
public:
	// AMNOTE: The tool's index in the session's tools (CModelDocEditorSession::m_unk2222). Its arguments are not proven:
	// no body reads one and no call site was found
	virtual int unk011() = 0;
	// AMNOTE: Attaches the tool to pSession and registers its IToolRenderCallbacks with the session window's scene
	virtual void unk012( CModelDocEditorSession *pSession );
	// AMNOTE: The tool became the session's active tool
	virtual void unk013();
	// AMNOTE: The tool stopped being the session's active tool
	virtual void unk014();
	// AMNOTE: The session's document was replaced (new, load, reload, the Compile Debugger's step document)
	virtual void unk015() {}
	// AMNOTE: A context menu opens over the viewport
	virtual void unk016() {}
	// AMNOTE: Once per session frame; pHits is the CUtlVector of 80-byte hit records under the cursor
	virtual void unk017( void *pHits ) {}
	// AMNOTE: The object under the cursor, which the session's frame keeps and redraws
	virtual void *unk018() { return NULL; }
	// AMNOTE: The cursor of the viewport, NULL for the viewport's own
	virtual QCursor *unk019() { return NULL; }
	// AMNOTE: Asked for an object the session gives render flags; true sets one of them
	virtual bool unk0110( void *pUnk ) { return false; }
	virtual void GetContextMenuCommands( IToolRenderableViewHost *pViewHost, CUtlVector< ToolContextMenuItem_t > *pItems ) {}

public:
	// AMNOTE: Set by unk012
	CModelDocEditorSession *m_pSession;
	// AMNOTE: Set by unk013, cleared by unk014
	bool m_unk111;
	// AMNOTE: The render proxy that registers the tool's IToolRenderCallbacks with the session window's scene
	uint64 m_unk112[13];
};

#endif // MODELDOC_EDITOR_TOOL_H
