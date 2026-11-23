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

// AMNOTE: Placeholder name: what BeginModify hands to the domain's listener
struct ToolAttrDomainModifyUnk_t
{
	const PropEdAttrUnk_t *m_pAttrs;
	int m_nAttrs;
	PropEdModifyType_t m_nType;
};

// Told about the edits a CToolAttrPropertyDomain makes
abstract_class IToolAttrDomainListener
{
public:
	// AMNOTE: BeginModify
	virtual void unk001( const ToolAttrDomainModifyUnk_t &modify ) = 0;
	// AMNOTE: EndModify
	virtual void unk002( const PropEdModifyType_t &nType ) = 0;
	// AMNOTE: An edit set the attribute's value on the target, for an attribute whose IBaseToolAttr::unk1048 is true
	virtual void unk003( HToolAttrTableInstance target, IBaseToolAttr *pAttr ) = 0;
};

// AMNOTE: Incomplete class
class CToolAttrPropertyDomain : public IPropertyEditDomain
{
public:
	// AMNOTE: True leaves the attribute out of the target's rows
	virtual bool unk011( IBaseToolAttr *pAttr, const HToolAttrTableInstance &target ) { return false; }
	// AMNOTE: Copied into the attribute information unk106 fills
	virtual bool unk012() { return false; }

public:
	// AMNOTE: NULL by default
	IToolAttrDomainListener *m_unk001;
	bool m_bEditorRebuildNeeded;
	// AMNOTE: True by default
	bool m_unk101;
	// AMNOTE: IsReadOnly returns it
	bool m_unk102;
	uint64 m_unk103[4];
};

#endif // TOOLATTR_PROPERTYDOMAIN_H
