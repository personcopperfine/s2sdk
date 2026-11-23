//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The filter a tool's filtered tree widget tests its items with
//
//===========================================================================//

#ifndef TREEWIDGETFILTER_H
#define TREEWIDGETFILTER_H
#ifdef _WIN32
#pragma once
#endif

#include "tier0/platform.h"

class QTreeWidgetItem;

//-----------------------------------------------------------------------------
// The base of CTreeWidgetFilter_Regexp and CTreeWidgetFilter_KeywordList. The
// filters have no virtual destructor; the widget builds them on its stack
//-----------------------------------------------------------------------------
abstract_class CTreeWidgetFilter
{
public:
	// AMNOTE: Whether the filter lets every item through: no object at m_unk001 and an empty pattern or keyword list
	virtual bool unk001() = 0;
	// AMNOTE: Whether the item passes the filter in the column: the item's data of every role in the role list is tested
	virtual bool unk002( QTreeWidgetItem *pItem, int nColumn ) = 0;

public:
	// AMNOTE: An object the filters ask first: when it is set and its first virtual returns false, the
	// item is rejected. Its type is not known
	void *m_unk001;
	// AMNOTE: The number of roles in the list at m_unk003
	int m_unk002;
	// AMNOTE: The item data roles the filter tests, not owned
	const int *m_unk003;
};

#endif // TREEWIDGETFILTER_H
