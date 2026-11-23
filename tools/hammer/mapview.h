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
#include "toolutils2/bindablecamera.h"
#include "mapdoclib/mapnode.h"
#include "hammer/toolmanager.h"
#include "mathlib/camera.h"
#include "mathlib/vector2d.h"
#include "tier0/platform.h"

class CMapViewMgr;
class IViewAttachTarget;
class QWidget;

// AMNOTE: The widget a map view draws into
abstract_class IMapViewWindow
{
public:
	// AMNOTE: The widget's native window id
	virtual uint64 unk001() = 0;
	virtual QWidget *unk002() = 0;
	// AMNOTE: Gives the keyboard focus to the widget's pane
	virtual void unk003() = 0;
	// AMNOTE: Builds and shows the view's context menu with the active tool's entries
	virtual void unk004() = 0;
	// AMNOTE: Maps vecPos in the view to global screen coordinates
	virtual void unk005( Vector2D *pOut, const Vector2D &vecPos ) = 0;
	// AMNOTE: Maps vecPos in global screen coordinates to the view
	virtual void unk006( Vector2D *pOut, const Vector2D &vecPos ) = 0;
	// AMNOTE: Updates the widget's cursor
	virtual void unk007() = 0;
	// AMNOTE: Shows the view's attachment to pTarget, NULL when it is detached, in the widget's pane
	virtual void unk008( IViewAttachTarget *pTarget, float flUnk, bool bUnk, bool bFollowHierarchy ) = 0;
	// AMNOTE: Updates the controls of the widget's pane from the view's state
	virtual void unk009() = 0;
};

// AMNOTE: Incomplete class, only the managers, the window, the type, the attachment and the camera are known.
// One class for the 2D and the 3D views; its virtuals are its three bases'
class CMapView : public IToolRenderableViewHost, public IBindTarget, public IBindableCameraScene
{
public:
	// AMNOTE: CToolEventMapRegistrationHelper< CMapView >, the view's event bindings
	uint64 m_unk011[6];
	CToolManager *m_pToolManager;
	CMapViewMgr *m_pViewMgr;
	// AMNOTE: NULL for a view without a widget
	IMapViewWindow *m_pWindow;
	uint8 m_unk111[24];
	// AMNOTE: Non-zero for the active view
	int m_unk112;
	// AMNOTE: -1 until set; 0 top, 1 front, 2 side, 3 3D, 4 the engine's view
	int m_nViewType;
	int m_nRenderMode;
	uint8 m_unk211[12];
	// AMNOTE: The object the view's camera follows, NULL while the view is attached to a target (m_unk311)
	CMapNode *m_pAttachedObject;
	// AMNOTE: The object whose view attach helper the view is attached to; 2D views are never attached
	CMapNode *m_unk311;
	float m_unk312;
	bool m_unk313;
	// AMNOTE: Follow hierarchy
	bool m_unk314;
	uint8 m_unk315[1106];
	CBindableCamera m_Camera;
	CFrustum m_unk411;
	uint8 m_unk412[1024];
};

#endif // MAPVIEW_H
