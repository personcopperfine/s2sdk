//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The ModelDoc document: the node tree of a .vmdl file and its undo history
//
//===========================================================================//

#ifndef MODELDOC_H
#define MODELDOC_H
#ifdef _WIN32
#pragma once
#endif

#include "modeldoc_lib/modeldocnode.h"
#include "toolutils2/undohistory.h"
#include "tier0/utlvector.h"
#include "tier0/platform.h"

// AMNOTE: Incomplete class, only the tree, the undo histories, the flags and the file time are known
class CModelDoc : public IUndoDoc, public IUndoListener
{
public:
	virtual void unk001( IUndoable *pUndoable ) override;
	virtual void unk002( IUndoable *pUndoable, IUndoable *pParent, int nIndex ) override;
	virtual void unk003( CUndoHistory *pHistory ) override;

	// AMNOTE: Updates the selection sets
	virtual void unk001( int nPhase ) override;

public:
	// AMNOTE: The document modified event is posted to it too, while m_unk003 is not above 0
	void *m_unk001;
	uint8 m_unk002[72];
	int m_unk003;
	uint8 m_unk004[852];
	int m_unk005;
	bool m_bModified;
	CModelDocNode *m_pRoot;
	CUndoHistory *m_pUndoHistory;
	// AMNOTE: m_pUndoHistory's partner
	CUndoHistory *m_pRedoHistory;
	bool m_unk101;
	void *m_unk102;
	// AMNOTE: The document sub type; a node type is allowed in a document by CModelDocNodeType::m_unk1024[m_unk103]
	int8 m_unk103;
	// AMNOTE: Flags: 1 read-only, 2 no undo history of its own, 8 the nodes are not editable
	int m_unk104;
	void *m_unk105;
	// AMNOTE: A child document's parent; a child document opens its undo steps in its top parent's history
	CModelDoc *m_pParent;
	uint8 m_unk201[32];
	// The time of the file when it was loaded
	int64 m_nFileTime;
	uint8 m_unk301[24];
};

#endif // MODELDOC_H
