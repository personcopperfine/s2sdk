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
#include "tier0/errorlistener.h"

class CModelDoc;
class CQModelDocEditorWnd;

abstract_class IAssetFingerprintListener
{
public:
	virtual void unk001() = 0;
};

// AMNOTE: Incomplete class, its own members are not known. Collects the errors of a document's nodes
class CModelDocAnalysis : public IErrorListener
{
public:
	virtual void ReportMessage( const ErrorListenerMessage_t &message ) override;
	virtual bool FormatMessageLocation( const ErrorListenerMessage_t &message, CBufferString &sOutLocation, const char *pszSuffix ) override;
	virtual const char *GetSourceName( int *pLineAndColumn ) override;
	virtual bool AppendContextPath( CBufferString &sOutContextPath ) override;
	virtual ErrorContextHandle_t PushContext( PRINTF_FORMAT_STRING const char *pszFormat, ... ) FMTFUNCTION( 2, 3 ) override;
	virtual void PopContext( int nContextLength ) override;

public:
	uint8 m_unk001[144];
};

// AMNOTE: Incomplete class, only the window, document, asset and analysis members are known
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
	uint8 m_unk221[920];
	// AMNOTE: The error listener the session's compile reports to
	CModelDocAnalysis m_Analysis;
	uint8 m_unk321[88];
};

// AMNOTE: Incomplete class, its own members are not known
class CModelDocEditorApp : public CBaseEditorSeparateWindowApp
{
public:
	uint8 m_unk021[560];
};

#endif // MODELDOC_EDITOR_APP_H
