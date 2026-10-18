//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: An attribute of an element of the datamodel
//
//===========================================================================//

#ifndef DMATTRIBUTE_H
#define DMATTRIBUTE_H
#ifdef _WIN32
#pragma once
#endif

#include "datamodel/idatamodel.h"
#include "tier0/utlsymbollarge.h"
#include "tier0/platform.h"

class CDmElement;

// AMNOTE: Incomplete class, only the members are known (no virtual functions)
class CDmAttribute
{
public:
	// AMNOTE: The next attribute of m_pOwner (the list starts at CDmElement::m_pAttributes)
	CDmAttribute *m_pNext;
	void *m_pData;
	CDmElement *m_pOwner;
	DmAttributeHandle_t m_Handle;
	// AMNOTE: The low 6 bits are the DmAttributeType_t
	uint32 m_nFlags;
	CUtlSymbolLarge m_Name;
};

#endif // DMATTRIBUTE_H
