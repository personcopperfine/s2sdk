//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The subrect editor's document session: the .rect rectangle sets, their undo document and the preview
//
//===========================================================================//

#ifndef SUBRECTEDITOR_SESSION_H
#define SUBRECTEDITOR_SESSION_H
#ifdef _WIN32
#pragma once
#endif

#include "tier0/keyvalues3.h"
#include "tier0/utlstring.h"
#include "tier0/utlvector.h"
#include "tier0/platform.h"
#include "mathlib/vector2d.h"
#include "color.h"
#include "rendersystem/irenderdevice.h"
#include "toolutils2/baseeditorsession.h"
#include "toolutils2/ibindtarget.h"
#include "toolutils2/undohistory.h"

class CQSubrectEditorSessionWindow;
class CSubrectEditorApp;
class IAsset;

// AMNOTE: Placeholder name; identifies a rectangle: the id of its set and its handle in the set
struct SubrectRectangleId_t
{
	int m_unk001;
	int m_unk002;
};

// AMNOTE: Placeholder name; a rectangle of a .rect, in 0..1 of the texture
struct SubrectRectangle_t
{
	SubrectRectangleId_t m_unk001;
	// AMNOTE: A random colour the editor draws it in, not saved
	Color m_unk002;
	Vector2D m_Min;
	Vector2D m_Max;
	Vector2D m_Inset;
	// AMNOTE: The rectangle's "properties" table ("allowRotation", "allowTiling")
	KeyValues3 m_Properties;
};

// AMNOTE: Placeholder name; a named set of rectangles of a .rect
struct SubrectRectangleSet_t
{
	int m_unk001;
	CUtlString m_Name;
	KeyValues3 m_Properties;
	CUtlVector< SubrectRectangle_t > m_Rectangles;
	// AMNOTE: The index into m_Rectangles of each handle, -1 for a free one
	CUtlVector< int > m_unk101;
};

// AMNOTE: What an undo step records of a document: the sets and the selection
class CSubrectDocumentState : public CBaseUndoable
{
public:
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

public:
	CUtlVector< SubrectRectangleSet_t > m_unk001;
	// AMNOTE: The selected rectangles
	CUtlVector< SubrectRectangleId_t > m_unk002;
	// AMNOTE: The index into m_unk001 of the set new rectangles go into, -1 for none
	int m_unk003;
};

// AMNOTE: Incomplete class, it adds no virtual of its own. Its IUndoDoc methods do nothing; its IUndoListener method sets
// m_unk102 after an undo or redo
class CSubrectDocument : public IUndoDoc, public IUndoListener
{
public:
	// AMNOTE: The event target that receives the document's events after m_unk002
	void *m_unk001;
	// AMNOTE: The document's event dispatcher
	uint8 m_unk002[72];
	// AMNOTE: No event is posted while it is above 0
	int m_unk003;
	CSubrectDocumentState m_unk004;
	// AMNOTE: 100 steps; m_unk101 is its partner, the redo history
	CUndoHistory *m_pUndoHistory;
	CUndoHistory *m_unk101;
	// AMNOTE: Set by an edit and after an undo or redo
	bool m_unk102;
};

// AMNOTE: Incomplete class, it adds no virtual of its own
class CSubrectEditorSession : public CSimpleBaseEditorSession, public IBindTarget, public ITextureResidencyListener
{
public:
	// AMNOTE: CToolEventMapRegistrationHelper< CSubrectEditorSession >, the session's event bindings
	uint64 m_unk021[6];
	// AMNOTE: The event target that receives the session's events after m_unk023 (the one the application holds and its
	// sessions share)
	void *m_unk022;
	// AMNOTE: The session's event dispatcher
	uint8 m_unk023[72];
	// AMNOTE: No event is posted while it is above 0
	int m_unk024;
	CQSubrectEditorSessionWindow *m_unk025;
	CSubrectDocument *m_pDoc;
	// AMNOTE: m_unk122 is registered with the event dispatcher of the document m_unk124; m_unk121 is the same event
	// target as m_unk022
	void *m_unk121;
	uint8 m_unk122[72];
	int m_unk123;
	CSubrectDocument *m_unk124;
	// AMNOTE: The preview material, a vmat asset; remembered per file in the tool settings, not saved in the .rect
	IAsset *m_unk125;
	// AMNOTE: The background texture
	HRenderTexture m_unk126;
	bool m_unk127;
	// AMNOTE: The grid size, 1 to 8 (1 the biggest); m_unk127 turns the grid on
	int m_unk128;
};

#endif // SUBRECTEDITOR_SESSION_H
