//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: A Hammer viewport
//
//===========================================================================//

#ifndef MAPVIEW_H
#define MAPVIEW_H
#ifdef _WIN32
#pragma once
#endif

#include "toolutils2/itoolrenderableviewhost.h"
#include "toolutils2/ibindablecamerascene.h"
#include "toolutils2/ibindtarget.h"
#include "tier0/platform.h"

class CMapView : public IToolRenderableViewHost, public IBindTarget, public IBindableCameraScene
{
public:
	uint8 m_unk011[100];
	// AMNOTE: -1 until set; above 2 is a 3D view
	int m_nViewType;
	int m_nRenderMode;
	// AMNOTE: Holds a CBindableCamera, whose camera GetCamera returns
	uint8 m_unk111[6708];
};

#endif // MAPVIEW_H
