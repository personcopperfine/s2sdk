//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: Creates the tool scene nodes that show a map (.vmap) inside a tool scene
//
//===========================================================================//

#ifndef ITOOLSCENENODEFACTORY_H
#define ITOOLSCENENODEFACTORY_H
#ifdef _WIN32
#pragma once
#endif

#include "appframework/iappsystem.h"
#include "tier0/utlstring.h"

class CToolScene;
class CToolSceneNode;

//-----------------------------------------------------------------------------
// A map (.vmap) and its 3D skybox map shown in a tool scene
//-----------------------------------------------------------------------------
abstract_class IToolSceneVmapNode
{
public:
	// The scene node this map is
	virtual CToolSceneNode *GetNode() = 0;

	// Removes the map from the node's scene, loads pszMapName and, with bLoadSkybox, the map named by the targetMapName key
	// of its skybox_reference entity, then adds the map back to the node's scene. On failure pError (when not NULL)
	// gets the message and false is returned.
	// AMNOTE: bUnk is handed to both map documents after they load
	virtual bool LoadMap( const char *pszMapName, bool bUnk, bool bLoadSkybox, CUtlString *pError ) = 0;

	// Registers the scene worlds of the map (and of its skybox map) with pScene; NULL is ignored
	virtual void AddToToolScene( CToolScene *pScene ) = 0;

	// Removes what AddToToolScene registered with pScene; NULL is ignored
	virtual void RemoveFromToolScene( CToolScene *pScene ) = 0;
};

//-----------------------------------------------------------------------------
// The tool scene node factory ("ToolSceneNodeFactory_001")
//-----------------------------------------------------------------------------
abstract_class IToolSceneNodeFactory : public IAppSystem
{
public:
	// Creates an empty map node in pScene under pParent (the scene's root node when NULL); NULL when out of memory
	virtual IToolSceneVmapNode *CreateVmapNode( CToolScene *pScene, CToolSceneNode *pParent ) = 0;

	// Deletes a map node made by CreateVmapNode; NULL is ignored
	virtual void DestroyVmapNode( IToolSceneVmapNode *pNode ) = 0;

	// AMNOTE: The implementation's last virtual is its destructor; whether the interface or only the implementing class declares it is not known
	virtual ~IToolSceneNodeFactory() {}
};

#endif // ITOOLSCENENODEFACTORY_H
