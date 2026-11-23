//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The nodes of a tool scene, the base the tools derive their preview nodes from
//
//===========================================================================//

#ifndef TOOLSCENE_H
#define TOOLSCENE_H
#ifdef _WIN32
#pragma once
#endif

#include "mathlib/vector.h"
#include "mathlib/mathlib.h"
#include "tier0/utlvector.h"
#include "tier0/platform.h"

class CSceneObject;
class CToolScene;
class CToolSceneTraceEnvironment;
class IHitTestable;

// AMNOTE: Incomplete class, only the scene, the parent and the children are known
class CToolSceneNode
{
public:
	// The name of the node's class ("CToolSceneNode", "CToolSceneVmap"); the asset preview shows the controller
	// widget registered for this name
	virtual const char *GetNodeClassName() = 0;
	virtual ~CToolSceneNode() = 0;
	// AMNOTE: The scene object that draws the node, or NULL; the node keeps its transform, bounds and visibility
	// up to date
	virtual CSceneObject *unk201() = 0;
	// AMNOTE: The node's bounds in its own space
	virtual void unk202( Vector *pMins, Vector *pMaxs ) = 0;
	// Sets the node's own visibility; the node is shown when it and every parent are visible
	virtual void SetVisible( bool bVisible ) = 0;
	// AMNOTE: The bounds of the node and its children in world space. pUnk is set to 0 or 1, nFlags (bits 1, 2
	// and 4) is handed to the children
	virtual bool unk301( Vector *pMins, Vector *pMaxs, int *pUnk, int nFlags ) = 0;
	virtual void AddChild( CToolSceneNode *pChild ) = 0;
	virtual void RemoveChild( CToolSceneNode *pChild ) = 0;
	virtual CUtlVector< CToolSceneNode * > *GetChildren() = 0;
	// AMNOTE: Called with the effective visibility after SetVisible changed it
	virtual void unk401( bool bVisible ) = 0;
	// AMNOTE: Draws the node into the scene's trace environment, which picking traces against
	virtual void unk402( CToolSceneTraceEnvironment *pEnvironment ) = 0;
	// AMNOTE: The base returns an empty string
	virtual const char *unk403() = 0;
	// AMNOTE: The base body is empty and no class overrides it; the arguments are not known
	virtual void unk404() = 0;
	// AMNOTE: Called with the node's world transform after it changed
	virtual void unk405( const matrix3x4_t &worldTransform ) = 0;
	virtual void unk406( int nUnk ) = 0;
	// AMNOTE: CToolSceneVmap runs the frame update of its map documents with the float
	virtual void unk407( float flUnk ) = 0;
	virtual void unk408() = 0;

public:
	CToolScene *m_pScene;
	CToolSceneNode *m_pParent;
	CUtlVector< CToolSceneNode * > m_Children;
	// AMNOTE: The transform relative to the parent
	matrix3x4_t m_unk501;
	// AMNOTE: The world transform: the parent's world transform times m_unk501
	matrix3x4_t m_unk502;
	bool m_unk503;
	// AMNOTE: The node's own visibility (SetVisible)
	bool m_unk504;
	// AMNOTE: Set when the node and every parent are visible
	bool m_unk505;
	uint8 m_unk506;
	void *m_unk507;
};

// AMNOTE: Placeholder name; a hit of IToolSceneCustomTrace::TraceRay
struct ToolSceneTraceHitUnk_t
{
	// AMNOTE: The distance from the ray's origin
	float m_unk001;
	// AMNOTE: The position of the hit
	Vector m_unk002;
	Vector m_unk003;
	// AMNOTE: The node that was hit
	CToolSceneNode *m_unk004;
	uint8 m_unk005[36];
};

// A node that adds its own hits when the tool scene traces a ray
abstract_class IToolSceneCustomTrace
{
public:
	// Traces the ray from vecOrigin along vecDirection (normalised here) and adds up to nMaxHits hits (all for a
	// negative count) to pHits; returns how many were added
	virtual int TraceRay( const Vector &vecOrigin, const Vector &vecDirection, CUtlVector< ToolSceneTraceHitUnk_t > *pHits, int nMaxHits ) = 0;
};

// Scene objects that a tool object owns as a group
abstract_class IToolSceneObjectContainer
{
public:
	// AMNOTE: CVertexListSceneObject tests its primitives against pUnk; the others do nothing
	virtual void unk001( void *pUnk, bool bUnk ) = 0;
	// AMNOTE: Sets the transform of the scene objects (combined with their own, where a container keeps one)
	virtual void unk002( const matrix3x4_t &transform ) = 0;
	// Deletes the container
	virtual void Release() = 0;
	// AMNOTE: CModelInstanceSceneObjectContainer returns itself, the others NULL
	virtual void *unk101() = 0;
};

// The debug-draw geometry of a tool: lines, triangles or points with per-vertex colour
abstract_class IVertexListObject : public IToolSceneObjectContainer
{
public:
	// AMNOTE: Appends nVertexCount vertices of the object's vertex size, copied from pVertices; NULL only reserves
	// the space
	virtual void unk011( const void *pVertices, int nVertexCount ) = 0;
	// AMNOTE: Appends room for nVertexCount vertices and returns it for the caller to fill
	virtual void *unk012( int nVertexCount ) = 0;
	// AMNOTE: Transforms the positions and normals of the vertices appended since the last call by transform
	virtual void unk013( const matrix3x4_t &transform ) = 0;
	// AMNOTE: The primitives appended from now on belong to pHitTestable: picking against them gives hits on it,
	// which keep nUnk and pUnk. pUnk is a pointer-sized value nothing here reads, its type is not known
	virtual void unk014( IHitTestable *pHitTestable, int64 nUnk, void *pUnk ) = 0;
};

#endif // TOOLSCENE_H
