//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The model editor tool (ModelDoc): application and document session
//
//===========================================================================//

#ifndef MODELDOC_EDITOR_APP_H
#define MODELDOC_EDITOR_APP_H
#ifdef _WIN32
#pragma once
#endif

#include "toolutils2/baseeditorapp.h"
#include "toolutils2/baseeditorsession.h"
#include "toolutils2/ibindtarget.h"
#include "toolutils2/itoolsresourcelistener.h"

class CModelDoc;
class CQModelDocEditorWnd;

abstract_class IAssetFingerprintListener
{
public:
	virtual void unk001() = 0;
};

// AMNOTE: Incomplete class, only the window, document and asset members are known
class CModelDocEditorSession : public CSimpleBaseEditorSession, public IBindTarget, public IAssetFingerprintListener, public IToolsResourceListener
{
public:
	uint8 m_unk021[136];
	CQModelDocEditorWnd *m_pMainWnd;
	// AMNOTE: Replaced on every load and reload
	CModelDoc *m_pDoc;
	uint8 m_unk121[2776];
	// AMNOTE: Asset system object of the session's file, NULL when the file has none
	void *m_pAsset;
	uint8 m_unk221[1160];
};

// AMNOTE: Incomplete class, its own members are not known
class CModelDocEditorApp : public CBaseEditorSeparateWindowApp
{
public:
	uint8 m_unk021[560];
};

#endif // MODELDOC_EDITOR_APP_H
