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

class CToolScene;
class CToolSceneNode;
class IToolSceneVmapNode;

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
