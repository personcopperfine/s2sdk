//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: Meshes of a Hammer map document
//
//===========================================================================//

#ifndef MAPMESH_H
#define MAPMESH_H
#ifdef _WIN32
#pragma once
#endif

#include "mapdoclib/mapnode.h"
#include "tier0/platform.h"

abstract_class IHammerMeshChangeListener
{
public:
	virtual void unk001() = 0;
	virtual void unk002( void * ) = 0;
	virtual void unk003() = 0;
};

// AMNOTE: Incomplete class. Holds the polygon mesh by value
class CMapMeshBase : public CMapNode
{
public:
	virtual void unk041( bool ) = 0;
	virtual bool unk042() = 0;
	virtual bool unk043() = 0;
	virtual MapNodeUnk8_t unk044() = 0;
	virtual int unk045() = 0;

public:
	uint8 m_unk041[14088];
};

class CMapMesh : public CMapMeshBase, public IHammerMeshChangeListener
{
public:
	virtual void unk051( void *, bool, void *, void *, void *, void *, void * ) = 0;
	virtual int unk052() = 0;
	virtual bool unk053( void *, int, bool ) = 0;
	virtual void unk054( void *, bool, int ) = 0;
	virtual void unk055( void * ) = 0;
	virtual void unk056() = 0;

public:
	uint8 m_unk051[152];
};

#endif // MAPMESH_H
