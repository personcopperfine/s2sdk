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
#include "hammer/hammereditorsession.h"
#include "tier0/utlvector.h"
#include "tier0/platform.h"

struct BoundingBoxChangeRegion_t;

abstract_class ITagVisualizationListener
{
public:
	// AMNOTE: The tag visualisation changed. No caller is known, so its arguments are not known
	virtual void unk001() = 0;
};

abstract_class IShaderReloadListener
{
public:
	// AMNOTE: Both are called for a shader reload. No caller is known, so their arguments are not known
	virtual void unk001() = 0;
	virtual void unk002() = 0;
};

abstract_class IBoundingBoxChangeListener
{
public:
	virtual void EnumerateBoundingBoxChangeRegions( CUtlVector< BoundingBoxChangeRegion_t > *pRegions ) = 0;
	virtual void unk101( void *pUnk ) = 0;
};

// AMNOTE: Incomplete class, only the managers, the session, the capturing view and the views are known
class CMapViewMgr : public ITagVisualizationListener, public IShaderReloadListener, public IBoundingBoxChangeListener
{
public:
	CToolManager *m_pToolManager;
	CHammerEditorSession *m_pSession;
	uint8 m_unk101[16];
	// AMNOTE: The view that holds the mouse capture, NULL when none does
	CMapView *m_unk102;
	uint8 m_unk103[24];
	CUtlVector< CMapView * > m_Views;
	uint8 m_unk201[216];
	// AMNOTE: Returned by the views' IToolRenderableViewHost::unk1010
	int m_unk202;
	uint8 m_unk203[36];
};

#endif // MAPVIEWMGR_H
