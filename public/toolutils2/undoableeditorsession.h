//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: Editor sessions that keep an undo history of their document, and the app that drives their undo
//
//===========================================================================//

#ifndef UNDOABLEEDITORSESSION_H
#define UNDOABLEEDITORSESSION_H
#ifdef _WIN32
#pragma once
#endif

#include "tier0/utlstring.h"
#include "tier0/platform.h"
#include "toolutils2/baseeditorapp.h"
#include "toolutils2/baseeditorsession.h"
#include "toolutils2/undohistory.h"

// AMNOTE: Incomplete class. Its new, load, reload and save are built on unk033 to unk035: a load and a reload clear both
// histories first. Its IUndoDoc methods do nothing
template < class TBaseSession, class TApp >
class CUndoableEditorSessionCommon : public TBaseSession, public IUndoDoc
{
public:
	// AMNOTE: False refuses an undo or redo, and skips unk036 and unk032 after one. The base returns true
	virtual bool unk031() = 0;
	// AMNOTE: Called after an undo or redo, once unk036 has run. Empty in the base
	virtual void unk032() = 0;
	// AMNOTE: Called after a new document is set up and after a load; false makes the load fail. The base returns true
	virtual bool unk033() = 0;
	// AMNOTE: Writes the document to pszNewPath, once its directory exists; the reason goes into pError when it fails
	virtual bool unk034( const char *pszOldPath, const char *pszNewPath, bool bUnk, CUtlString *pError ) = 0;
	// AMNOTE: Reads the document from pszFileName; the reason goes into pErrors when it fails
	virtual bool unk035( const char *pszFileName, CUtlString *pErrors ) = 0;
	// AMNOTE: Calls SetModified( true )
	virtual void unk036() = 0;

public:
	// AMNOTE: 50 steps in the post-processing editor; the redo history is its partner
	CUndoHistory *m_pUndoHistory;
	CUndoHistory *m_unk131;
};

// AMNOTE: Adds nothing to its base
class CUndoableEditorSessionBase : public CUndoableEditorSessionCommon< CSimpleSharedWindowEditorSession, CBaseEditorSharedWindowApp >
{
};

// AMNOTE: Incomplete class. Its IUndoListener method takes notify code 1 (an undo or redo was done): it asks the active
// session's unk031, then calls its unk036 and unk032
template < class TSession, class TMainWnd >
class CEditorAppWithUndo : public CSimpleEditorSharedWindowApp< TSession, TMainWnd >, public IUndoListener
{
};

#endif // UNDOABLEEDITORSESSION_H
