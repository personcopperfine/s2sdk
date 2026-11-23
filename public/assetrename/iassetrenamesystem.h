//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The tools' asset copy, move, delete and replace service
//
//===========================================================================//

#ifndef IASSETRENAMESYSTEM_H
#define IASSETRENAMESYSTEM_H
#ifdef _WIN32
#pragma once
#endif

#include "appframework/iappsystem.h"
#include "tier0/buffer_string.h"
#include "tier0/utlstring.h"
#include "tier0/utlvector.h"

class IAsset;

// How a copy or move turns an asset name into the new one: a find / replace in the name, a
// destination folder for the file name, a generated base name that keeps the extension, and a
// content folder other than the first CONTENT search path
// AMNOTE: The struct's name is in no binary
struct AssetRenameRules_t
{
	bool m_bReplace;
	CUtlString m_Find;
	CUtlString m_Replace;
	bool m_bDestinationFolder;
	CUtlString m_DestinationFolder;
	bool m_bBaseName;
	CUtlString m_BaseName;
	bool m_bContentFolderOverride;
	CUtlString m_ContentFolderOverride;
	// AMNOTE: Set from a check box of the copy / move window; the rename slots don't read it
	bool m_unk101;
};

// One file of a CopyRenameFiles job: names relative to the content root, paths absolute
// AMNOTE: The struct's name is in no binary
struct AssetCopyRenameFile_t
{
	// AMNOTE: Not read by CopyRenameFiles; callers store the object the entry was made from
	void *m_unk001;
	CUtlString m_OldName;
	CUtlString m_NewName;
	CUtlString m_OldPath;
	CUtlString m_NewPath;
	// Removes the old file after the copy
	bool m_bMove;
};

// AMNOTE: The struct's name is in no binary
struct AssetCopyRenameJob_t
{
	// False runs a preview that only writes the report
	bool m_bExecute;
	CUtlVector< AssetCopyRenameFile_t > m_Files;
	bool m_bOverwrite;
	bool m_bUsePerforce;
	// Compiles every new file after the copy
	bool m_bCompile;
	// When set, the Perforce changelist the files are opened in
	CUtlString m_Changelist;
	// AMNOTE: Not read by CopyRenameFiles; callers store a content folder override here
	CUtlString m_unk101;
};

// AMNOTE: The struct's name is in no binary
struct AssetCopyRenameResult_t
{
	bool m_bSuccess;
	// The files whose references were fixed up, or would be in a preview
	int m_nFixedFiles;
	// The HTML report is appended to it
	CBufferString *m_pReport;
};

//-----------------------------------------------------------------------------
// The asset rename system ("AssetRenameSystem_001"). Every slot that takes assets opens a
// non-modal window on them and returns; the window does the work when the user confirms it.
//-----------------------------------------------------------------------------
abstract_class IAssetRenameSystem : public IAppSystem
{
public:
	// Nothing happens when assets is empty
	virtual void MoveAssets( const CUtlVector< IAsset * > &assets ) = 0;
	// Reports the assets only one map uses and the folders nothing references; nothing happens when assets is empty
	virtual void MoveUnusedAssets( const CUtlVector< IAsset * > &assets ) = 0;
	// Nothing happens when assets is empty
	virtual void CopyAssets( const CUtlVector< IAsset * > &assets ) = 0;
	virtual void DeleteAssets( const CUtlVector< IAsset * > &assets ) = 0;
	virtual void ReplaceAssets( const CUtlVector< IAsset * > &assets ) = 0;
	virtual void ShowAssetStatistics( const CUtlVector< IAsset * > &assets ) = 0;
	// Shows the references of the first asset; nothing happens when assets is empty
	virtual void ShowAssetReferences( const CUtlVector< IAsset * > &assets ) = 0;

	// The last folder name of GetContentRoot's path
	virtual void GetContentModName( CUtlString *pModName ) = 0;
	// The first CONTENT search path
	virtual void GetContentRoot( CUtlString *pContentRoot ) = 0;

	// pNewName gets pszNewName, pOldPath pszOldName's absolute CONTENT path and pNewPath the absolute path of
	// pszNewName, under the rules' content folder override when it is set
	virtual void ComputeDestinationPaths( const AssetRenameRules_t &rules, const char *pszNewName, const char *pszOldName, CUtlString *pNewName, CUtlString *pOldPath, CUtlString *pNewPath ) = 0;
	// Makes the new name of pszOldName by the rules, pszSuffix following a generated base name, then
	// ComputeDestinationPaths
	virtual void ApplyRenameRulesAndComputePaths( const AssetRenameRules_t &rules, const char *pszOldName, const char *pszSuffix, CUtlString *pNewName, CUtlString *pOldPath, CUtlString *pNewPath ) = 0;

	// AMNOTE: The implementation calls itself and never returns; its arguments are not known
	virtual void unk101() = 0;

	// Copies or moves the files without a window, with Perforce when the job says so. Only a new
	// .vpcf file gets its own references fixed up; files that reference an old name are not changed.
	virtual void CopyRenameFiles( const AssetCopyRenameJob_t &job, AssetCopyRenameResult_t *pResult ) = 0;

	// AMNOTE: The implementation's last virtual is its destructor; whether the interface or only the implementing class declares it is not known
	virtual ~IAssetRenameSystem() {}
};

#endif // IASSETRENAMESYSTEM_H
