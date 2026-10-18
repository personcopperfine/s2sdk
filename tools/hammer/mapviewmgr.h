//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The views of a Hammer session
//
//===========================================================================//

#ifndef MAPVIEWMGR_H
#define MAPVIEWMGR_H
#ifdef _WIN32
#pragma once
#endif

#include "hammer/mapview.h"
#include "tier0/utlvector.h"
#include "tier0/platform.h"

abstract_class ITagVisualizationListener
{
public:
	virtual void unk001() = 0;
};

abstract_class IShaderReloadListener
{
public:
	virtual void unk001() = 0;
	virtual void unk002() = 0;
};

abstract_class IBoundingBoxChangeListener
{
public:
	virtual void unk001( void * ) = 0;
	virtual void unk002( void * ) = 0;
};

class CMapViewMgr : public ITagVisualizationListener, public IShaderReloadListener, public IBoundingBoxChangeListener
{
public:
	uint8 m_unk001[64];
	CUtlVector< CMapView * > m_Views;
	uint8 m_unk101[256];
};

#endif // MAPVIEWMGR_H
