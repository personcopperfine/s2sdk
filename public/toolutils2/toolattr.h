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
class IToolAttr_Array;
class IToolAttr_KV3;
class IToolAttr_Map;
class IToolAttr_SaveLoad;
class IToolAttr_Table;
class IToolAttr_Value;
class CToolEditContextQuery_Base;

// An object with an attribute table, the target the property editors show
class HToolAttrTableInstance
{
public:
	uint8 m_unk001[16];
	uint32 m_unk002;
	// AMNOTE: The instance is valid when this and m_unk004 are set
	void *m_unk003;
	// AMNOTE: The attribute table of the object
	IToolAttr_Table *m_unk004;
};

abstract_class IToolAttr_Table
{
public:
	virtual void unk001( const HToolAttrTableInstance &key, CUtlVector< IBaseToolAttr * > *pAttrs ) = 0;
	virtual void unk002( const HToolAttrTableInstance &key, CUtlString *pUnk, CUtlString *pUnk2 ) = 0;
	virtual bool unk003( void *pUnk, CUtlString *pUnk2, void *pUnk3 ) = 0;
	// AMNOTE: The text of the target's row
	virtual bool unk004( const HToolAttrTableInstance &key, CUtlString *pText ) = 0;
	// AMNOTE: The name of the target
	virtual const char *unk005( const HToolAttrTableInstance &key ) = 0;
	virtual bool unk006() = 0;
	virtual bool unk007() = 0;
	virtual bool unk008() = 0;
	virtual HToolAttrTableInstance unk009( const HToolAttrTableInstance &key ) = 0;
	virtual void unk0010( const HToolAttrTableInstance &key, void *pUnk ) = 0;
	virtual void unk0011( const HToolAttrTableInstance &key, void *pUnk ) = 0;
};

// An attribute of an attribute table, what a property editor row shows and edits
// AMNOTE: The target is the object the attribute is read from or written to
abstract_class IBaseToolAttr
{
public:
	virtual ~IBaseToolAttr() {}

	// AMNOTE: The attribute's name
	virtual const char *unk101() = 0;
	// AMNOTE: The name of the class the attribute belongs to. No call site found, the arguments are not proven
	virtual const char *unk102() { return ""; }
	// AMNOTE: The first string unk1022 returns. No call site found, the arguments are not proven
	virtual const char *unk103() { return ""; }
	// AMNOTE: The second string unk1022 returns. No call site found, the arguments are not proven
	virtual const char *unk104() { return ""; }
	// AMNOTE: The attribute's type: 3 a float, 13 an array (unk1010), 14 a table (unk1011), 15 a map (unk1014)
	virtual int unk105( HToolAttrTableInstance target ) = 0;
	// AMNOTE: When this is 8, unk107 gives a name
	virtual int unk106( HToolAttrTableInstance target ) { return 0; }
	virtual const char *unk107( HToolAttrTableInstance target ) { return ""; }
	// AMNOTE: The attribute's metadata, a table the editors look keys such as "readonly_expr" and "suppress_expr" up in.
	// The engine's default returns an empty static value
	virtual KeyValues3 *unk108( HToolAttrTableInstance target ) = 0;
	// AMNOTE: The attribute's value interface, NULL when it has none
	virtual IToolAttr_Value *unk109( HToolAttrTableInstance target ) { return nullptr; }
	// AMNOTE: The attribute's array interface, NULL when it is not an array
	virtual IToolAttr_Array *unk1010( HToolAttrTableInstance target ) { return nullptr; }
	// AMNOTE: The table the attribute's value is, an empty instance when it is not a table
	virtual HToolAttrTableInstance unk1011( HToolAttrTableInstance target ) { return HToolAttrTableInstance(); }
	// AMNOTE: The attribute's KeyValues3 interface, NULL when it has none
	virtual IToolAttr_KV3 *unk1012( HToolAttrTableInstance target ) { return nullptr; }
	// AMNOTE: No call site found, the arguments are not proven
	virtual IToolAttr_SaveLoad *unk1013() { return nullptr; }
	// AMNOTE: The attribute's map interface, NULL when it is not a map
	virtual IToolAttr_Map *unk1014( HToolAttrTableInstance target ) { return nullptr; }
	// AMNOTE: Returns NULL in every class; no call site found, the arguments and the return type are not proven
	virtual void *unk1015() { return nullptr; }
	// AMNOTE: False makes the row read-only
	virtual bool unk1016( HToolAttrTableInstance target ) { return true; }
	virtual bool unk1017( HToolAttrTableInstance target ) { return false; }
	// AMNOTE: True hides the row
	virtual bool unk1018( HToolAttrTableInstance target ) { return false; }
	// AMNOTE: The name the row shows
	virtual void unk1019( HToolAttrTableInstance target, CUtlString *pName ) { pName->Set( unk101() ); }
	virtual int unk1020() { return 0; }
	virtual const char *unk1021() { return ""; }
	// AMNOTE: Two strings the help system looks the attribute up with; true when the second is not empty
	virtual bool unk1022( CUtlString *pUnk, CUtlString *pUnk2 ) { return false; }
	// AMNOTE: Like unk1022 for the target, asked first
	virtual bool unk1023( HToolAttrTableInstance target, CUtlString *pUnk, CUtlString *pUnk2 ) { return false; }
	virtual void unk1024( HToolAttrTableInstance target, CUtlString *pText ) {}
	virtual int unk1025() { return 0; }
	// AMNOTE: The FGD attributes answer from their "required" key
	virtual bool unk1026( HToolAttrTableInstance target ) { return false; }
	// AMNOTE: The FGD attributes answer from their "important" key
	virtual bool unk1027() { return false; }
	// AMNOTE: The FGD attributes answer from their "participates_in_undo" key
	virtual bool unk1028( HToolAttrTableInstance target ) { return true; }
	virtual bool unk1029( HToolAttrTableInstance target, bool *pUnk ) { *pUnk = false; return false; }
	// AMNOTE: Removes a value the class does not expect, the row's "remove_attr" command
	virtual bool unk1030( HToolAttrTableInstance target ) { return false; }
	// AMNOTE: 1 the value overrides a base node's, 2 it is inherited from a base node, 3 it is read-only
	virtual int unk1031( HToolAttrTableInstance target ) { return 0; }
	// AMNOTE: True overrides the base node's value, false inherits it again
	virtual void unk1032( HToolAttrTableInstance target, bool bUnk ) {}
	virtual bool unk1033( HToolAttrTableInstance target, bool *pUnk ) { *pUnk = false; return false; }
	// AMNOTE: Resets the value to its default, the row's "reset_attr" command
	virtual bool unk1034( HToolAttrTableInstance target ) { return false; }
	virtual bool unk1035( HToolAttrTableInstance target ) { return false; }
	// AMNOTE: Copies the attribute's value from source to target
	virtual bool unk1036( HToolAttrTableInstance source, HToolAttrTableInstance target ) { return false; }
	// AMNOTE: Adds the row's commands to pCommands, a CUtlVector of 96-byte entries
	virtual void unk1037( HToolAttrTableInstance target, void *pCommands ) {}
	// AMNOTE: Runs one of the row's commands, 1 is success
	virtual int unk1038( HToolAttrTableInstance target, const char *pszCommand ) { return 0; }
	// AMNOTE: unk1038 for an element below an array, asked first when the path is not empty
	virtual int unk1039( HToolAttrTableInstance target, const char *pszCommand, const CUtlVector< int > *pPath ) { return 0; }
	// AMNOTE: A colour for the row
	virtual bool unk1040( HToolAttrTableInstance target, uint32 *pUnk ) { return false; }
	virtual bool unk1041( HToolAttrTableInstance target, CUtlString *pText ) { return false; }
	virtual bool unk1042( HToolAttrTableInstance target ) { return false; }
	// AMNOTE: The row's alert text; the FGD attributes answer from their "alert_func" key
	virtual bool unk1043( HToolAttrTableInstance target, CUtlString *pText ) { return false; }
	// AMNOTE: The engine has a default body
	virtual CUtlString unk1044( HToolAttrTableInstance target ) = 0;
	virtual void unk1045( HToolAttrTableInstance target, int nUnk ) {}
	virtual void unk1046( HToolAttrTableInstance target, int nUnk ) {}
	// AMNOTE: No call site found, the arguments are not proven
	virtual void unk1047() {}
	virtual bool unk1048( HToolAttrTableInstance target ) { return false; }
	virtual bool unk1049( HToolAttrTableInstance target ) { return false; }
	// AMNOTE: Fills the context a picker opens with
	virtual void unk1050( HToolAttrTableInstance target, CToolEditContextQuery_Base *pQuery ) {}
};

abstract_class IToolAttrNotifyRoot
{
public:
	virtual void unk001( void *pUnk, void *pUnk2 ) = 0;
	virtual void unk002( void *pUnk, void *pUnk2 ) = 0;
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
