//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The tools' database of every asset in the search paths: files, types, mods,
//          tags, working sets, change detection, recompiles and checkouts
//
//===========================================================================//

#ifndef IASSETSYSTEM_H
#define IASSETSYSTEM_H
#ifdef _WIN32
#pragma once
#endif

#include "appframework/iappsystem.h"
#include "resourcefile/resourcetype.h"
#include "tier0/utlstring.h"
#include "tier0/utlvector.h"

class IAsset;
class IAssetType;
class IAssetDir;
class ISubasset;
class ISubassetType;
class IWorkingSet;
class IAssetCacheListener;
class IAssetFileListener;
class IAssetFingerprintListener;
class IAssetTagListener;

// AMNOTE: Incomplete struct, only the members InitializeAssetSystem reads are known
struct AssetSystemInitSettings_t
{
	// AMNOTE: Copied into a string the asset system keeps
	const char *m_unk001;
	// AMNOTE: When set, the saved asset databases are loaded at start-up; unk201 returns it
	bool m_unk002;
	bool m_unk003;
	// AMNOTE: unk203 returns it
	bool m_unk004;
	bool m_unk005;
	bool m_unk006;
	bool m_unk007;
};

//-----------------------------------------------------------------------------
// The asset system ("AssetSystem001")
//-----------------------------------------------------------------------------
abstract_class IAssetSystem : public IAppSystem
{
public:
	// The working sets: the system's own, then the ones added with AddWorkingSet
	virtual int GetWorkingSetCount() = 0;
	virtual IWorkingSet *GetWorkingSet( int nIndex ) = 0;
	// Case-insensitive; NULL when no set has the name
	virtual IWorkingSet *FindWorkingSetByName( const CUtlString &name ) = 0;
	// Creates and saves a set named by MakeUniqueWorkingSetName ("Unnamed" for an empty name)
	virtual IWorkingSet *CreateWorkingSet( const CUtlString &name ) = 0;
	// Destroys a set made by CreateWorkingSet; false when the set refuses deletion
	virtual bool DeleteWorkingSet( IWorkingSet *pWorkingSet ) = 0;
	// Lists a set the caller owns; RemoveWorkingSet unlists it without destroying it
	virtual void AddWorkingSet( IWorkingSet *pWorkingSet ) = 0;
	virtual void RemoveWorkingSet( IWorkingSet *pWorkingSet ) = 0;
	// Saves the sets when needed and reports the set as changed on the next RunFrame
	virtual void OnWorkingSetChanged( IWorkingSet *pWorkingSet ) = 0;
	virtual IWorkingSet *GetAllAssetsWorkingSet() = 0;
	virtual IWorkingSet *GetMostRecentlyUsedWorkingSet() = 0;

	// AMNOTE: Returns 0; its arguments and return type are not known
	virtual void *unk001() = 0;

	// Appends " (n)" to name until no working set has it
	virtual void MakeUniqueWorkingSetName( const CUtlString &name, CUtlString *pOutName ) = 0;

	// An absolute, a "GAME"-relative or a fake path to its asset
	virtual IAsset *FindAssetByFilename( const char *pszFileName ) = 0;
	// A relative asset name to its asset; NULL for an absolute path
	virtual IAsset *FindAssetByName( const char *pszName ) = 0;

	// AMNOTE: Like FindAssetByName, through another lookup of the name
	virtual IAsset *unk101( const char *pszName ) = 0;

	// Splits pszText at line breaks, spaces, tabs, commas and semicolons and appends each asset found once
	virtual void FindAssetsInText( const char *pszText, CUtlVector< IAsset * > *pAssets ) = 0;
	// The assets' names, one per line
	virtual void AssetNamesToString( const CUtlVector< IAsset * > &assets, CUtlString *pOut ) = 0;
	// 0 is "Game", 1 is "Content"
	virtual const char *GetSearchPathTypeName( int nSearchPathType ) = 0;
	virtual IAssetType *FindAssetTypeByExtension( const CUtlString &extension ) = 0;
	virtual IAssetType *FindAssetTypeByExtensionPsz( const char *pszExtension ) = 0;
	// Case-insensitive
	virtual IAssetType *FindAssetTypeByName( const CUtlString &name ) = 0;
	virtual IAssetType *FindAssetTypeByNamePsz( const char *pszName ) = 0;
	// Replaces the list's contents
	virtual void GetAssetTypes( CUtlVector< IAssetType * > *pAssetTypes ) = 0;
	virtual IAssetType *FindAssetTypeByResourceType( ResourceType_t nResourceType ) = 0;
	// Appends the mod names
	virtual void GetModNames( CUtlVector< CUtlString > *pModNames ) = 0;
	// Queues a reload of each asset ("Manual Reload")
	virtual void ReloadAssets( const CUtlVector< IAsset * > &assets ) = 0;
	// Recompiles each asset in order under one progress notification; false when one failed
	// AMNOTE: nMode is passed on to each asset's recompile
	virtual bool RecompileAssets( const CUtlVector< IAsset * > &assets, int nMode ) = 0;
	// Handles a change of the file at once; returns its asset
	virtual IAsset *NotifyFileChanged( const CUtlString &fileName ) = 0;

	// Listeners are called from RunFrame
	virtual void AddAssetCacheListener( IAssetCacheListener *pListener ) = 0;
	virtual void RemoveAssetCacheListener( IAssetCacheListener *pListener ) = 0;
	virtual void AddAssetFileListener( IAssetFileListener *pListener ) = 0;
	virtual void RemoveAssetFileListener( IAssetFileListener *pListener ) = 0;
	virtual void AddAssetFingerprintListener( IAssetFingerprintListener *pListener, IAsset *pAsset ) = 0;
	virtual void RemoveAssetFingerprintListener( IAssetFingerprintListener *pListener, IAsset *pAsset ) = 0;

	virtual void InitializeAssetSystem( const AssetSystemInitSettings_t *pSettings ) = 0;
	// Handles file changes, finished compiles, the listeners and the queued reloads
	virtual void RunFrame() = 0;
	// Opens the assets' files for edit in Perforce; assets in a read-only mod are skipped
	virtual void OpenForEdit( const CUtlVector< IAsset * > &assets, int nSearchPathType ) = 0;

	// AMNOTE: Return start-up settings
	virtual bool unk201() = 0;
	virtual bool unk202() = 0;
	virtual bool unk203() = 0;
	// AMNOTE: Writes a ", "-joined description into pOut; false when there is none
	virtual bool unk204( CUtlString *pOut ) = 0;
	virtual void *unk205( int nIndex ) = 0;

	// The CRC of an asset file (a relative path), cached per file; false when the file is unknown
	virtual bool GetAssetFileCRC( const char *pszFileName, uint32 *pCRC ) = 0;
	// The CRC of any file (an absolute path)
	virtual bool GetFileCRC( const char *pszFileName, uint32 *pCRC ) = 0;
	virtual int UpdateAllAssetFileCRCs( unsigned int nFlags, uint64 *pUnk ) = 0;

	// AMNOTE: Writes the path of the asset file into pOut when not NULL; false when the file is unknown
	virtual bool unk301( const char *pszFileName, CUtlString *pOut ) = 0;

	virtual int GetAssetTypeCount() = 0;
	virtual int GetModCount() = 0;

	// AMNOTE: Maps the mod found by name through a table; *pResult is -1 when there is none
	virtual int *unk401( int *pResult, const char *pszModName ) = 0;
	// AMNOTE: Replaces the list's contents with the names of a string table of the system
	virtual void unk402( CUtlVector< CUtlString > *pNames ) = 0;

	// *pResult is the mod's index, -1 when there is none
	virtual int *FindModByName( int *pResult, const char *pszModName ) = 0;
	virtual const char *GetModName( int nMod ) = 0;
	virtual bool IsModHidden( int nMod ) = 0;
	// Replaces the list's contents with the root path of every mod that is not hidden
	virtual void GetSearchPathRoots( int nSearchPathType, CUtlVector< CUtlString > *pPaths ) = 0;

	// AMNOTE: Does nothing; its arguments are not known
	virtual void unk501() = 0;
	// AMNOTE: The persistent-info serialization of asset lists; pBuffer is the stream
	virtual bool unk502( void *pBuffer, CUtlVector< IAsset * > *pAssets ) = 0;
	virtual void unk503() = 0;
	virtual bool unk504( const CUtlVector< IAsset * > *pAssets, void *pBuffer, bool bUnk ) = 0;
	virtual bool unk505( const CUtlVector< IAsset * > *pAssets, void *pBuffer, bool bUnk ) = 0;
	virtual void unk506() = 0;

	// Writes the asset databases when more than flMinInterval seconds passed since the last flush
	// (always for 0); false when it did not
	virtual bool FlushPersistentInfo( double flMinInterval ) = 0;
	// Compiled child resources whose parents are gone, appended to pAssets when not NULL; bVerbose logs each
	// AMNOTE: pFilter, when not NULL, is asked about each asset (with its reason strings) through its first virtual
	virtual void FindOrphanedAssets( void *pFilter, CUtlVector< IAsset * > *pAssets, bool bVerbose ) = 0;
	// NotifyFileChanged on each file, then RunFrame
	virtual void HandleBatchedFileChanges( const char *const *ppFileNames, int nCount ) = 0;

	// AMNOTE: pResults is a list of 72-byte entries that start with an IAsset *; the result is a virtual of pUnk called with pUnk2
	virtual bool unk601( void *pUnk, void *pUnk2, const void *pResults ) = 0;

	// Writes one mod's asset database; false for a bad index or while saves are suspended
	virtual bool SavePersistentInfoForMod( int nMod ) = 0;
	virtual bool SetModOverrideInfo( const char *pszModName, const char *pszPath ) = 0;

	// Tags are 16-bit ids, 0xFFFF when invalid
	virtual const char *GetTagName( uint16 nTag ) = 0;
	// AMNOTE: The tag's record, NULL for an invalid id
	virtual const void *GetTagInfo( uint16 nTag ) = 0;
	// The tags whose name matches pszName, or contains it for tags without an exact-match flag
	virtual void FindTagsByName( const char *pszName, CUtlVector< uint16 > *pTags ) = 0;
	// Brackets tag changes; the outermost close saves the changed tags
	virtual void SetTagChangeBatch( bool bBegin ) = 0;

	// AMNOTE: Sets a flag of the tag manager
	virtual void unk701( bool bUnk ) = 0;

	// AMNOTE: Each entry is a tag record (see GetTagInfo); the user tags are the ones without an automatic source
	virtual void GetAllTags( CUtlVector< const void * > *pTags ) = 0;
	virtual void GetUserTags( CUtlVector< const void * > *pTags ) = 0;
	// 0xFFFF when no tag has the name
	virtual uint16 FindTagByName( const char *pszName ) = 0;

	// AMNOTE: False on a customer machine, otherwise whether a user tag exists
	virtual bool unk801() = 0;

	virtual void AddAssetTagListener( IAssetTagListener *pListener ) = 0;
	virtual void RemoveAssetTagListener( IAssetTagListener *pListener ) = 0;
	virtual bool IsAssetQueuedForReload( IAsset *pAsset ) = 0;

	// AMNOTE: Appends the assets with a string per-asset info value whose key and value match the wildcards
	virtual void unk901( const char *pszKeyWildcard, const char *pszValueWildcard, CUtlVector< IAsset * > *pAssets ) = 0;

	// FindAssetByFilename, then AddAssetToMostRecentlyUsed
	virtual void AddFileToMostRecentlyUsed( const char *pszFileName ) = 0;
	virtual void AddAssetToMostRecentlyUsed( IAsset *pAsset ) = 0;
	// The sub-asset of the type (by name) with the name (lower-cased)
	virtual ISubasset *FindSubasset( const char *pszSubassetTypeName, const char *pszName ) = 0;
	virtual ISubassetType *FindSubassetType( const char *pszName ) = 0;
	// Replaces the list's contents
	virtual void GetSubassetTypes( CUtlVector< ISubassetType * > *pSubassetTypes ) = 0;

	// AMNOTE: The asset type whose name from another of its virtuals matches, case-insensitive
	virtual IAssetType *unk1001( const char *pszName ) = 0;
	virtual int unk1002() = 0;
	// AMNOTE: Appends the assets whose type returns nValue from one of its virtuals
	virtual void unk1003( CUtlVector< IAsset * > *pAssets, int nValue ) = 0;
	// AMNOTE: The address of a member; the queries of unk1201 compare theirs with it
	virtual void *unk1004() = 0;
	// AMNOTE: Removes from pAssets the assets unk1201 rejects
	virtual void unk1005( CUtlVector< IAsset * > *pAssets, void *pUnk, const void *pUnk2 ) = 0;

	// The asset's index in the most recently used set, -1 when it is not there
	virtual int FindInMostRecentlyUsed( IAsset *pAsset ) = 0;

	// AMNOTE: The asset warnings: unk1101 finds the one whose first member equals *pKey and writes it to *pOut
	virtual void unk1101( const void *pKey, void *pOut ) = 0;
	virtual void unk1102( CUtlVector< void * > *pWarnings ) = 0;

	virtual IAssetDir *GetRootAssetDir() = 0;
	// The root for an empty path, NULL when there is no such directory
	virtual IAssetDir *FindAssetDir( const char *pszPath ) = 0;

	// AMNOTE: Resizes pResults to the number of assets (4 bytes each, set to 1) and runs the queries pUnk2 and pUnk3 on them
	virtual void unk1201( const CUtlVector< IAsset * > *pAssets, void *pResults, void *pUnk, const void *pUnk2, const void *pUnk3 ) = 0;

	// True for paths of the cubemap, resource cache and sparse shadow tree build steps
	virtual bool IsBuildArtifactPath( const char *pszPath ) = 0;
};

#endif // IASSETSYSTEM_H
