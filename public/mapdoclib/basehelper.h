//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The editor helpers of a Hammer map node
//
//===========================================================================//

#ifndef BASEHELPER_H
#define BASEHELPER_H
#ifdef _WIN32
#pragma once
#endif

#include "datamodel/dmelementhandle.h"
#include "mapdoclib/mapdoc.h"
#include "mapdoclib/mapnode.h"
#include "mathlib/vector.h"
#include "mathlib/vmatrix.h"
#include "qcontrols/toolcontextmenuitem.h"
#include "toolutils2/toolattr.h"
#include "tier0/utlvector.h"
#include "tier0/platform.h"

class CHammerEditorSession;

// AMNOTE: Values not known
enum ManipulationMode_t : int;

// A helper the game data attaches to a node: the model, sprite, light cone, line, particle or gizmo the editor draws
// for it
// AMNOTE: Incomplete class, only the scene object, the owner node and the visibility are known. The destructor is
// the IBaseToolAttr one
class CBaseHelper : public IToolRenderCallbacks, public IHitTestable, public IManipulatorTarget, public IBaseToolAttr, public IToolAttr_Table, public IRaytraceEnvironmentOwner
{
public:
	virtual void unk011( void *pUnk, int nUnk ) = 0;
	virtual void unk012( void *pUnk ) = 0;
	virtual void unk013( void *pUnk ) = 0;
	// AMNOTE: Called when the helper is added to the document: keeps one of the document's flags and adds the scene
	// object to the document's scene
	virtual void unk014( void *pDoc ) = 0;
	// AMNOTE: Called when the helper leaves the document: posts EventHelperRemovedFromDocument_t and releases the
	// scene object
	virtual void unk015( void *pDoc ) = 0;
	// AMNOTE: Called with the transform of the owner node's DoTransform
	virtual void unk016( const VMatrix &matrix, int nFlags ) = 0;
	// AMNOTE: Called with the owner node's new origin
	virtual void unk017( const Vector &vecOrigin ) = 0;
	// AMNOTE: Called with the owner node's new angles
	virtual void unk018( const QAngle &angAngles ) = 0;
	// AMNOTE: Called with the owner node's new scales
	virtual void unk019( const Vector &vecScales ) = 0;
	// AMNOTE: Called when a key of the owner entity is set
	virtual void unk0110( const char *pszKey, const char *pszValue ) = 0;
	// AMNOTE: Stores unk0138's answer through unk0137 when it changed, calls unk0122 with it and redraws
	virtual void unk0111( int nUnk ) = 0;
	// AMNOTE: Called with the owner node's highlight state
	virtual void unk0112( int nState ) = 0;
	virtual void unk0113() = 0;
	virtual void unk0114() = 0;
	virtual void unk0115( int nUnk ) = 0;
	virtual void unk0116() = 0;
	virtual void unk0117() = 0;
	virtual void unk0118() = 0;
	virtual void unk0119() = 0;
	virtual void unk0120() = 0;
	virtual void unk0121( void *pUnk, int nUnk ) = 0;
	// AMNOTE: Called with the new visibility
	virtual void unk0122( bool bVisible ) = 0;
	virtual void unk0123( void *pUnk, bool bUnk ) = 0;
	virtual void unk0124( void *pUnk ) = 0;
	virtual void unk0125( void *pUnk, bool bUnk ) = 0;
	virtual void unk0126() = 0;
	// AMNOTE: Called when the editor's manipulation mode changes
	virtual void unk0127( ManipulationMode_t mode ) = 0;
	// AMNOTE: Called when the gizmo's transform space changes
	virtual void unk0128() = 0;
	virtual void unk0129( void *pUnk, int nUnk ) = 0;
	virtual void unk0130( void *pUnk, void *pUnk2 ) = 0;
	virtual bool unk0131( void *pUnk ) = 0;
	virtual bool unk0132() = 0;
	virtual bool unk0133( void *pUnk ) = 0;
	virtual bool unk0134() = 0;
	virtual bool unk0135() = 0;
	// AMNOTE: Called with the owner node's new pivot when unk0134 and unk0135 are true
	virtual void unk0136( const Vector &vecPivot ) = 0;
	// AMNOTE: Stores the visibility and passes it to the scene object
	virtual void unk0137( bool bVisible ) = 0;
	// AMNOTE: Whether the helper is drawn: the owner node's visibility, the document's filters and unk0140 to unk0143
	virtual bool unk0138() = 0;
	// AMNOTE: Its arguments are not proven: no body reads one and no call site was found
	virtual bool unk0139() = 0;
	virtual bool unk0140() = 0;
	virtual bool unk0141() = 0;
	virtual bool unk0142() = 0;
	virtual bool unk0143() = 0;
	virtual bool unk0144() = 0;
	virtual bool unk0145() = 0;
	// AMNOTE: A flag mask the owner node ANDs over its helpers, 15 in the base
	virtual int unk0146() = 0;
	virtual void unk0147( void *pUnk ) = 0;
	virtual bool unk0148() = 0;
	// AMNOTE: The helper's center point, false when it has none
	virtual bool unk0149( Vector *pCenter ) = 0;
	virtual bool unk0150() = 0;
	// AMNOTE: Its arguments are not proven: no body reads one and no call site was found
	virtual bool unk0151() = 0;
	// AMNOTE: Passes both arguments to the scene object
	virtual void unk0152( void *pUnk, void *pUnk2 ) = 0;
	// AMNOTE: Flags, 0 in the base
	virtual int unk0153() = 0;
	// AMNOTE: Adds the helper's context menu entries for the selected nodes to pItems
	virtual void GetCustomCommands( CHammerEditorSession *pSession, CMapDoc *pDoc, const CUtlVector< CMapNode * > &nodes, CUtlVector< ToolContextMenuItem_t > *pItems ) const = 0;
	virtual bool unk111( void *pUnk, void *pUnk2, void *pUnk3, void *pUnk4 ) = 0;
	virtual void unk112( void *pUnk, void *pUnk2, void *pUnk3, void *pUnk4 ) = 0;
	virtual void unk113( void *pUnk, void *pUnk2, void *pUnk3, int nFlags, void *pUnk4, void *pUnk5, void *pUnk6, void *pUnk7 ) = 0;
	// AMNOTE: Sets the owner node; m_unk012 keeps its element handle when it is a CMapNode
	virtual void unk114( CMapNode *pNode ) = 0;
	// AMNOTE: Passes the redraw flags to the scene object
	virtual void unk115( int nFlags ) = 0;
	// AMNOTE: The fog helpers copy their fog parameters to pParams
	virtual bool unk116( void *pParams ) = 0;
	// AMNOTE: The tone mapping helper copies its parameters to pParams
	virtual bool unk117( void *pParams ) = 0;
	virtual bool unk118( void *pUnk ) = 0;
	// AMNOTE: The helper's IToolAttr_Table face, NULL for a NULL this. Its arguments are not proven: no body reads one and no call site was found
	virtual IToolAttr_Table *unk119() = 0;
	virtual void unk1110( void *pUnk ) = 0;

public:
	// AMNOTE: The helper's scene object: the document's scene draws it, the visibility and the redraw flags go to it
	uint8 m_unk011[104];
	// AMNOTE: The owner node's element handle
	DmElementHandle_t m_unk012;
	// AMNOTE: The visibility unk0137 stores
	bool m_unk013;
	// AMNOTE: The document flag unk014 keeps
	bool m_unk014;
};

#endif // BASEHELPER_H
