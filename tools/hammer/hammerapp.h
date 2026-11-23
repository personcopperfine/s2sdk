//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The Hammer application (ToolSystem2_001): one main window, one session per open map
//
//===========================================================================//

#ifndef HAMMERAPP_H
#define HAMMERAPP_H
#ifdef _WIN32
#pragma once
#endif

#include "toolutils2/baseeditorapp.h"
#include "assetbrowser/iassetbrowsersystem.h"
#include "mapdoclib/mapdoc.h"
#include "hammer/hammereditorsession.h"
#include "tier0/utlstring.h"
#include "tier0/utlvector.h"
#include "tier0/platform.h"

class CMapDocExternalToolReference;
class CQEntityReportDlgUI;
class CQHammerMainWnd;

abstract_class IEntityReportListener
{
public:
	// AMNOTE: pDialog is going away
	virtual void unk001( CQEntityReportDlgUI *pDialog ) = 0;
};

// AMNOTE: Hands map documents to other tools
abstract_class IMapDocExternalToolReferenceProvider
{
public:
	// AMNOTE: Creates a map document that keeps pUnk and returns its file reference
	virtual IMapFileReference *unk001( void *pUnk ) = 0;
	// AMNOTE: Destroys a document unk001 created
	virtual void unk002( IMapFileReference *pReference ) = 0;
};

// AMNOTE: Incomplete class, only the main window, the session lists, the dialogs and the external documents are known
class CHammerApp : public CBaseEditorSharedWindowApp, public IAssetMenuCustomCommandContext, public IEntityReportListener, public IMapDocExternalToolReferenceProvider
{
public:
	// AMNOTE: CToolEventMapRegistrationHelper< CHammerApp >, the app's event bindings
	uint64 m_unk021[6];
	CQHammerMainWnd *m_pMainWnd;
	// AMNOTE: CBindTargetProxy, the bind target the menus and toolbars use for the active session's commands
	uint64 m_unk121[3];
	// AMNOTE: The sessions whose document changed this frame
	CUtlVector< CHammerEditorSession * > m_unk122;
	CUtlString m_unk123;
	CUtlString m_unk124;
	uint64 m_unk125;
	// AMNOTE: The two entity report dialogs, NULL while closed
	CQEntityReportDlgUI *m_unk126;
	CQEntityReportDlgUI *m_unk127;
	uint8 m_unk128[56];
	// AMNOTE: A KeyValues3 table, the "Editor Session Layouts" block of the tool settings
	uint64 m_unk129[2];
	// AMNOTE: The sessions in the order they were last active, the newest last
	CUtlVector< CBaseEditorSession * > m_unk1210;
	// AMNOTE: The documents unk001 of IMapDocExternalToolReferenceProvider created
	CUtlVector< CMapDocExternalToolReference * > m_unk1211;
};

#endif // HAMMERAPP_H
