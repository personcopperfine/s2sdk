//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The property editor domain over the tools' attribute tables, the base of the tools' domains
//
//===========================================================================//

#ifndef TOOLATTR_PROPERTYDOMAIN_H
#define TOOLATTR_PROPERTYDOMAIN_H
#ifdef _WIN32
#pragma once
#endif

#include "tier0/platform.h"
#include "toolutils2/toolattr.h"
#include "propertyeditor/ipropertyeditorsystem.h"

class IBaseToolAttr;

// AMNOTE: Incomplete class
class CToolAttrPropertyDomain : public IPropertyEditDomain
{
public:
	// AMNOTE: True leaves the attribute out of the target's rows
	virtual bool unk011( IBaseToolAttr *pAttr, const HToolAttrTableInstance &target ) { return false; }
	// AMNOTE: Copied into the attribute information unk106 fills
	virtual bool unk012() { return false; }

public:
	uint64 m_unk001;
	bool m_bEditorRebuildNeeded;
	// AMNOTE: True by default
	bool m_unk101;
	// AMNOTE: IsReadOnly returns it
	bool m_unk102;
	uint64 m_unk103[4];
};

#endif // TOOLATTR_PROPERTYDOMAIN_H
