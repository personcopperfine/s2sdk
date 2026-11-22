//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: Instances of a map inside a Hammer map document
//
//===========================================================================//

#ifndef MAPINSTANCE_H
#define MAPINSTANCE_H
#ifdef _WIN32
#pragma once
#endif

#include "datamodel/dmelementhandle.h"
#include "mapdoclib/mapdoc.h"
#include "mapdoclib/mapentity.h"
#include "mapdoclib/mapnode.h"
#include "tier0/utlstring.h"
#include "tier0/platform.h"

// AMNOTE: A node that can be entered for editing (instances, prefabs, deformers); the open ones are the map document's
// CEditScopeStack
abstract_class IMapEditScope
{
public:
	// AMNOTE: The node this scope belongs to
	virtual CMapNode *unk001() = 0;
	// AMNOTE: CMapInstance returns the root node of the instanced map
	virtual CMapNode *unk002() = 0;
	// AMNOTE: The root element of the map the scope edits, NULL for a scope without a map of its own (CMapInstance)
	virtual CMapRootElement *unk003() = 0;
	virtual bool unk004() = 0;
	virtual bool unk005() = 0;
	// AMNOTE: Called when the scope is entered
	virtual void unk006() = 0;
	// AMNOTE: Called when the scope is left
	virtual void unk007() = 0;
	// AMNOTE: Called after the open scopes changed
	virtual void unk008() = 0;
	// AMNOTE: Writes the scope's display name to pName: the kind alone for 0 ("Instance"), else with its map file or id
	virtual void unk009( int, CUtlString *pName ) = 0;
	// AMNOTE: Path of the scope's icon image
	virtual const char *unk0010() = 0;
	// AMNOTE: Whether pNode is inside the scope
	virtual bool unk0011( CMapNode *pNode, int ) = 0;
	// AMNOTE: Saves a state that unk0013 restores
	virtual void unk0012( void **pState ) = 0;
	virtual void unk0013( void *pState ) = 0;
};

// AMNOTE: Incomplete class, only the instanced element and its root node are known
class CMapInstance : public CMapEntityIONode, public IMapEditScope
{
public:
	virtual int unk051() = 0;
	// AMNOTE: Bakes the instance: copies the instanced map's contents into the document and returns the new node, or NULL
	virtual CMapNode *unk052() = 0;
	virtual bool unk053() = 0;
	virtual bool unk054() = 0;
	virtual bool unk055() = 0;
	virtual bool unk056() = 0;
	virtual bool unk057() = 0;
	// AMNOTE: Appends the node's id to an id path
	virtual void unk058( void * ) = 0;
	// AMNOTE: The map document of the node
	virtual void *unk059() = 0;

public:
	uint8 m_unk051[8];
	// AMNOTE: Handle of the instanced element (the "target" attribute variable, which ends with its CDmAttribute *)
	DmElementHandle_t m_hTarget;
	uint8 m_unk151[20];
	// AMNOTE: The root node of the instanced map
	CMapNode *m_unk152;
	uint8 m_unk153[9];
	bool m_bVisExclude;
	uint8 m_unk251[6];
};

#endif // MAPINSTANCE_H
