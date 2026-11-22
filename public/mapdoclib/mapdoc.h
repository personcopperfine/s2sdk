//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The Hammer map document, its root element and its undo history
//
//===========================================================================//

#ifndef MAPDOC_H
#define MAPDOC_H
#ifdef _WIN32
#pragma once
#endif

#include "datamodel/dmelement.h"
#include "mapdoclib/mapnode.h"
#include "toolutils2/undohistory.h"
#include "tier0/utlstring.h"
#include "tier0/utlvector.h"
#include "tier0/platform.h"

class CMapDoc;
class CMapDocSession;
class IMapEditScope;
class CSelection;

// AMNOTE: A map document or a map file it references (prefabs)
abstract_class IMapFileReference
{
public:
	// AMNOTE: Called before the map file is written; CMapDoc stores the editor version and build in its root and prepares its nodes for the save
	virtual void unk001( bool ) = 0;
	// AMNOTE: Called after the map file is written; CMapDoc undoes what unk001 prepared
	virtual void unk002() = 0;
	virtual void unk003( const char * ) = 0;
	virtual bool unk004() = 0;
	virtual bool unk005( void * ) = 0;
	virtual bool unk006() = 0;
	virtual void unk007( void *, void * ) = 0;
};

abstract_class IUndoDoc
{
public:
	// AMNOTE: CMapDoc marks the node pUndoable as removed from the document
	virtual void unk001( IUndoable *pUndoable ) = 0;
	// AMNOTE: CMapDoc adds the node pUndoable back under pParent, or under none when it is NULL
	virtual void unk002( IUndoable *pUndoable, IUndoable *pParent ) = 0;
	// AMNOTE: CMapDoc records its selection into pHistory
	virtual void unk003( CUndoHistory *pHistory ) = 0;
};

// AMNOTE: Undo history of a map document
class CMapDocHistory : public CUndoHistory
{
public:
	// AMNOTE: A second history; Undo and HasEntries also act on it
	CMapDocHistory *m_unk011;
};

// AMNOTE: The DME root element of a map document ("world", "defaultcamera", "3dcameras", "visbility", "mapVariables", "rootSelectionSet", "nodeInstanceData", ...)
class CMapRootElement : public CDmElement
{
public:
	// AMNOTE: The attribute variables "editorversion", "editorbuild", "isprefab", "m_bIsCordoning", "m_bCordonsVisible", "itemFile",
	// "defaultcamera" and "3dcameras"
	uint8 m_unk011[232];
	// AMNOTE: Handle of the world element (the "world" attribute variable, which ends with its CDmAttribute *)
	DmElementHandle_t m_hWorld;
	// AMNOTE: The attribute variables "visbility", "mapVariables", "rootSelectionSet", "m_ReferencedMeshSnapshots" and "nodeInstanceData"
	uint8 m_unk111[188];
	CMapDocHistory *m_pUndoHistory;
	// AMNOTE: The partner of m_pUndoHistory
	CMapDocHistory *m_pRedoHistory;
	uint8 m_unk211[16];
};

// AMNOTE: Edit scopes open on a map document
class CEditScopeStack : public IUndoable
{
public:
	virtual IUndoable *unk001() override;
	virtual void unk002( IUndoable *pSource ) override;
	virtual void unk003() override;
	virtual void unk004() override;
	virtual void unk005() override;
	virtual void unk006( bool ) override;
	virtual void unk007() override;
	virtual bool unk008() override;
	virtual void *unk009() override;
	virtual void unk0010( void * ) override;
	virtual int unk0011() override;
	virtual void unk0012() override;

public:
	CMapDoc *m_pDoc;
	// AMNOTE: The innermost scope is the last
	CUtlVector< IMapEditScope * > m_Scopes;
};

class CMapDoc : public IMapFileReference, public IUndoDoc, public IUndoListener
{
public:
	virtual void unk001( bool ) override;
	virtual void unk002() override;
	virtual void unk003( const char * ) override;
	virtual bool unk004() override;
	virtual bool unk005( void * ) override;
	virtual bool unk006() override;
	virtual void unk007( void *, void * ) override;

	virtual void unk001( IUndoable *pUndoable ) override;
	virtual void unk002( IUndoable *pUndoable, IUndoable *pParent ) override;
	virtual void unk003( CUndoHistory *pHistory ) override;

	virtual void unk001( int ) override;

public:
	uint8 m_unk001[96];
	CMapDocSession *m_pDocSession;
	CMapRootElement *m_pRoot;
	// AMNOTE: The CMapWorld
	CMapNode *m_pWorld;
	uint8 m_unk101[8];
	CEditScopeStack m_EditScopeStack;
	uint8 m_unk201[88];
	bool m_bActive;
	CSelection *m_pSelection;
	uint8 m_unk301[1400];
	// AMNOTE: The map file's path
	CUtlString m_Path;
	uint8 m_unk401[1576];
};

#endif // MAPDOC_H
