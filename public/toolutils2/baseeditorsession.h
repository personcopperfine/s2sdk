//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: Base classes of a document open in a Workshop Tools editor application
//
//===========================================================================//

#ifndef BASEEDITORSESSION_H
#define BASEEDITORSESSION_H
#ifdef _WIN32
#pragma once
#endif

#include "tier0/utlstring.h"
#include "tier0/utlvector.h"
#include "tier0/platform.h"

class CBaseEditorApp;
class CBaseEditorSharedWindowApp;
class QWidget;

// AMNOTE: Incomplete class
class CBaseEditorSession
{
public:
	virtual ~CBaseEditorSession() = 0;
	// AMNOTE: Asks to save unsaved changes in a modal dialog, none when IsModified is false; returns 0 when cancelled,
	// 1 when there was nothing to save. With true, discarding the changes also calls SetModified( false )
	virtual int unk101( bool bUnk ) = 0;
	virtual int unk102() = 0;
	// AMNOTE: Sets up a new untitled document named pszName
	virtual bool unk103( const char *pszName ) = 0;
	virtual bool unk104() = 0;
	// AMNOTE: Like unk103, also given a second string
	virtual bool unk105( const char *pszName, const char *pszUnk ) = 0;
	// AMNOTE: Loads pszFileName; returns 2 when loaded, 3 when loaded with the errors written to pErrors,
	// 4 when loaded without a path, anything else when it failed
	virtual int unk106( const char *pszFileName, CUtlString *pErrors ) = 0;
	// AMNOTE: Reloads the document from its file
	virtual void ReloadDocument() = 0;
	virtual void unk201() = 0;
	virtual void unk202() = 0;
	virtual bool unk203( const char *pszFileName ) = 0;
	virtual bool IsModified() = 0;
	virtual void SetModified( bool bModified ) = 0;
	// AMNOTE: "" for an untitled session
	virtual const char *GetPath() = 0;
	// AMNOTE: Writes the default file name for a new file into pOut
	virtual bool unk301( CUtlString *pOut ) = 0;
	virtual void unk302( bool bUnk ) = 0;
	virtual bool unk303() = 0;
	virtual bool unk304() = 0;
	virtual bool Save( const char *pszOldPath, const char *pszNewPath, bool bUnk, bool bUnk2 ) = 0;
	virtual void unk401( CUtlString *pOut ) = 0;
	// AMNOTE: True when pszFileName is the session's file
	virtual bool unk402( const char *pszFileName ) = 0;
	// AMNOTE: Asked before the session closes; false keeps it open. The base returns unk101( true ) != 0
	virtual bool unk403() = 0;
	// AMNOTE: The window the session is shown in
	virtual QWidget *unk404() = 0;
	virtual void unk405() = 0;
	// AMNOTE: Adds the session's file to version control and refreshes its file status; false when the add fails.
	// Hammer also offers to add the referenced maps that are not under version control
	virtual bool unk406() = 0;
	virtual void unk407() = 0;

public:
	CBaseEditorApp *m_unk001;
	// AMNOTE: The file is read-only: in a read-only search path or not writable
	bool m_unk002;
	// AMNOTE: The file is in a search path that cannot be modified
	bool m_unk003;
	// AMNOTE: The file is under version control; m_unk005 is its version control state, m_unk006 is set when a newer
	// revision exists. unk202 is called when one of the three changes
	bool m_unk004;
	int m_unk005;
	bool m_unk006;
	// AMNOTE: The session has no file yet
	bool m_bIsNew;
	// AMNOTE: m_unk101 to m_unk103 are the version control helper of the session
	CBaseEditorApp *m_unk101;
	void *m_unk102;
	CUtlString m_unk103;
	// AMNOTE: Counts the path changes
	int m_unk104;
	// AMNOTE: Told when the path changes and when the session is destroyed
	CUtlVector< void * > m_unk105;
};

class CSimpleBaseEditorSession : public CBaseEditorSession
{
public:
	CUtlString m_Path;
	bool m_bModified;
	bool m_unk111;
};

class CSimpleSharedWindowEditorSession : public CSimpleBaseEditorSession
{
public:
	CBaseEditorSharedWindowApp *m_unk021;
};

#endif // BASEEDITORSESSION_H
