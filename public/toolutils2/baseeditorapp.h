//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: Base classes of the Workshop Tools editor applications (one tool module, several open documents)
//
//===========================================================================//

#ifndef BASEEDITORAPP_H
#define BASEEDITORAPP_H
#ifdef _WIN32
#pragma once
#endif

#include "assetsystem/iassetsystem.h"
#include "tier3/tier3.h"
#include "tier0/keyvalues3.h"
#include "tier0/utlstring.h"
#include "tier0/utlvector.h"
#include "toolframework2/itoolframework2.h"
#include "toolutils2/ibindtarget.h"

class CBaseEditorSession;
class QWidget;

class CBaseToolSystem2 : public CTier3AppSystem< IToolSystem2 >
{
public:
	// AMNOTE: Index of the tool in the tool framework
	uint8 m_nToolIndex;
};

// AMNOTE: Incomplete class, only the queue is known. Queues the asset system's file changes for the tool to act on
class CContentChangeWatcher : public IAssetFileListener
{
public:
	// AMNOTE: The only virtual
	virtual void unk001( void *pUnk ) override;

public:
	// AMNOTE: A CUtlVector of unknown elements
	uint64 m_unk011[3];
	uint64 m_unk012[4];
	uint64 m_unk013[4];
	// AMNOTE: The queued file changes, a CUtlVector of 48-byte records
	uint64 m_unk014[3];
	bool m_unk015;
	uint64 m_unk016[2];
};

// AMNOTE: Incomplete class
class CBaseEditorApp : public CBaseToolSystem2, public IBindTarget
{
public:
	// AMNOTE: Creates an untitled session and makes it the active one
	virtual CBaseEditorSession *unk071() = 0;
	// AMNOTE: Returns the session of the file, NULL if it can't be opened. Ignored while another OpenFile runs
	virtual CBaseEditorSession *OpenFile( const char *pszFileName, uint32 nFlags ) = 0;
	// AMNOTE: The tool's main window
	virtual QWidget *unk171() = 0;
	// AMNOTE: Asked by the autosave timer before it saves; false postpones the autosave
	virtual bool unk172() = 0;
	// AMNOTE: Made from the tool's CEngineToolInfo::m_ToolIcon
	virtual void *unk173() = 0;
	virtual const char *unk174() = 0;
	virtual const char *unk175() = 0;
	// AMNOTE: Tool specific part of the tool system initialization; false fails it
	virtual bool unk176() = 0;
	// AMNOTE: Tool specific part of the frame
	virtual void unk177() = 0;
	// AMNOTE: Tool specific part of the shutdown, in this order
	virtual void unk178() = 0;
	virtual void unk179() = 0;
	// AMNOTE: Allocates a session of the tool's own class
	virtual CBaseEditorSession *unk1710() = 0;
	// AMNOTE: Destroys a session unk1710 created
	virtual void unk1711( CBaseEditorSession *pSession ) = 0;
	// AMNOTE: Called when the active session changes
	virtual void unk1712( CBaseEditorSession *pPrevious, CBaseEditorSession *pNew ) = 0;
	virtual bool unk1713( CBaseEditorSession *pSession ) = 0;
	virtual void unk1714() = 0;
	virtual bool unk1715() = 0;
	virtual bool unk1716() = 0;
	virtual bool unk1717( CBaseEditorSession *pSession, const char *pszFileName ) = 0;
	virtual bool unk1718( const char *pszFileName ) = 0;
	virtual void unk1719( KeyValues3 *pSettings ) = 0;
	virtual bool unk1720() = 0;
	virtual bool unk1721( const char *pszFileName ) = 0;
	virtual bool unk1722( const char *pszFileName ) = 0;
	virtual void unk1723( CBaseEditorSession *pSession, const char *pszFileName ) = 0;
	virtual void AppRestoreToolSettings( KeyValues3 *pSettings ) = 0;
	virtual void AppSaveToolSettings( KeyValues3 *pSettings ) = 0;
	// AMNOTE: False makes closing a session do nothing and report success
	virtual bool unk271() = 0;
	// AMNOTE: The session to make active when pSession closes, NULL for none
	virtual CBaseEditorSession *unk272( CBaseEditorSession *pSession ) = 0;
	// AMNOTE: Read once, when the file manager is set up in InitToolSystem
	virtual bool unk273() = 0;
	// AMNOTE: Size of the recent files list, read with unk273; a size below 10 is raised to 10. The base returns 100
	virtual int unk274() = 0;
	virtual void unk275() = 0;

public:
	// AMNOTE: Kept in the tool settings as "LastLoadDirectory"
	CUtlString m_LastLoadDirectory;
	// AMNOTE: The filter of the open dialog, "All Files (*)" by default
	CUtlString m_unk101;
	CBaseEditorSession *m_pActiveSession;
	CUtlVector< CBaseEditorSession * > m_Sessions;
	// AMNOTE: Set by PreShutdown
	bool m_unk201;
	// AMNOTE: Set by Shutdown once the sessions are closed
	bool m_unk202;
	// AMNOTE: Kept in the tool settings as "LastSaveDirectory"
	CUtlString m_LastSaveDirectory;
	// AMNOTE: The filter of the Save As dialog, "All Files (*)" by default
	CUtlString m_unk301;
	// AMNOTE: The directory the Save As dialog starts in when there is no last save directory
	CUtlString m_unk302;
	// AMNOTE: The name prefix of a new untitled session, "untitled_" by default
	CUtlString m_unk303;
	// AMNOTE: The file manager: the recent files with their closed-correctly and autosaved flags, the new files, autosave and recovery
	uint8 m_unk304[80];
	// AMNOTE: The options read from the tool settings ("Perforce Integration", the autosave options)
	uint8 m_unk305[32];
	CContentChangeWatcher m_unk306;
	// AMNOTE: The settings changed; RunFrame saves them while this is set, half a second after the last save at the earliest
	bool m_unk307;
	// AMNOTE: The time of the last settings save
	float m_unk308;
	// AMNOTE: OpenFile also takes a file under the GAME search path as content
	bool m_unk309;
	// AMNOTE: OpenFile opens a file outside the content directory without asking
	bool m_unk3010;
	// AMNOTE: The open dialog takes several files
	bool m_unk3011;
	// AMNOTE: Set while OpenFile runs; no session closes while it is set
	bool m_bInOpenFile;
	// AMNOTE: Set once OpenFile has run the recovery check
	bool m_unk401;
	// AMNOTE: "AppRestoreToolSettings" or "AppSaveToolSettings" while those run, NULL otherwise
	const char *m_unk402;
	// AMNOTE: The sessions in the order they were made active; m_unk404 is the current entry, -1 for none
	CUtlVector< CBaseEditorSession * > m_unk403;
	int m_unk404;
	uint64 m_unk405[3];
};

// AMNOTE: Editor app whose sessions share one main window
class CBaseEditorSharedWindowApp : public CBaseEditorApp
{
public:
	// AMNOTE: The main window
	virtual QWidget *unk081() = 0;
};

// AMNOTE: Editor app that shows every session in its own main window
class CBaseEditorSeparateWindowApp : public CBaseEditorApp
{
};

template < class TSession, class TMainWnd >
class CSimpleEditorSharedWindowApp : public CBaseEditorSharedWindowApp
{
public:
	TMainWnd *m_pMainWnd;
};

#endif // BASEEDITORAPP_H
