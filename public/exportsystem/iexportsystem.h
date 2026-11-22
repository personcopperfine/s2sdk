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
#include "mathlib/mathlib.h"
#include "resourcefile/resourcetype.h"
#include "tier0/utlbuffer.h"
#include "tier0/utlstring.h"
#include "tier0/utlvector.h"

class CMesh;
class CModel;
class CRenderMesh;
class IErrorListener;

// AMNOTE: A model resource; the engine's error text names the type HModel
typedef ResourceHandle_t HModel;

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

//-----------------------------------------------------------------------------
// A model export, made by IExportSystem::CreateExportModel and freed with delete. Its scene is
// filled from a source file, a buffer, model resources or meshes, then written as FBX.
//-----------------------------------------------------------------------------
abstract_class IExportModel : public IExportOpts
{
public:
	// AMNOTE: Unserializes DMX data from buf (pFileName is the file name the datamodel is given) and adds its
	// root element to the scene; pPathID goes to the file times read for the scene's info
	virtual bool unk011( CUtlBuffer &buf, const char *pFileName, const char *pPathID, IErrorListener *pErrorListener ) = 0;
	// AMNOTE: Loads a model source file into the scene
	virtual bool unk012( const char *pFileName, const char *pPathID, CUtlString *pError ) = 0;
	// AMNOTE: Adds a mesh to the scene; pSkeletonPose is optional and has the type unk014 takes
	virtual bool unk013( CMesh *pMesh, CRenderMesh *pRenderMesh, const void *pSkeletonPose, CUtlString *pError ) = 0;
	// AMNOTE: Adds a skeleton and its bind pose to the scene; the type of pSkeletonPose is not known, its first member is an int count
	virtual bool unk014( const void *pSkeletonPose, CUtlString *pError ) = 0;
	// AMNOTE: Adds a model to the scene; pBoneTransforms is optional and used only when it has one matrix per bone
	virtual bool unk015( const CModel *pModel, const CUtlVector< matrix3x4_t > *pBoneTransforms, CUtlString *pError ) = 0;
	// AMNOTE: Adds a model to the scene; pBoneTransforms is optional and used only when it has one matrix per bone
	virtual bool unk016( HModel hModel, const CUtlVector< matrix3x4_t > *pBoneTransforms, CUtlString *pError ) = 0;
	// AMNOTE: Starts an animation named pszName of nFrames frames at nFrameRate frames per second (at least 1) on
	// the model's skeleton; false when the scene has none or the name is taken
	virtual bool unk017( HModel hModel, const char *pszName, int nFrames, int nFrameRate ) = 0;
	// AMNOTE: Sets frame nFrame of the animation pszName from one bone transform per bone: a CUtlVector of
	// 32-byte elements, position, a scale and a rotation quaternion
	virtual bool unk018( const char *pszName, int nFrame, const void *pBoneTransforms ) = 0;
	// AMNOTE: Finishes the animation pszName: filters its curves
	virtual bool unk019( const char *pszName ) = 0;
	// AMNOTE: Writes the scene as FBX
	virtual bool unk0110( const char *pFileName, const char *pPathID, CUtlString *pError ) = 0;
};

#endif // IEXPORTSYSTEM_H
