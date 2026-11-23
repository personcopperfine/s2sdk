//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The selection of a Hammer map document
//
//===========================================================================//

#ifndef SELECTION_H
#define SELECTION_H
#ifdef _WIN32
#pragma once
#endif

#include "mapdoclib/selectionset.h"
#include "toolutils2/undohistory.h"
#include "tier0/utlvector.h"
#include "tier0/platform.h"

class CMapDoc;

// AMNOTE: Incomplete class, only the document, the select mode and the sets are known. Its methods act on the set of
// the current select mode
class CSelection : public IUndoable
{
public:
	virtual ~CSelection();

public:
	CMapDoc *m_pDoc;
	SelectMode_t m_SelectMode;
	uint8 m_unk101[60];
	// AMNOTE: One set per select mode
	ISelectionSet *m_pSelectionSets[SELECT_MODE_COUNT];
	// AMNOTE: The quick-hide sets, at most one of each kind
	CUtlVector< ISelectionSet * > m_QuickHideSets;
};

#endif // SELECTION_H
