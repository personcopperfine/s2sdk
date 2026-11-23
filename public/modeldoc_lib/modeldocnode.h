//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The nodes of a ModelDoc document and their node type descriptor
//
//===========================================================================//

#ifndef MODELDOCNODE_H
#define MODELDOCNODE_H
#ifdef _WIN32
#pragma once
#endif

#include "mathlib/aabb.h"
#include "mathlib/mathlib.h"
#include "mathlib/vector.h"
#include "tier0/utlstring.h"
#include "tier0/utlvector.h"
#include "tier0/platform.h"
#include "toolutils2/toolattr.h"
#include "toolutils2/toolnodetypename.h"
#include "toolutils2/undohistory.h"

class CModelDoc;
class CModelDocNode;
class CModelPreviewPart;
class CKV3TransferLoadContext;
class CKV3TransferSaveContext;

// AMNOTE: Incomplete class. The base of the document nodes and of the editor's preview parts
class CModelDocAtom : public IToolAttrNotifyRoot, public IToolAttr_Table
{
public:
	// AMNOTE: Fills pAttrs with the atom's attributes: its GetStaticAttributes table, then a node's dynamic attributes
	virtual void unk011( CUtlVector< IBaseToolAttr * > *pAttrs ) = 0;

protected:
	// The attribute table of the class
	virtual void GetStaticAttributes( CUtlVector< IBaseToolAttr * > *pAttrs ) {}

public:
	// AMNOTE: The bounds of the atom's helpers; false when none has bounds
	virtual bool unk111( AABB_t *pBounds ) = 0;
	// AMNOTE: this when the atom is a node, else NULL
	virtual CModelDocNode *unk112() = 0;
	virtual const CModelDocNode *unk112() const = 0;
	// AMNOTE: this when the atom is a preview part, else NULL
	virtual CModelPreviewPart *unk113() = 0;
	virtual const CModelPreviewPart *unk113() const = 0;
	// AMNOTE: The parent
	virtual CModelDocAtom *unk114() = 0;
	virtual const CModelDocAtom *unk114() const = 0;
	// AMNOTE: The number of children and a child, NULL for an index past the last
	virtual int unk115() = 0;
	virtual CModelDocAtom *unk116( int nIndex ) = 0;
	virtual const CModelDocAtom *unk116( int nIndex ) const = 0;
	// AMNOTE: A node is in its document's primary selection set
	virtual bool unk117() = 0;
	virtual bool unk118() = 0;
	// AMNOTE: unk117 of the parent, and of any ancestor
	virtual bool unk119() = 0;
	virtual bool unk1110() = 0;
	// AMNOTE: A name the atom has for nKind, or NULL
	virtual const char *unk1111( int nKind ) { return NULL; }
	// AMNOTE: The text the preview shows for the atom; false when it has none
	virtual bool unk1112( CUtlString *pText ) { return false; }
	virtual bool unk1112( CUtlString *pText ) const { return false; }
	// AMNOTE: A node's document is read-only
	virtual bool unk1113() = 0;
	// AMNOTE: The atom's name, "" when it has none
	virtual const char *unk1114() = 0;
	// AMNOTE: A node's type name
	virtual const char *unk1115() = 0;
	// AMNOTE: Appends the names of the node editors the editor shows for the atom
	virtual void unk1116( CUtlVector< CUtlString > *pEditors ) {}
	virtual ~CModelDocAtom() = 0;
	// AMNOTE: Adds the atom's helpers, made through pUnk
	virtual void unk211( void *pUnk ) {}

public:
	// AMNOTE: Owned, destroyed with the atom: the helpers unk211 adds
	CUtlVector< void * > m_unk001;
	int m_unk002;
	uint8 m_unk003[4];
	// AMNOTE: Taken from a global counter on construction
	int m_unk004;
	// AMNOTE: The atom's index in the list of atoms m_unk006 points to
	int m_unk005;
	void *m_unk006;
};

// AMNOTE: Placeholder name, the binary has none: the node type descriptor each node class registers, a static object per type.
// Incomplete struct, only the names, the base, the namespace and the flags are known
struct CModelDocNodeType
{
	// The _class name of the type
	CToolNodeTypeName m_Name;
	CToolNodeTypeName m_BaseName;
	// AMNOTE: The descriptor of m_BaseName, NULL for the root type
	const CModelDocNodeType *m_pBase;
	// AMNOTE: 16 bytes, likely a KeyValues3
	uint8 m_unk101[16];
	bool m_unk102;
	// AMNOTE: Creates a node of the type; NULL for an abstract type
	void *m_unk103;
	// AMNOTE: Node names are unique per namespace
	int m_unk104;
	int m_unk105;
	const char *m_unk106;
	const char *m_unk107;
	const char *m_unk108;
	// AMNOTE: The add menu labels, "Add %1" and "Add %1..." by default
	const char *m_unk109;
	const char *m_unk1010;
	CUtlVector< const char * > m_unk1011;
	int m_unk1012;
	bool m_unk1013;
	bool m_unk1014;
	bool m_unk1015;
	// AMNOTE: A node of any type can be added under a node of this type
	bool m_unk1016;
	bool m_unk1017;
	bool m_unk1018;
	CUtlVector< CToolNodeTypeName > m_unk1019;
	CUtlVector< CToolNodeTypeName > m_unk1020;
	CUtlVector< CToolNodeTypeName > m_unk1021;
	const char *m_unk1022;
	// AMNOTE: A std::function
	uint8 m_unk1023[64];
	// AMNOTE: Whether the type is allowed in a document, per document sub type
	bool m_unk1024[4];
	int m_unk1025;
};

// AMNOTE: Incomplete class, only the document, the tree, the name, the note and the disabled flag are known
class CModelDocNode : public CModelDocAtom, public IUndoable
{
public:
	virtual const CModelDocNodeType *unk021() = 0;
	// AMNOTE: m_Name of unk021()
	virtual CToolNodeTypeName unk022() = 0;
	// AMNOTE: m_unk104 and m_unk1025 of unk021()
	virtual int unk023() = 0;
	virtual int unk024() = 0;
	// AMNOTE: Whether the node's type is name: the tokens are compared
	virtual bool unk025( const CToolNodeTypeName &name ) = 0;
	virtual void unk026( void *pUnk, int nUnk ) = 0;
	virtual void unk027( void *pUnk ) = 0;
	virtual void unk028( const Vector &vecUnk ) = 0;
	virtual bool unk029( void *pUnk, void *pUnk2 ) = 0;
	// AMNOTE: Its arguments are not known: no body or caller read shows them
	virtual int unk0210() = 0;
	// AMNOTE: A string the node class keeps, "" when it has none; unk0212 records the node for undo and sets it
	virtual const char *unk0211() = 0;
	virtual void unk0212( const char *pszUnk ) = 0;
	// AMNOTE: Its arguments are not known: no body or caller read shows them
	virtual bool unk0213() = 0;
	// Records the node for undo and sets m_bDisabled
	virtual void SetDisabled( bool bDisabled ) = 0;
	virtual void unk121( void *pUnk ) = 0;
	virtual bool unk122( void *pUnk ) = 0;
	virtual bool unk123( const void *pUnk ) = 0;
	// Whether pChild can be added under this node; false, with the reason in pError when it is not NULL, when pChild is
	// this node or one of its ancestors or its type does not allow this node's type as its parent. A folder asks its
	// nearest ancestor that is not a folder, and fails without one
	virtual bool CanAddChild( CModelDocNode *pChild, CUtlString *pError ) = 0;
	// AMNOTE: A folder node
	virtual bool unk221() = 0;
	virtual bool unk222() = 0;
	virtual void *unk223() = 0;
	// AMNOTE: Writes the node, then its children, into the save context's table
	virtual void unk224( CKV3TransferSaveContext *pContext ) = 0;
	// AMNOTE: Reads the node from the load context's table
	virtual void unk225( CKV3TransferLoadContext *pContext ) = 0;
	virtual void unk226( int nUnk ) = 0;
	// AMNOTE: Its arguments are not known: no body or caller read shows them
	virtual void unk227() = 0;
	// AMNOTE: pAttr is cast to the node's dynamic attribute class
	virtual bool unk228( IBaseToolAttr *pAttr ) = 0;
	virtual void *unk229() = 0;
	virtual void *unk2210() = 0;
	virtual int unk2211( CUtlVector< void * > *pUnk ) = 0;
	// AMNOTE: The identity in the base
	virtual void unk2212( matrix3x4_t *pTransform ) = 0;
	virtual void unk2213( void *pUnk ) = 0;
	virtual void unk2214( void *pUnk ) = 0;
	virtual int unk2215( int nUnk, void *pUnk ) = 0;
	virtual int unk2216( void **ppUnk ) = 0;
	virtual int unk2217( void *pUnk, void *pUnk2 ) = 0;
	// AMNOTE: Its arguments are not known: no body or caller read shows them
	virtual int unk2218() = 0;
	// AMNOTE: Its arguments are not known: no body or caller read shows them
	virtual bool unk2219() = 0;
	// AMNOTE: Copies the note and, by nFlags, more of pSource into this node
	virtual void unk2220( CModelDocNode *pSource, int nFlags ) = 0;
	virtual void unk2221( CModelDocNode *pSource, void *pUnk ) = 0;
	virtual bool unk2222() = 0;
	virtual bool unk2223( CUtlString *pUnk ) = 0;
	virtual bool unk2224( void *pUnk ) = 0;
	virtual bool unk2225() = 0;
	// AMNOTE: The node has children
	virtual bool unk2226() = 0;
	virtual void *unk2227( const char *pszName, int nKind ) = 0;
	virtual void unk2228( void *pUnk ) = 0;
	virtual void unk2229( void *pUnk ) = 0;
	virtual void unk2230( CUtlString *pUnk ) = 0;
	virtual void *unk2231() = 0;
	virtual void unk2232() = 0;
	virtual void *unk2233() = 0;

public:
	CModelDoc *m_pDocument;
	CModelDocNode *m_pParent;
	uint8 m_unk101[8];
	// AMNOTE: unk223 returns the pointer this object holds at m_pDocument's offset
	void *m_unk102;
	uint8 m_unk103[16];
	CUtlVector< CModelDocNode * > m_Children;
	// AMNOTE: The dynamic attributes
	uint8 m_unk201[16];
	CUtlString m_Name;
	bool m_bDisabled;
	CUtlString m_Note;
};

#endif // MODELDOCNODE_H
