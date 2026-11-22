//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: Prefabs of a Hammer map document
//
//===========================================================================//

#ifndef MAPPREFAB_H
#define MAPPREFAB_H
#ifdef _WIN32
#pragma once
#endif

#include "mapdoclib/mapdoc.h"
#include "mapdoclib/mapinstance.h"
#include "tier0/utlstring.h"
#include "tier0/platform.h"

// AMNOTE: Incomplete class, only the prefab's map file and its options are known
class CMapPrefab : public CMapInstance, public IMapFileReference
{
public:
	// AMNOTE: The prefab's map file
	CUtlString m_TargetMapPath;
	// AMNOTE: The prefab's target name (the tool attribute "m_EntityIOTargetName"), the entity name prefix when
	// m_bUseTargetnameAsPrefix is set
	CUtlString m_unk161;
	bool m_bFixupEntityNames;
	bool m_bUseTargetnameAsPrefix;
	bool m_bLoadIfNested;
	bool m_bLoadAtRuntime;
	bool m_bPrefabRuntimeEntity;
	// AMNOTE: The attribute variables "variableOverrideNames" and "variableOverrideValues"
	uint8 m_unk261[67];
	// AMNOTE: The root element of the prefab's map
	CMapRootElement *m_unk262;
	uint8 m_unk263[24];
};

#endif // MAPPREFAB_H
