//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: A map open in Hammer
//
//===========================================================================//

#ifndef HAMMEREDITORSESSION_H
#define HAMMEREDITORSESSION_H
#ifdef _WIN32
#pragma once
#endif

#include "toolutils2/baseeditorsession.h"
#include "toolutils2/ibindtarget.h"
#include "toolutils2/itoolsresourcelistener.h"
#include "mapdoclib/mapdoc.h"
#include "tier0/utlstring.h"
#include "tier0/platform.h"

class CMapViewMgr;
class CHammerEditorSession;

abstract_class IBindableCommandListener
{
public:
	virtual void unk001( int, void *, int ) = 0;
};

abstract_class IAssetFileListener
{
public:
	virtual void unk001( int * ) = 0;
};

abstract_class IMapDocSession
{
public:
	// AMNOTE: Updates the views of the owning session
	virtual void unk001() = 0;
	virtual void unk002() = 0;
	virtual bool unk003() = 0;
	virtual void unk004() = 0;
};

// AMNOTE: Owns the map document of a CHammerEditorSession
class CMapDocSession : public IMapDocSession
{
public:
	virtual ~CMapDocSession() = 0;

public:
	uint8 m_unk001[8];
	CMapDoc m_Doc;
	CHammerEditorSession *m_pOwner;
	uint8 m_unk101[568];
};

class CHammerEditorSession : public CBaseEditorSession, public IBindTarget, public IToolsResourceListener, public IBindableCommandListener, public IAssetFileListener
{
public:
	// AMNOTE: The document's path, an empty string without a document
	virtual const CUtlString &GetMapFilePath() = 0;

public:
	uint8 m_unk011[176];
	CMapViewMgr *m_pViewMgr;
	CMapDocSession *m_pDocSession;
	uint8 m_unk111[296];
};

#endif // HAMMEREDITORSESSION_H
