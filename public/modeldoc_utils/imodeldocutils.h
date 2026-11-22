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
#include "tier0/utlvector.h"

class CModelDoc;
class CModelDocNode;

//-----------------------------------------------------------------------------
// The sink the ModelDoc library reports the errors and warnings of a load,
// a resolve or a compile to
//-----------------------------------------------------------------------------
abstract_class IModelDocErrorHandler
{
public:
	virtual bool HasErrors() = 0;
	virtual bool HasWarnings() = 0;
	// pNode is the node the message is about, or NULL
	virtual void ReportError( CModelDocNode *pNode, const char *pszMessage ) = 0;
	virtual void ReportWarning( CModelDocNode *pNode, const char *pszMessage ) = 0;

	// AMNOTE: A stack of nodes the library pushes and pops; a message reported without a node is reported for the last one
	CUtlVector< CModelDocNode * > m_unk001;
};

// What IModelDocLoaderUtils loads a file as
// AMNOTE: The binary names only the type; the enumerators' names are not known
enum LoaderDataType_t
{
	// AMNOTE: Loads nothing
	LOADER_DATA_TYPE_UNK0 = 0,
	LOADER_DATA_TYPE_MESH,				// A source mesh: FBX, DMX, SMD or OBJ
	LOADER_DATA_TYPE_ANIMATION,			// A source animation: DMX, FBX, SMD or RTS
	LOADER_DATA_TYPE_MODELDOC,			// A ModelDoc document or prefab
	LOADER_DATA_TYPE_GEOMETRY_CACHE,	// An Alembic archive
	// AMNOTE: Loads nothing
	LOADER_DATA_TYPE_UNK5,
	// AMNOTE: A source animation too, loaded with a flag the animation loader sets for it
	LOADER_DATA_TYPE_UNK6,
};

//-----------------------------------------------------------------------------
// Told about every file IModelDocLoaderUtils is asked to load
//-----------------------------------------------------------------------------
abstract_class ILoaderUtilsListener
{
public:
	// pszPath is the path LoadFile was given, before the cache is searched
	virtual void OnLoadFile( const char *pszPath, LoaderDataType_t nType ) = 0;
};

// AMNOTE: Which of IModelDocLoaderUtils' virtuals belong to this base is not known, only their order
abstract_class IModelDocProcessingCache
{
public:
	// AMNOTE: The document kept under pKey in the table named pszTable, or NULL
	virtual CModelDoc *unk001( const char *pszTable, const void *pKey ) = 0;
	// AMNOTE: Keeps pDoc under pKey in the table named pszTable and owns it: the document kept there before is deleted,
	// and a full table (8 documents) deletes its least recently used one
	virtual void unk002( const char *pszTable, const void *pKey, CModelDoc *pDoc ) = 0;
};

//-----------------------------------------------------------------------------
// The loader and cache of the files a ModelDoc document uses; a file is kept
// with its path, type and CRC, and a second request for it finds it loaded
//-----------------------------------------------------------------------------
abstract_class IModelDocLoaderUtils : public IModelDocProcessingCache
{
public:
	// Loads a file into a new document, or finds it loaded and unchanged, and adds a reference to it;
	// returns its index, or -1. pszPath is relative to the content roots, pErrors may be NULL.
	// AMNOTE: pszUnk is part of what a loaded file is matched by. With nUnk 1 the messages of a file found
	// loaded are reported for the nodes they were reported for, otherwise for the last node of pErrors
	virtual int LoadFile( const char *pszPath, LoaderDataType_t nType, IModelDocErrorHandler *pErrors, const char *pszUnk, int nUnk ) = 0;
	// Removes a reference LoadFile added; a file that changed on disk is freed with its last reference
	virtual void ReleaseFile( int nIndex ) = 0;
	// The document the file was loaded into; NULL for a bad index
	virtual CModelDoc *GetFileDocument( int nIndex ) = 0;
	// The file's path on disk; NULL for a bad index
	virtual const char *GetFilePath( int nIndex ) = 0;
	// Whether the file was loaded as nType from pszPath and its CRC on disk is still the same
	virtual bool IsFileCurrent( int nIndex, LoaderDataType_t nType, const char *pszPath ) = 0;

	// AMNOTE: The object unk121 keeps; LoadFile calls two of its virtuals with the path of every file it returns
	// and with each of that file's strings
	virtual void *unk111() = 0;
	// AMNOTE: The strings a file was loaded with; the count and a string, 0 and NULL for a bad index
	virtual int unk112( int nIndex ) = 0;
	virtual const char *unk113( int nIndex, int nString ) = 0;

	// A listener is added once
	virtual void AddListener( ILoaderUtilsListener *pListener ) = 0;
	virtual void RemoveListener( ILoaderUtilsListener *pListener ) = 0;

	// Appends the files a DMX source (its makefile) or an FBX source pulls in to pOut; pErrors may be NULL
	virtual void GetAdditionalRelatedFiles( CUtlVector< CUtlString > *pOut, const char *pszPath, IModelDocErrorHandler *pErrors ) = 0;

	virtual void unk121( void *pObject ) = 0;
};

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
