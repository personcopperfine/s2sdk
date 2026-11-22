//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose:
//
// $NoKeywords: $
//
//===========================================================================//

#ifndef ITOOLSERVICE_H
#define ITOOLSERVICE_H

#ifdef _WIN32
#pragma once
#endif

#include "engine2/iengineservicemgr.h"
#include "mathlib/vector.h"
#include "resourcefile/resourcetype.h"
#include "tier0/basetypes.h"
#include "tier0/buffer_string.h"
#include "tier0/utlstring.h"
#include "tier0/utlvector.h"

class CNavData;
class INavListener;
class IToolGameSimulationAPI;
class IToolClientSimulationAPI;
class CEntityClass;
class CProjectedTextureBase;
class ISceneWorld;
class CSceneObject;
class CSceneLightObject;
class CSceneBarnLightObject;
struct LightDesc_t;
struct matrix3x4_t;

// AMNOTE: Placeholder for the weak resource handle IToolService::unk302 returns by value; it must stay trivially copyable
struct ToolServiceUnk8_t
{
	ResourceHandle_t m_pBinding;
};

// AMNOTE: The game's services for the tools. Most methods forward to ISource2Server or ISource2Client
// and return 0, false or nothing when that interface is not loaded
abstract_class IToolService : public IEngineService
{
public:
	// AMNOTE: Adds the line to the engine's command buffer, only while the tool framework is loaded
	virtual void unk001( const char *pszCommand ) = 0;
	// AMNOTE: The connected network client's map name, else ISource2Server::GetActiveWorldName, else an empty string
	virtual const char *unk002( void ) = 0;
	// AMNOTE: True when the network game client exists and its state is 6
	virtual bool unk003( void ) = 0;

	virtual bool IsPaused( void ) const = 0;
	virtual bool GetNavMeshData( CNavData *pNavMeshData ) = 0;
	virtual void SetNavMeshData( const CNavData *navMeshData ) = 0;
	// AMNOTE: False when the listener is registered already or the server holds 16
	virtual bool RegisterNavListener( INavListener *pNavListener ) = 0;
	virtual void UnregisterNavListener( INavListener *pNavListener ) = 0;
	virtual void GetAnimationActivityList( CUtlVector<CUtlString> &activityList ) = 0;
	virtual void GetAnimationEventList( CUtlVector<CUtlString> &eventList ) = 0;
	virtual IToolGameSimulationAPI *GetToolGameSimulationAPI( void ) = 0;
	virtual IToolClientSimulationAPI *GetToolClientSimulationAPI( void ) = 0;

	// AMNOTE: unk101 to unk108 create, update and delete the projected textures and lights of particles.
	// Creates the projected texture in *ppTexture when it is NULL, then applies pDesc to it
	virtual void unk101( const void *pDesc, CProjectedTextureBase **ppTexture ) = 0;
	// AMNOTE: Deletes the projected texture
	virtual void unk102( CProjectedTextureBase *pTexture ) = 0;
	// AMNOTE: Returns NULL in CS2
	virtual void *unk103( ISceneWorld *pWorld, void *, const Vector &, float, const Vector &, float, float, float, Vector, float, float, float, float, float, void **ppObject ) = 0;
	// AMNOTE: Does nothing in CS2
	virtual void unk104( void *pObject ) = 0;
	// AMNOTE: Creates the light from desc in *ppLight when it is NULL, else updates it from desc; returns it
	virtual CSceneLightObject *unk105( ISceneWorld *pWorld, const LightDesc_t &desc, CSceneLightObject **ppLight ) = 0;
	// AMNOTE: ISceneSystem::DeleteSceneObject
	virtual void unk106( CSceneObject *pObject ) = 0;
	// AMNOTE: The same for a barn light, placed at transform
	virtual CSceneBarnLightObject *unk107( ISceneWorld *pWorld, const void *pBarnLightDesc, const matrix3x4_t &transform, CSceneBarnLightObject **ppLight ) = 0;
	// AMNOTE: ISceneSystem::DeleteSceneObject
	virtual void unk108( CSceneObject *pObject ) = 0;

	// AMNOTE: unk109 to unk121 do nothing in CS2 beyond what their notes say
	virtual void unk109( const char *, bool, bool, CUtlVector<CUtlString> &, void * ) = 0;
	virtual void unk110( void *, bool, bool, CUtlVector<CUtlString> &, void * ) = 0;
	virtual void unk111( const char *, const char *, bool, bool, bool, void *pOut ) = 0;
	virtual void unk112( const void *, const char *, bool, bool, bool, void *pOut ) = 0;
	// AMNOTE: Returns 0
	virtual int unk113( const char * ) = 0;
	// AMNOTE: Returns 1.0
	virtual float unk114( const char *, bool ) = 0;
	// AMNOTE: Returns 1.0
	virtual float unk115( void *, bool ) = 0;
	virtual void unk116( void *, bool, void *pOut ) = 0;
	// AMNOTE: Empties out and returns false
	virtual bool unk117( void *, int, CBufferString &out ) = 0;
	virtual void unk118( void * ) = 0;
	// AMNOTE: Empties out
	virtual void unk119( void *, CBufferString &out ) = 0;
	virtual void unk120( void *, void *, const Vector &, int, float, float, float ) = 0;
	// AMNOTE: Returns false
	virtual bool unk121( void *, void *, void * ) = 0;
	// AMNOTE: The client's econ item system
	virtual void *unk122( void ) = 0;

	virtual void *GetEconItemSystem( void ) = 0;

	// AMNOTE: Releases the reference in *phResource and clears every output; does nothing else in CS2
	virtual void unk201( void *, ResourceHandle_t *phResource, int *, void **, void ** ) = 0;
	// AMNOTE: Dispatches an engine event with true; unk203 dispatches it with false
	virtual void unk202( void ) = 0;
	virtual void unk203( void ) = 0;

	virtual void GetHitGroupInfo( CUtlVector<int> &groupIDs, CUtlVector<CUtlString> &groupNames ) = 0;

	// AMNOTE: Returns NULL in CS2
	virtual void *unk301( int ) = 0;
	// AMNOTE: Returns an empty handle in CS2
	virtual ToolServiceUnk8_t unk302( void * ) = 0;
	// AMNOTE: Whether the client's value it asks for is not -1, false without a network game client
	virtual bool unk303( void ) = 0;
	// AMNOTE: Forces rendering for the next frames, then returns IRenderService::GetSceneWorld once the world is fully loaded, else NULL
	virtual ISceneWorld *unk304( void ) = 0;
	// AMNOTE: The same check, then a client view render query for nSlot; -1 is the active split screen slot
	virtual void *unk305( CSplitScreenSlot nSlot ) = 0;
	// AMNOTE: -1 is the active split screen slot
	virtual float unk306( CSplitScreenSlot nSlot ) = 0;
	virtual void unk307( void *pOut ) = 0;

	virtual const char *GetVDataClassName( const char *pszName, const char *pszScopeFile ) = 0;
	virtual const char *GetVDataClassNameByDataType( const char *pszName, const char *pszGenericDataType ) = 0;
	virtual const CUtlVector<CUtlString> &GetSubclassNamesInScope( const char *pszScopeFile ) = 0;
	virtual const CUtlVector<CUtlString> &GetSubclassNamesInScopeByDataType( const char *pszGenericDataType ) = 0;
	virtual void GetAllSubclassNames( CUtlVector<CUtlString> &names ) = 0;
	virtual const char *GetSubclassDesignerName( const char *pszSubclassName ) = 0;
	virtual const CUtlVector<CUtlString> &GetDesignerNamesForClass( const char *pszClassName ) = 0;
	// AMNOTE: Does nothing in CS2
	virtual void unk401( void *, void * ) = 0;
	virtual void *unk402( void ) = 0;
	virtual const char *GetNativeClassForScriptClass( const char *pszScriptClassName ) = 0;
	virtual CEntityClass *GetScriptClassForDesignerName( const char *pszDesignerName ) = 0;
	virtual bool IsScriptClassDerivedFrom( const char *pszDesignerName, const char *pszBaseName ) = 0;

	// AMNOTE: Does nothing in CS2
	virtual void unk501( const char *, void *pOut ) = 0;
	// AMNOTE: unk502 and unk503 queue a screenshot write
	virtual void unk502( void *, void * ) = 0;
	virtual void unk503( void *, int, void * ) = 0;
	// AMNOTE: Builds the next free screenshot file name
	virtual void unk504( const char *pszSubDir, const char *pszExtension, CUtlString &sFileName ) = 0;
	// AMNOTE: These four do nothing in CS2
	virtual void unk505( void ) = 0;
	virtual void unk506( void ) = 0;
	virtual void unk507( void ) = 0;
	virtual void unk508( void ) = 0;
	virtual uint16 unk509( int ) = 0;
	// AMNOTE: Does nothing for 0
	virtual void unk510( uint16 ) = 0;
};

#endif // ITOOLSERVICE_H
