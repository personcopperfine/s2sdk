//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: Types of the datamodel's attributes
//
//===========================================================================//

#ifndef DMATTRIBUTETYPES_H
#define DMATTRIBUTETYPES_H
#ifdef _WIN32
#pragma once
#endif

#include "tier0/uniqueid.h"
#include "datamodel/dmelementhandle.h"

typedef UniqueId_t DmObjectId_t;

// AMNOTE: The attribute type; stored in the low 6 bits of CDmAttribute::m_nFlags, the values are not known
enum DmAttributeType_t : int;

#endif // DMATTRIBUTETYPES_H
