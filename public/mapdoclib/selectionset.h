//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The selection sets of a Hammer map document, one per select mode
//
//===========================================================================//

#ifndef SELECTIONSET_H
#define SELECTIONSET_H
#ifdef _WIN32
#pragma once
#endif

#include "datamodel/dmelement.h"
#include "datamodel/idatamodel.h"
#include "mapdoclib/mapnode.h"
#include "mathlib/aabb.h"
#include "mathlib/vector.h"
#include "mathlib/vmatrix.h"
#include "toolutils2/undohistory.h"
#include "tier0/utlstring.h"
#include "tier0/utlvector.h"
#include "tier0/platform.h"

class CSelection;

// AMNOTE: Enumerator names follow the "SelectionMode*" bind commands; the prefix is in no binary
enum SelectMode_t
{
	SELECT_MODE_INVALID = -1,

	SELECT_MODE_GROUPS = 0,
	SELECT_MODE_OBJECTS,
	SELECT_MODE_MESHES,
	SELECT_MODE_VERTICES,
	SELECT_MODE_EDGES,
	SELECT_MODE_FACES,
	SELECT_MODE_NAV,
	// AMNOTE: The tile editor's mode; no string names it
	SELECT_MODE_UNK007,

	SELECT_MODE_COUNT
};

// AMNOTE: A saved state of a selection set, made by ISelectionSet::unk0162 and restored by unk0163
abstract_class ISelectionState
{
public:
	// AMNOTE: The only virtual
	virtual ~ISelectionState() {}
};

// AMNOTE: A set of selected items of one kind (objects, mesh vertices, edges or faces, ...). The nMode arguments
// that merge items take 1 (replace), 2 (add), 3 (remove) and 4 (toggle)
abstract_class ISelectionSet : public ITransformable
{
public:
	virtual ~ISelectionSet() {}
	// AMNOTE: A new set of the same kind, empty
	virtual ISelectionSet *unk011( int nUnk, CSelection *pSelection ) = 0;
	// AMNOTE: unk013 with pNode alone
	virtual bool unk012( CMapNode *pNode, int nMode ) = 0;
	// AMNOTE: Merges the nodes into the set
	virtual bool unk013( const CUtlVector< CMapNode * > &nodes, int nMode ) = 0;
	// AMNOTE: Replaces pOld with pNew
	virtual void unk014( CMapNode *pOld, CMapNode *pNew ) = 0;
	virtual void unk015( CMapNode *pNode ) = 0;
	// AMNOTE: Whether pNode is in the set
	virtual bool unk016( CMapNode *pNode ) = 0;
	// AMNOTE: Whether pNode, or a component of it, is in the set
	virtual bool unk017( CMapNode *pNode ) = 0;
	virtual void unk018( ISelectionSet *pUnk, CMapNode *pUnk1, CMapNode *pUnk2 ) = 0;
	// AMNOTE: The first selected object, NULL when the set is empty or is a component set
	virtual CMapNode *unk019() = 0;
	// AMNOTE: The selected nodes; the mesh component sets give none (unk0150 gives their meshes)
	virtual void unk0110( CUtlVector< CMapNode * > *pNodes ) = 0;
	// AMNOTE: The undoables of the selected nodes
	virtual void unk0111( CUtlVector< IUndoable * > *pUndoables ) = 0;
	// AMNOTE: Deletes the selection; pRemoved gets the nodes to remove from the document
	virtual void unk0112( CUtlVector< CMapNode * > *pRemoved ) = 0;
	// AMNOTE: Copies of the selected nodes
	virtual void unk0113( CUtlVector< CMapNode * > *pCopies, void *pUnk1, void *pUnk2 ) = 0;
	// AMNOTE: Called with true when the set becomes the active one, with false when it stops being it
	virtual void unk0114( bool bActive ) = 0;
	virtual void unk0115() = 0;
	virtual void unk0116() = 0;
	virtual void unk0117() = 0;
	// AMNOTE: Removes the items of pNode
	virtual void unk0118( CMapNode *pNode ) = 0;
	// AMNOTE: Removes every item
	virtual void unk0119() = 0;
	virtual bool unk0120() = 0;
	virtual bool unk0121() = 0;
	virtual bool unk0122( int nFlags ) = 0;
	// AMNOTE: Whether the set has no item
	virtual bool unk0123() = 0;
	// AMNOTE: The number of items
	virtual int unk0124() = 0;
	// AMNOTE: Fills the set from pFrom when the select mode changes; nConversion is 0 (none), 1 (convert), 2 (connected)
	// or 3 (boundary)
	virtual void unk0125( ISelectionSet *pFrom, int nConversion ) = 0;
	virtual void unk0126( ISelectionSet *pUnk, int nMode ) = 0;
	// AMNOTE: Merges the items of pOther, a set of the same kind; false when it is of another kind
	virtual bool unk0127( ISelectionSet *pOther, int nMode, int nUnk ) = 0;
	// AMNOTE: Removes the last item
	virtual void unk0128() = 0;
	// AMNOTE: Removes the first item
	virtual void unk0129() = 0;
	// AMNOTE: Select All
	virtual void unk0130() = 0;
	// AMNOTE: Invert Selection
	virtual void unk0131() = 0;
	// AMNOTE: Select Similar
	virtual void unk0132() = 0;
	virtual void unk0133() = 0;
	// AMNOTE: Grows the selection
	virtual void unk0134() = 0;
	// AMNOTE: Shrinks the selection
	virtual void unk0135() = 0;
	virtual void unk0136() = 0;
	// AMNOTE: Every set has an empty body; its arguments are not known
	virtual void unk0137() = 0;
	virtual void unk0138( bool bUnk, int nUnk ) = 0;
	// AMNOTE: The bounds of the items
	virtual const AABB_t &unk0139() = 0;
	// AMNOTE: Recomputes the bounds
	virtual void unk0140() = 0;
	virtual void unk0141( void *pUnk, Vector *pMins, Vector *pMaxs ) = 0;
	virtual void unk0142( VMatrix *pMatrix ) = 0;
	virtual void unk0143( Vector *pOrigin ) = 0;
	virtual void unk0144( int nIndex, Vector *pOrigin ) = 0;
	virtual void unk0145( CUtlVector< Vector > *pOrigins ) = 0;
	virtual void unk0146( int nIndex, AABB_t *pBounds ) = 0;
	virtual void unk0147( CUtlVector< AABB_t > *pBounds ) = 0;
	virtual void unk0148( int nIndex, AABB_t *pBounds ) = 0;
	virtual void unk0149( CUtlVector< AABB_t > *pBounds ) = 0;
	// AMNOTE: The nodes of the items (the meshes of the component sets)
	virtual void unk0150( CUtlVector< CMapNode * > *pNodes ) = 0;
	virtual void unk0151( int nIndex, VMatrix *pMatrix ) = 0;
	virtual void unk0152( CUtlVector< VMatrix > *pMatrices ) = 0;
	// AMNOTE: Starts a transform of the items
	virtual void unk0153( int nUnk ) = 0;
	// AMNOTE: Transforms the items; nFlags as CMapPoint::DoTransform's
	virtual void unk0154( const VMatrix &matrix, int nFlags ) = 0;
	// AMNOTE: Transforms each item by its own matrix
	virtual void unk0155( const CUtlVector< VMatrix > &matrices, int nFlags ) = 0;
	// AMNOTE: Transforms the pivot
	virtual void unk0156( const VMatrix &matrix ) = 0;
	virtual void unk0157( const void *pUnk ) = 0;
	// AMNOTE: Ends the transform unk0153 started
	virtual void unk0158() = 0;
	// AMNOTE: Whether a transform is in progress
	virtual bool unk0159() = 0;
	// AMNOTE: Snap To Grid
	virtual void unk0160( const void *pGridSnap ) = 0;
	virtual void unk0161( int nUnk ) = 0;
	// AMNOTE: Saves the set's state
	virtual ISelectionState *unk0162() = 0;
	// AMNOTE: Restores a state unk0162 saved
	virtual void unk0163( ISelectionState *pState ) = 0;
	// AMNOTE: Opens a change; unk0165 closes it
	virtual void unk0164() = 0;
	// AMNOTE: Closes a change unk0164 opened
	virtual void unk0165() = 0;
	// AMNOTE: Whether a change is open
	virtual bool unk0166() = 0;
	// AMNOTE: The pivot
	virtual const Vector &unk0167() = 0;
	virtual void unk0168( const Vector &vecPivot ) = 0;
	// AMNOTE: Moves the pivot to the origin of the selection
	virtual void unk0169() = 0;
	// AMNOTE: The kind of the set: two sets of the same kind give the same pointer
	virtual const int *unk0170() = 0;
	// AMNOTE: Display name of the kind ("Objects", "Mesh Faces", ...)
	virtual const char *unk0171() = 0;
	virtual bool unk0172() = 0;
	virtual bool unk0173( CMapNode *pNode, int nUnk, bool bUnk1, bool bUnk2 ) = 0;
	// AMNOTE: Whether an item belongs to pNode
	virtual bool unk0174( CMapNode *pNode ) = 0;
	virtual void unk0175( CMapNode *pNode, int nMode ) = 0;
	virtual int unk0176( int nUnk ) = 0;
	// AMNOTE: The number of items pOther has too
	virtual int unk0177( ISelectionSet *pOther ) = 0;
	virtual void unk0178( int nUnk ) = 0;
	virtual int unk0179() = 0;
	virtual void unk0180( int nUnk ) = 0;
	virtual SelectMode_t unk0181() = 0;
	// AMNOTE: Writes a description of the selection ("%d objects", ...)
	virtual void unk0182( CUtlString *pDescription ) = 0;
	// AMNOTE: Creates the DME element that saves the set
	virtual CDmElement *unk0183( DmFileId_t fileId ) = 0;
	// AMNOTE: Loads the set from an element unk0183 made
	virtual void unk0184( CDmElement *pElement ) = 0;
};

// AMNOTE: Incomplete class, only the items, the owner, the bounds and the pivot are known. The base of the sets; T is
// the item, CMapNode * for the object sets
template < class T >
class CSelectionSet : public ISelectionSet
{
public:
	// AMNOTE: Whether item may stay in the set
	virtual bool unk021( const T &item ) { return true; }
	virtual bool unk022( const T &item ) { return true; }
	// AMNOTE: Whether item belongs to pNode
	virtual bool unk023( const T &item, CMapNode *pNode ) { return false; }
	virtual bool unk024( CMapNode *pNode, const T &item ) = 0;
	// AMNOTE: Computes the bounds of the items
	virtual void unk025( AABB_t *pBounds ) { pBounds->MakeInvalid(); }
	// AMNOTE: Called after the items changed
	virtual void unk026( const CUtlVector< T > &added, const CUtlVector< T > &removed ) {}
	virtual void unk027( T item ) {}
	virtual void unk028( T item ) {}

public:
	CUtlVector< T > m_SelectedItems;
	// AMNOTE: The items again, for lookups
	uint8 m_unk101[40];
	// AMNOTE: A default-constructed item
	T m_unk102;
	int m_unk103;
	SelectMode_t m_SelectMode;
	CSelection *m_pSelection;
	AABB_t m_Bounds;
	// AMNOTE: True when the set has an owner
	bool m_unk201;
	uint8 m_unk202[71];
	Vector m_vecPivot;
	// AMNOTE: unk0178 sets it
	int m_unk301;
};

class CObjectSelectionSet : public CSelectionSet< CMapNode * >
{
public:
	// AMNOTE: True while a transform is in progress
	bool m_unk011;
	int m_unk012;
	// AMNOTE: unk0179 returns it, unk0180 sets it
	int m_unk013;
	// AMNOTE: A flag, then a CUtlVector of unknown elements
	uint8 m_unk014[28];
};

#endif // SELECTIONSET_H
