//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The resource compiler: compiles a content file into the resource the game loads
//
//===========================================================================//

#ifndef IRESOURCECOMPILERSYSTEM_H
#define IRESOURCECOMPILERSYSTEM_H
#ifdef _WIN32
#pragma once
#endif

#include "appframework/iappsystem.h"
#include "tier0/buffer_string.h"
#include "tier0/keyvalues.h"
#include "tier0/keyvalues3.h"
#include "tier0/utlbuffer.h"
#include "tier0/utlvector.h"

class IInMemoryCompileResultsListener;
class IResourceCompileFileSystemInterface;

//-----------------------------------------------------------------------------
// What IResourceCompilerSystem::GenerateResourceFile compiles a file with
//-----------------------------------------------------------------------------
struct GenerateResourceFileParams_t
{
	int m_unk001;
	bool m_unk002;
	bool m_unk003;
	// AMNOTE: The compile hints, handed to the compilers
	KeyValues *m_unk004;
	// Compiled instead of the file's content when set
	const CUtlBuffer *m_pOverrideInputData;
	const char *m_unk101;
	const char *m_unk102;
	// AMNOTE: Replace the strings the system holds for the compile when set
	const char *m_unk103;
	const char *m_unk104;
	// AMNOTE: Handed to each compile context of the file
	void *m_unk105;
	// AMNOTE: When set, points to three counters: compiled, skipped and failed; one of them is incremented per compiled resource
	int *m_unk106;
};

// AMNOTE: Name and layout not known: a value and whether it is set, 8 bytes
struct ResourceCompilerUnk8_t
{
	int m_unk001;
	bool m_unk002;
};

// AMNOTE: Name not known: a module's name and the member of its metadata IResourceCompilerSystem::unk201 asked for
struct ResourceCompilerUnk16_t
{
	const char *m_unk001;
	KeyValues3 *m_unk002;
};

//-----------------------------------------------------------------------------
// The resource compiler system ("ResourceCompilerSystem001")
//-----------------------------------------------------------------------------
abstract_class IResourceCompilerSystem : public IAppSystem
{
public:
	// Compiles one file in process; returns false when the compile failed
	virtual bool GenerateResourceFile( const char *pFileName, const GenerateResourceFileParams_t *pParams ) = 0;

	// AMNOTE: Compiles pInputData in place of the file's content; returns false when the compile failed
	virtual bool unk101( const char *pFileName, const CUtlBuffer *pInputData, IInMemoryCompileResultsListener *pListener, KeyValues *pHints ) = 0;

	// AMNOTE: The special dependency queries: each looks the compiler up by its identifier and asks it.
	// When no such compiler exists, a returned value is unset and pOut is set to the dependency's name
	virtual int unk102( const char *, const char *pCompilerIdentifier, const char *pSpecialDependency, int nUserData ) = 0;
	virtual ResourceCompilerUnk8_t unk103( const char *, const char *pCompilerIdentifier, const char *pSpecialDependency, int nUserData ) = 0;
	virtual void unk104( const char *, const char *pCompilerIdentifier, const char *pSpecialDependency, int nUserData, CBufferString *pOut ) = 0;
	virtual ResourceCompilerUnk8_t unk105( const char *, const char *pCompilerIdentifier, const char *, const char *pSpecialInputDependency, KeyValues3 * ) = 0;
	virtual void unk106( const char *, const char *pCompilerIdentifier, const char *, const char *pSpecialInputDependency, CBufferString *pOut ) = 0;

	// Makes the compiles use pTestFS as their file system until it is uninstalled
	virtual void InstallTestFilesystem( IResourceCompileFileSystemInterface *pTestFS ) = 0;
	virtual void UninstallTestFilesystem( IResourceCompileFileSystemInterface *pTestFS ) = 0;

	// AMNOTE: Appends the given member of each module metadata block the system holds
	virtual void unk201( const CKV3MemberName &name, CUtlVector<ResourceCompilerUnk16_t> *pOut ) = 0;
};

#endif // IRESOURCECOMPILERSYSTEM_H
