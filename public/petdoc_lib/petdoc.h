//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: Particle system document of the particle editor: the node tree and its undo history
//
//===========================================================================//

#ifndef PETDOC_H
#define PETDOC_H
#ifdef _WIN32
#pragma once
#endif

#include "tier0/keyvalues3.h"
#include "tier0/utlvector.h"
#include "tier0/buffer_string.h"
#include "toolutils2/toolattr.h"
#include "toolutils2/undohistory.h"

class CPetDoc;
class CPetRootNode;
class CPetChildNode;
class CPetFunctionNode;
class CPetVariableNode;

// AMNOTE: Incomplete class, only its document and its table are known
class CBasePetNode : public CBaseKV3DataWithFGDClass, public IToolAttrNotifyRoot
{
public:
	// AMNOTE: The node's kind: for a function node the index of the root's node array it is in (0 to 6), 7 for a
	// child, 8 for a variable, 9 for the root
	virtual int unk021() = 0;
	// AMNOTE: Name of the node's schema class: "CParticleSystemDefinition" for the root, "ParticleChildrenInfo_t" for
	// a child, "ParticleNamedValueSource_t" for a variable, the table's "_class" for a function
	virtual const char *GetClassName() = 0;
	// AMNOTE: True only for a child, the root, a function, a variable node
	virtual bool unk121() = 0;
	virtual bool unk122() = 0;
	virtual bool unk123() = 0;
	virtual bool unk124() = 0;
	// AMNOTE: this when the node is of the class, else NULL
	virtual CPetChildNode *unk125() = 0;
	virtual CPetRootNode *unk126() = 0;
	virtual CPetFunctionNode *unk127() = 0;
	virtual CPetVariableNode *unk128() = 0;
	// AMNOTE: m_unk003
	virtual KeyValues3 *unk129() = 0;
	virtual KeyValues3 *unk1210() = 0;
	// AMNOTE: Copies the node's KeyValues3 into pOut; the root writes its node arrays with it
	virtual void unk1211( KeyValues3 *pOut ) = 0;
	// AMNOTE: Replaces the node's KeyValues3 by a copy of pIn; the root reads its node arrays with it
	virtual void unk1212( const KeyValues3 *pIn ) = 0;
	// AMNOTE: False when the node's m_bDisableOperator (a child's m_bDisableChild) is set
	virtual bool unk1213() = 0;
	// AMNOTE: Sets the node's m_bDisableOperator (a child's m_bDisableChild) to !bEnabled
	virtual void unk1214( bool bEnabled ) = 0;
	// AMNOTE: Writes the node's row of the function list: its name into pName (the definition's friendly name, a
	// child's file name), its value into pValue, "Edit node" into pUnk
	virtual void unk1215( CBufferString *pName, CBufferString *pValue, CBufferString *pUnk ) = 0;

public:
	// AMNOTE: The document the node belongs to
	CPetDoc *m_unk001;
	uint64 m_unk002;
	// AMNOTE: The node's table, an instance of its schema class
	KeyValues3 m_unk003;
};

// AMNOTE: The particle system the document edits: its table holds the system's own properties, its nodes and
// control point configurations are kept apart and written back into it on save
class CPetRootNode : public CBasePetNode
{
public:
	// AMNOTE: The nodes by kind (CBasePetNode::unk021), the file's m_PreEmissionOperators, m_Emitters,
	// m_Initializers, m_Operators, m_ForceGenerators, m_Constraints, m_Renderers, m_Children and m_NamedValueLocals
	CUtlVector< CBasePetNode * > m_unk011[9];
	// AMNOTE: Pointers to 144-byte records read from and written to the table's m_controlPointConfigurations
	CUtlVector< void * > m_controlPointConfigurations;
};

struct PetDocSelection_t
{
	// AMNOTE: Kind of the selected node
	int m_unk001;
	int m_unk002;
};

// AMNOTE: Incomplete class, only the tree, selection and undo members are known
class CPetDoc : public CBaseUndoable, public IUndoListener
{
public:
	// AMNOTE: Records the document as an undo step
	virtual void unk021() = 0;

public:
	uint8 m_unk001[88];
	CUtlVector< PetDocSelection_t > m_Selection;
	CPetRootNode *m_pRoot;
	CUndoHistory *m_pUndoHistory;
	// AMNOTE: m_pUndoHistory's partner
	CUndoHistory *m_unk101;
	// AMNOTE: Caches of the tree, refreshed on undo
	uint8 m_unk102[56];
};

#endif // PETDOC_H
