//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: Base classes of Hammer's editor tools
//
//===========================================================================//

#ifndef BASETOOL_H
#define BASETOOL_H
#ifdef _WIN32
#pragma once
#endif

#include "toolutils2/ibindtarget.h"
#include "toolutils2/undohistory.h"
#include "mapdoclib/mapnode.h"
#include "mathlib/vector.h"
#include "mathlib/vector2d.h"
#include "color.h"
#include "tier0/utlstring.h"
#include "tier0/platform.h"

class CBaseToolPlane;
class CHammerEditorSession;
class CMapView;
class QCursor;
class QWidget;

// AMNOTE: Incomplete class, only the tool id and the session are known. The base of every Hammer tool; the
// tool manager keeps one instance of each and switches between them
class CBaseTool : public IBindTarget, public IToolRenderCallbacks, public IHitTestable
{
public:
	// AMNOTE: Attaches the tool to pSession and its document's render scene
	virtual void unk011( CHammerEditorSession *pSession );
	// AMNOTE: Detaches the tool from its session's render scene; the base ignores pSession
	virtual void unk012( CHammerEditorSession *pSession );
	// AMNOTE: Takes a map view's pick context; true skips the document's own hit test
	virtual bool unk013( void *pContext ) { return false; }
	// AMNOTE: False refuses a switch to this tool
	virtual bool unk014() { return true; }
	// AMNOTE: False refuses a switch away from this tool
	virtual bool unk015() { return true; }
	// AMNOTE: Builds the tool's panel into pParent
	virtual void unk016( QWidget *pParent ) {}
	// AMNOTE: Takes the tool's panel out of pWidget
	virtual void unk017( QWidget *pWidget ) {}
	// AMNOTE: A drag of the tool's own object is running
	virtual bool unk018() { return false; }
	// AMNOTE: The tool holds nothing
	virtual bool unk019() { return m_unk114; }
	// AMNOTE: Drops what the tool holds
	virtual void unk0110() { unk0139(); m_unk114 = true; }
	// AMNOTE: No tool overrides it, so its arguments are not known
	virtual void unk0111() {}
	// AMNOTE: Writes the tool's status bar text into pText
	virtual void unk0112( CUtlString *pText ) {}
	// AMNOTE: The tool became the active one, after unk0114
	virtual void unk0113() {}
	// AMNOTE: The tool is being made the active one; 1 when the switch is forced, else 0
	virtual void unk0114( int nUnk ) {}
	// AMNOTE: The tool stopped being the active one
	virtual void unk0115() {}
	// AMNOTE: Another tool is being made the active one; 1 when the switch is forced, else 0
	virtual void unk0116( int nUnk ) {}
	// AMNOTE: The active tool was asked for again
	virtual void unk0117() {}
	// AMNOTE: The tool is no longer the one to return to after a temporary switch
	virtual void unk0118() {}
	// AMNOTE: Called after an undo or a redo
	virtual void unk0119() {}
	// AMNOTE: No tool overrides it, so its arguments are not known
	virtual void unk0120() {}
	// AMNOTE: Once per editor frame while the tool is active
	virtual void unk0121() {}
	virtual void unk0122( int nUnk ) { m_unk112 = nUnk; }
	virtual int unk0123() { return m_unk112; }
	// AMNOTE: The tool manager's manipulation mode changed from nOldMode to nNewMode
	virtual void unk0124( int nOldMode, int nNewMode ) {}
	// AMNOTE: The document's select mode changed to nSelectMode
	virtual void unk0125( int nSelectMode ) {}
	// AMNOTE: Commits the tool's pending work or leaves the tool (what Enter does)
	virtual void unk0126() {}
	// AMNOTE: The document's active map root element changed
	virtual void unk0127() {}
	// AMNOTE: No tool overrides it, so its arguments are not known
	virtual bool unk0128() { return false; }
	// AMNOTE: True forces the views to draw the selection outline
	virtual bool unk0129() { return false; }
	// AMNOTE: True replaces the selection outline color with pColor
	virtual bool unk0130( Color *pColor ) { return false; }
	// AMNOTE: A drag or a simulation of the tool is running
	virtual bool unk0131() { return false; }
	// AMNOTE: unk0132 to unk0135 read only vecPos, so the first two arguments are not known
	virtual bool unk0132( void *pUnk, void *pUnk2, const Vector2D &vecPos ) { return false; }
	virtual bool unk0133( void *pUnk, void *pUnk2, const Vector2D &vecPos ) { return false; }
	virtual bool unk0134( void *pUnk, void *pUnk2, const Vector2D &vecPos ) { return false; }
	virtual bool unk0135( void *pUnk, void *pUnk2, const Vector2D &vecPos ) { return false; }
	// AMNOTE: The mouse moved to vecPos in pView; pHits is the view's CUtlVector of hit records under the cursor
	virtual void unk0136( CMapView *pView, const Vector2D &vecPos, void *pHits ) {}
	// AMNOTE: The mouse entered pView
	virtual void unk0137( CMapView *pView, const Vector2D &vecPos ) {}
	// AMNOTE: The mouse left pView
	virtual void unk0138( CMapView *pView, const Vector2D &vecPos ) {}
	// AMNOTE: Invalidates what the tool draws
	virtual void unk0139();
	// AMNOTE: Once per map view render while the tool is active
	virtual void unk0140() {}
	// AMNOTE: The gizmo transform space changed to nSpace
	virtual void unk0141( int nSpace ) {}
	// AMNOTE: No tool overrides it, so its arguments are not known
	virtual void unk0142() {}
	// AMNOTE: The cursor over pView, NULL for the view's own
	virtual QCursor *unk0143( CMapView *pView ) { return nullptr; }
	// AMNOTE: A context menu opens over pView; the selection tools first select what is under the cursor
	virtual void unk0144( CMapView *pView ) {}
	// AMNOTE: Adds the tool's entries to the context menu of pView; pEntries is the CUtlVector of menu entries the view then adds
	virtual void unk0145( CMapView *pView, void *pEntries ) {}
	// AMNOTE: The document's grid snap state; tools that override it apply the snapping toggle modifier
	virtual bool unk0146();
	virtual bool unk0147() { return unk0146(); }
	// AMNOTE: Shows or hides the tool's gizmo
	virtual void unk0148( bool bVisible ) {}
	// AMNOTE: The tool's gizmo helper
	virtual void *unk0149() { return nullptr; }
	// AMNOTE: The tool's gizmo
	virtual void *unk0150() { return nullptr; }

public:
	// AMNOTE: The tool's index in the tool manager, -1 until it is registered
	int m_nToolID;
	// AMNOTE: The render proxy that registers the tool's IToolRenderCallbacks and IHitTestable with the document's render scene
	uint64 m_unk111[13];
	// AMNOTE: Set by unk0122, returned by unk0123
	int m_unk112;
	// AMNOTE: Set once the tool manager activated the tool, cleared by unk011 and when the tool is deactivated
	bool m_unk113;
	// AMNOTE: Returned by unk019, set by unk0110
	bool m_unk114;
	// AMNOTE: The primitives the base IToolRenderCallbacks::unk003 draws, cleared when the tool is deactivated
	uint64 m_unk115[11];
	// AMNOTE: Set by unk011
	CHammerEditorSession *m_pSession;
};

// AMNOTE: Incomplete class, only the origin and the drag state are known. A tool that places an object at an origin
class CBaseTool3D : public CBaseTool
{
public:
	// AMNOTE: Returns non-zero when vecPos in pView is over the tool's handle
	virtual int unk021( CMapView *pView, const Vector2D &vecPos, int nUnk ) = 0;
	// AMNOTE: Moves the origin to vecOrigin and redraws; false when it did not change
	virtual bool unk022( const Vector &vecOrigin );
	// AMNOTE: Adds the origin to *pPosition
	virtual void unk023( Vector *pPosition ) { *pPosition += m_unk022; }
	// AMNOTE: Ends the drag and redraws
	virtual void unk024( bool bCommit );

public:
	// AMNOTE: Zeroed by the constructor
	uint8 m_unk021[48];
	// AMNOTE: The origin unk022 sets and unk023 adds
	Vector m_unk022;
	uint8 m_unk023[12];
	// AMNOTE: A drag is running; returned by unk018, cleared by unk024
	bool m_unk024;
	// AMNOTE: m_unk025 to m_unk028 are set and cleared by unk0132 to unk0135, m_unk0211 is written by unk0136
	bool m_unk025;
	bool m_unk026;
	bool m_unk027;
	bool m_unk028;
	Vector2D m_unk029;
	Vector2D m_unk0210;
	Vector2D m_unk0211;
};

// AMNOTE: Incomplete class, only the click state and the lasso translation are known. A tool that selects objects by
// click, box and lasso
class CBaseSelectionTool : public CBaseTool
{
public:
	// AMNOTE: The selection bounds are shown
	virtual bool unk021();
	// AMNOTE: False leaves pNode out of a box selection
	virtual bool unk022( CMapNode *pNode ) { return true; }

public:
	// AMNOTE: The document's active selection set, fetched when the tool becomes active
	void *m_unk021;
	bool m_unk022;
	// AMNOTE: The click state: 0 idle, 1 held, 2 box or lasso drag
	int m_unk023;
	// AMNOTE: Plat_MSTime() + 500 when the click is held
	int m_unk024;
	uint8 m_unk025[596];
	// AMNOTE: The lasso is being moved, from the cursor position m_unk027
	bool m_unk026;
	Vector2D m_unk027;
};

// AMNOTE: The undoable state of a CBaseToolPlane: the plane's three points
class CToolPlaneState : public CBaseUndoable
{
public:
	// AMNOTE: unk001, unk002 and the destructor are the class's own; the others keep CBaseUndoable's default bodies
	virtual IUndoable *unk001() override;
	virtual void unk002( IUndoable *pSource ) override;
	virtual void unk003() override;
	virtual void unk004() override;
	virtual void unk005() override;
	virtual void unk006( bool bUnk ) override;
	virtual void unk007() override;
	virtual bool unk008() override;
	virtual void *unk009() override;
	virtual void unk0010( void *pUnk ) override;
	virtual int unk0011() override;
	virtual void unk0012() override;
	virtual ~CToolPlaneState();

public:
	// AMNOTE: The tool the state belongs to, NULL in a snapshot; restoring a snapshot into it calls the tool's unk022
	CBaseToolPlane *m_pTool;
	// AMNOTE: The points are set
	bool m_unk121;
	// AMNOTE: The plane's rotation about its normal in degrees; a restore keeps it
	float m_unk122;
	Vector m_unk123;
	// AMNOTE: m_unk124 and m_unk125 are the points CBaseToolPlane::m_unk023 0 and 1 select
	Vector m_unk124;
	Vector m_unk125;
};

// AMNOTE: Incomplete class, only the plane state and the drag state are known. A tool that places a plane by three
// points dragged in a 2D view; its table has unk0146 pure, each plane tool has its own
class CBaseToolPlane : public CBaseTool
{
public:
	// AMNOTE: Records m_unk021 into the open undo operation
	virtual void unk021();
	// AMNOTE: The plane changed; called after an undo or a redo restored m_unk021
	virtual void unk022() {}

public:
	CToolPlaneState m_unk021;
	// AMNOTE: The pick distance of a point in pixels, 6
	int m_unk022;
	// AMNOTE: The dragged point: -1 none, 0 or 1 one point, 2 both
	int m_unk023;
	// AMNOTE: A drag is running; returned by unk018
	bool m_unk024;
	// AMNOTE: The last position of the drag
	Vector m_unk025;
};

#endif // BASETOOL_H
