//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: Hammer's tool manager: one instance of every editor tool per session
//
//===========================================================================//

#ifndef TOOLMANAGER_H
#define TOOLMANAGER_H
#ifdef _WIN32
#pragma once
#endif

#include "hammer/basetool.h"
#include "toolutils2/undohistory.h"
#include "tier0/utlvector.h"
#include "tier0/platform.h"

class CHammerEditorSession;
class CToolManager;

// AMNOTE: The tool manager's undoable state. The tool ids are ToolID_t and the modes ManipulationMode_t, -1 for none
class CToolManagerUndoableState : public CBaseUndoable
{
public:
	// AMNOTE: unk001, unk002 and the destructor are the class's own; the others keep CBaseUndoable's default bodies
	virtual IUndoable *unk001() override;
	virtual void unk002( IUndoable *pSource ) override;
	virtual void unk003() override;
	virtual void unk004() override;
	virtual void unk005() override;
	virtual void unk006( bool bUnk ) override;
	virtual void unk007() override;
	virtual bool unk008() override;
	virtual void *unk009() override;
	virtual void unk0010( void *pUnk ) override;
	virtual int unk0011() override;
	virtual void unk0012() override;
	virtual ~CToolManagerUndoableState();

public:
	// AMNOTE: The manager the state belongs to, NULL in a snapshot; restoring a snapshot into it switches the manager's tool
	CToolManager *m_pToolManager;
	int m_nActiveTool;
	int m_nManipulationMode;
	// AMNOTE: The tool and mode to go back to after a temporary switch
	int m_nReturnTool;
	int m_nReturnMode;
};

// AMNOTE: Incomplete class, only the tools, the session and the state are known
class CToolManager
{
public:
	// AMNOTE: CToolEventMapRegistrationHelper< CToolManager >, the manager's event bindings
	uint64 m_unk001[6];
	// AMNOTE: Indexed by ToolID_t
	CUtlVector< CBaseTool * > m_Tools;
	CHammerEditorSession *m_pSession;
	// AMNOTE: The live state, the one undo records
	CToolManagerUndoableState m_State;
	// AMNOTE: Set while the manager switches tools
	bool m_unk101;
	// AMNOTE: QCursor[8][4], the selection cursors per select mode for no modifier, add, remove and toggle
	uint64 m_unk102[32];
};

#endif // TOOLMANAGER_H
