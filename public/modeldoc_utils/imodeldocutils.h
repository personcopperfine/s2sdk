//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The ModelDoc library outside the editor: reads model source files,
// resolves ModelDoc documents and imports older model formats
//
//===========================================================================//

#ifndef IMODELDOCUTILS_H
#define IMODELDOCUTILS_H
#ifdef _WIN32
#pragma once
#endif

#include "appframework/iappsystem.h"
#include "tier0/utlbuffer.h"
#include "tier0/utlstring.h"

class CModelDoc;
class CModelDocNode;
class IModelDocLoaderUtils;

//-----------------------------------------------------------------------------
// The ModelDoc utilities ("ModelDocUtils001")
//-----------------------------------------------------------------------------
abstract_class IModelDocUtils : public IAppSystem
{
public:
	// The file loader and cache the source files of a document are loaded through
	virtual IModelDocLoaderUtils *GetLoaderUtils() = 0;

	// AMNOTE: Copies pSource into pTarget and resolves its prefabs and references there; returns false when a node fails to resolve.
	// pParams is a 0x30 byte block whose int at +0x28 is a mode: 0 copies every node, 1 and 2 leave out the animation nodes
	virtual bool unk101( const void *pParams, CModelDoc *pSource, CModelDoc *pTarget ) = 0;
	// AMNOTE: The same as unk101, in place
	virtual bool unk102( const void *pParams, CModelDoc *pDoc ) = 0;
	// AMNOTE: Resolves a copy of pDoc and fills pOut, a CUtlVector of 0x220 byte mesh records, with its render meshes and their transforms.
	// A non-zero nMode filters the meshes; returns false when the resolve fails
	virtual bool unk103( int nMode, CModelDoc *pDoc, void *pOut ) = 0;
	// AMNOTE: Builds pDoc from a pre-ModelDoc VMDL. pOptions starts with a CUtlString * that receives the errors and warnings
	// as text, followed by string lists that receive more results; returns false when there was an error
	virtual bool unk104( CModelDoc *pDoc, const char *, const char *, const char *, void *pOptions ) = 0;
	// AMNOTE: Add the nodes of a collision file and of a constraint file to pDoc; errors and warnings come back in pMessages
	virtual bool unk105( CModelDoc *pDoc, const char *pFileName, CUtlString *pMessages ) = 0;
	virtual bool unk106( CModelDoc *pDoc, const char *pFileName, CUtlString *pMessages ) = 0;
	// AMNOTE: The same as unk104, from a compiled model or a Source 1 MDL
	virtual bool unk107( CModelDoc *pDoc, const char *, const char *, const char *, void *pOptions ) = 0;
	// AMNOTE: False, with a warning, when the source animation of the simulation cannot be baked
	virtual bool unk108( const void *pParams ) = 0;

	// The file the model archetypes are read from
	virtual const char *GetArchetypeListFileName() = 0;
	// Whether the archetype, or the archetype it is based on, suppresses the warning (with or without its "suppress_warning_" prefix)
	virtual bool IsWarningSuppressed( const char *pArchetype, const char *pWarning ) = 0;

	// AMNOTE: Loads a model source file and serializes it as binary DMX into pOut; the other arguments are handed to the model file loader
	virtual bool unk201( const char *pFileName, float, const char *, float, CUtlBuffer *pOut ) = 0;
	// AMNOTE: A value read from the animation pNode's source file loads; flDefault when the file does not load
	virtual float unk202( CModelDocNode *pNode, float flDefault ) = 0;

	// AMNOTE: Writes a mesh as an FBX file; false when either argument is null
	virtual bool WriteFbxMesh( const void *pMesh, const char *pFileName ) = 0;
};

#endif // IMODELDOCUTILS_H
