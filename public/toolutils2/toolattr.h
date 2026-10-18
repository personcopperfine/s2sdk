//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: Attribute tables the tools' property editors use for a document object
//
//===========================================================================//

#ifndef TOOLATTR_H
#define TOOLATTR_H
#ifdef _WIN32
#pragma once
#endif

#include "tier0/keyvalues3.h"
#include "tier0/utlstring.h"
#include "tier0/utlvector.h"
#include "tier0/platform.h"

class IBaseToolAttr;

// AMNOTE: Layout not known, 40 bytes
struct ToolAttrUnk_t
{
	uint8 m_unk001[40];
};

abstract_class IToolAttr_Table
{
public:
	virtual void unk001( const ToolAttrUnk_t &key, CUtlVector< IBaseToolAttr * > *pAttrs ) = 0;
	virtual void unk002( const ToolAttrUnk_t &key, CUtlString *, CUtlString * ) = 0;
	virtual bool unk003( void *, CUtlString *, void * ) = 0;
	virtual bool unk004( const ToolAttrUnk_t &key, void * ) = 0;
	virtual const char *unk005() = 0;
	virtual bool unk006() = 0;
	virtual bool unk007() = 0;
	virtual bool unk008() = 0;
	virtual ToolAttrUnk_t unk009( const ToolAttrUnk_t &key ) = 0;
	virtual void unk0010( const ToolAttrUnk_t &key, void * ) = 0;
	virtual void unk0011( const ToolAttrUnk_t &key, void * ) = 0;
};

abstract_class IToolAttrNotifyRoot
{
public:
	virtual void unk001( void *, void * ) = 0;
	virtual void unk002( void *, void * ) = 0;
	virtual void *unk003() = 0;
	virtual const char *unk004() = 0;
	virtual bool unk005() = 0;
	virtual int unk006() = 0;
};

// AMNOTE: Document object stored as KeyValues3 and described by a schema class
class CBaseKV3DataWithFGDClass : public IToolAttr_Table
{
public:
	virtual ~CBaseKV3DataWithFGDClass() = 0;
	virtual void *unk111() = 0;
	virtual void *unk112() = 0;
	virtual KeyValues3 *unk113() = 0;
	// AMNOTE: Like unk113, for a change: notifies the document first
	virtual KeyValues3 *unk114() = 0;
	// AMNOTE: unk113()
	virtual KeyValues3 *unk115() = 0;
};

#endif // TOOLATTR_H
