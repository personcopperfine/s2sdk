//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The tools' model and animation export to FBX and DMX
//
//===========================================================================//

#ifndef IEXPORTSYSTEM_H
#define IEXPORTSYSTEM_H
#ifdef _WIN32
#pragma once
#endif

#include <functional>

#include "tier0/platform.h"

//-----------------------------------------------------------------------------
// The options an export object holds. From unk101 to unk1024 each getter returns what the setter after it stored.
// AMNOTE: Which of these virtuals IExportOpts declares and which IExportModel and IExportAnim declare is
// not visible; both implementations have these 32 in this order. The animation export ignores the
// options it has no use for: its setters do nothing and its getters return a constant.
//-----------------------------------------------------------------------------
abstract_class IExportOpts
{
public:
	virtual ~IExportOpts() {}

	virtual bool unk101() = 0;
	virtual void unk102( bool bUnk ) = 0;
	virtual bool unk103() = 0;
	virtual void unk104( bool bUnk ) = 0;
	virtual bool unk105() = 0;
	virtual void unk106( bool bUnk ) = 0;
	virtual bool unk107() = 0;
	virtual void unk108( bool bUnk ) = 0;
	virtual bool unk109() = 0;
	virtual void unk1010( bool bUnk ) = 0;
	// AMNOTE: 2 while unk1014 holds a scale; 0 by default
	virtual int unk1011() = 0;
	virtual void unk1012( int nUnk ) = 0;
	// AMNOTE: The scale unk1014 stored while unk1011 returns 2, otherwise 1.0
	virtual float unk1013() = 0;
	// AMNOTE: A scale other than 0 also sets unk1012( 2 )
	virtual void unk1014( float flScale ) = 0;
	virtual uint8 unk1015() = 0;
	// AMNOTE: The asset browser passes a single bit, 1 << n
	virtual void unk1016( uint8 nUnk ) = 0;
	virtual uint64 unk1017() = 0;
	virtual void unk1018( uint64 nUnk ) = 0;
	virtual int unk1019() = 0;
	// AMNOTE: Values below -1 are stored as -1
	virtual void unk1020( int nUnk ) = 0;
	virtual bool unk1021() = 0;
	virtual void unk1022( bool bUnk ) = 0;
	virtual bool unk1023() = 0;
	virtual void unk1024( bool bUnk ) = 0;
	// AMNOTE: Adds a filter: with nMode 0 a value matches when it has every bit of nValue set, with 1 when it equals nValue
	virtual void unk1025( int nValue, int nMode ) = 0;
	// AMNOTE: Whether nValue matches any filter unk1025 added
	virtual bool unk1026( int nValue ) = 0;
	// AMNOTE: Stores the string IExportSystem::CreateExportModel or CreateExportAnim was given
	virtual void unk1027( const char *pszName ) = 0;
	// AMNOTE: Returns the string unk1027 stored, "" when there is none
	virtual const char *unk1028() = 0;
	// AMNOTE: Stores the function unk1030 calls; the asset browser passes one that appends the text to its export log
	virtual void unk1029( std::function< bool( const char *pszText ) > &&fn ) = 0;
	// AMNOTE: Calls the function unk1029 stored with pszText; false when there is none
	virtual bool unk1030( const char *pszText ) = 0;
	// AMNOTE: A copy of the function unk1029 stored
	virtual std::function< bool( const char *pszText ) > unk1031() = 0;
};

#endif // IEXPORTSYSTEM_H
