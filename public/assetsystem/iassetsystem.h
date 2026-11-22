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
#include "tier0/utlbuffer.h"
#include "tier0/utlstring.h"
#include "tier0/utlvector.h"

class IAsset;
class IAssetType;
class IBitmapAsset;
class CBufferString;
class CSimpleAssetTypeInfo;
struct AssetEngineCommand_t;
class KeyValues;
class KeyValues3;
class IAssetDir;
class ISubasset;
class ISubassetType;
class IWorkingSet;
class IAssetCacheListener;
class IAssetFileListener;
class IAssetFingerprintListener;
class IAssetTagListener;

// AMNOTE: The two places an asset's files are in. The enumerator names are the engine's; the enum's name and
// ASSET_LOCATION_INVALID are in no binary
enum AssetLocation_t
{
	ASSET_LOCATION_INVALID = -1,
	ASSET_LOCATION_GAME = 0,
	ASSET_LOCATION_CONTENT = 1,
};

// AMNOTE: The result of IAsset::CompileState. ASSET_FILE_COMPILED and ASSET_FILE_UNCOMPILED are the engine's names;
// the enum's name and the other enumerators are in no binary
enum AssetCompileState_t
{
	// Up to date, or a type whose compile state is ignored
	ASSET_FILE_COMPILED = 0,
	// No game file, a corrupt one, or an out-of-date dependency
	ASSET_FILE_UNCOMPILED = 1,
	// AMNOTE: The resource compile failed
	ASSET_FILE_UNK2 = 2,
	ASSET_FILE_UNK3 = 3,
};

//-----------------------------------------------------------------------------
// An asset of the asset system: one record per asset name, with its files in the game and content
// locations, its dependencies, compile state and tags. The asset system owns every asset.
//-----------------------------------------------------------------------------
abstract_class IAsset
{
public:
	// The asset name, a relative path with its extension
	virtual const char *GetName() = 0;

	// AMNOTE: GetName written into pBuffer
	virtual const char *unk101( CBufferString *pBuffer ) = 0;
	// AMNOTE: The name of a part of the asset's key; unk1205 and unk1206 return others
	virtual const char *unk102() = 0;

	// The path of the asset's file in the location; a game file comes back as the file system resolves it in "GAME"
	// AMNOTE: nMod is a mod index, -1 any, -2 and -3 special values
	virtual const char *GetAbsolutePath_Transient( AssetLocation_t nLocation, int nMod = -2 ) = 0;
	// Whether GetAbsolutePath_Transient has a file for the same arguments
	virtual bool HasFileInLocation( AssetLocation_t nLocation, int nMod = -2 ) = 0;

	// AMNOTE: Whether the asset has a file in either location
	virtual bool unk201() = 0;
	// AMNOTE: The name of the asset's file in the location, with its root
	virtual const char *unk202( AssetLocation_t nLocation ) = 0;

	// False (with a logged warning) when the asset has no such file or is in a read-only mod; otherwise opens
	// the file for edit in Perforce under the asset type's changelist
	virtual bool EnsureFileWritable( AssetLocation_t nLocation, int nMod ) = 0;
	virtual IAssetType *GetAssetType() = 0;
	// The name of the asset's mod
	virtual const char *GetModName() = 0;
	// 0 for an asset that is not a compiled resource
	virtual ResourceType_t GetResourceType() = 0;

	// AMNOTE: NULL for an asset that is not a compiled resource; for one, the loaded resource of unk302 when its
	// type has a type manager and unk304 is true
	virtual ResourceHandle_t unk301() = 0;
	// AMNOTE: The resource id of the asset's name, 0 for an asset that is not a compiled resource
	virtual ResourceId_t unk302() = 0;
	// AMNOTE: nUnk other than 0 adds the asset to the asset system's reload queue with the reason; then calls unk303
	// with the reason and -1 on the assets of a list of its dependency information. The asset system passes -1
	virtual void unk303( const char *pszReason, int nUnk ) = 0;
	// AMNOTE: Whether the asset is cached: held through unk501 for most, a loaded resource or bitmap for those
	virtual bool unk304() = 0;

	// False with the reason written into pReason (when not NULL) when the asset cannot be reloaded
	virtual bool CanReload( CUtlString *pReason ) = 0;

	// AMNOTE: 255, 1 or 2 from the asset's flags
	virtual int unk401() = 0;

	// False for an asset that is not a compiled resource; for one, a compile with the hints (nMode as
	// IAssetSystem::RecompileAssets passes it)
	// AMNOTE: nMode 1 is ResourceCompileMode_t::FORCE_PARENTS, the value a call without arguments passes too;
	// bUnk, pUnk and bUnk2 are passed on to the compile
	virtual bool RecompileAsset( int nMode, KeyValues *pHints, bool bUnk, void *pUnk, bool bUnk2 ) = 0;
	// False with the reason written into pReason (when not NULL) when the asset cannot be recompiled
	virtual bool CanRecompile( CUtlString *pReason ) = 0;

	// GetCompileStateReason_Transient is its text
	virtual AssetCompileState_t CompileState() = 0;

	// AMNOTE: Holds the asset (a count) and updates its cache request with bUnk; unk502 releases it
	virtual void unk501( bool bUnk ) = 0;
	virtual void unk502() = 0;
	// AMNOTE: Compiles the resource from a copy of buffer instead of its file (an in-memory replacement), with the
	// hints; false for an asset that is not a compiled resource
	virtual bool unk503( const CUtlBuffer &buffer, KeyValues *pHints ) = 0;
	// AMNOTE: The copy unk503 keeps, NULL without an in-memory replacement
	virtual CUtlBuffer *unk504() = 0;
	virtual void *unk505() = 0;
	// Discards the in-memory replacement of the asset's resource and reloads it
	virtual void DiscardInMemoryReplacement() = 0;

	// AMNOTE: unk601 to unk6010 append to pAssets (when not NULL) the assets related to this one through its
	// dependency information that are not in it yet, recursively where bRecursive is set, and return how many
	// there are
	virtual int unk601( CUtlVector< IAsset * > *pAssets, bool bRecursive, int nUnk ) = 0;
	virtual int unk602( CUtlVector< IAsset * > *pAssets, bool bRecursive, int nUnk ) = 0;
	virtual int unk603( CUtlVector< IAsset * > *pAssets, bool bRecursive ) = 0;
	virtual int unk604( CUtlVector< IAsset * > *pAssets, bool bRecursive ) = 0;
	virtual int unk605( CUtlVector< IAsset * > *pAssets, bool bRecursive ) = 0;
	virtual int unk606( CUtlVector< IAsset * > *pAssets, bool bRecursive ) = 0;
	virtual int unk607( CUtlVector< IAsset * > *pAssets, bool bRecursive ) = 0;
	virtual int unk608( CUtlVector< IAsset * > *pAssets, bool bRecursive ) = 0;
	virtual int unk609( CUtlVector< IAsset * > *pAssets, bool bRecursive ) = 0;
	virtual int unk6010( CUtlVector< IAsset * > *pAssets, bool bRecursive ) = 0;
	// AMNOTE: The number of assets this one references (unk6011) and of the assets that reference it (unk6012)
	virtual int unk6011( bool bRecursive ) = 0;
	virtual int unk6012( bool bRecursive ) = 0;
	// AMNOTE: pEntries is a CUtlVector of 32-byte entries
	virtual void unk6013( void *pEntries, bool bUnk ) = 0;
	virtual void unk6014( void *pEntries, bool bUnk ) = 0;
	// AMNOTE: Replaces pMessages with one message per dependency the file system does not have; false when there is none
	virtual bool unk6015( CUtlVector< CUtlString > *pMessages, bool bUnk ) = 0;
	// AMNOTE: The number of dependency files of the kind (0 for all), and the nIndex-th of them: its name, kind and flag
	virtual int unk6016( int nKind ) = 0;
	virtual bool unk6017( int nKind, int nIndex, CUtlString *pName, int *pKind, bool *pFlag ) = 0;
	// AMNOTE: Not unk201
	virtual bool unk6018() = 0;
	// AMNOTE: A fingerprint over the asset's own data; CalculateRecursiveFingerprint returns it for an asset without
	// dependency information, with bUnk set for nMode 2
	virtual uint32 unk6019( bool bUnk ) = 0;

	// The fingerprint over the asset's inputs
	virtual uint32 CalculateRecursiveFingerprint( int nMode ) = 0;

	// AMNOTE: The child resources: their count and the name, the location (ASSET_LOCATION_INVALID for none) and the
	// asset of the nIndex-th
	virtual int unk701() = 0;
	virtual const char *unk702( int16 nIndex ) = 0;
	virtual AssetLocation_t unk703( int16 nIndex ) = 0;
	virtual IAsset *unk704( int16 nIndex ) = 0;
	// True when a file of the asset is in a read-only mod; writes the mod's name into pModName when not NULL
	virtual bool IsInReadOnlyMod( CUtlString *pModName ) = 0;
	// AMNOTE: The per-asset info values of the key (a string, a float or an integer value); false when the asset has none
	virtual bool unk801( const char *pszKey, int *pValue ) = 0;
	virtual bool unk802( const char *pszKey, float *pValue ) = 0;
	// AMNOTE: "!name", "!type" and "!type_raw" give the name and the type's names
	virtual bool unk803( const char *pszKey, CUtlString *pValue ) = 0;
	// AMNOTE: The per-asset info keys and values by kind (string, float, integer); both lists are replaced
	virtual void unk804( CUtlVector< CUtlString > *pKeys, CUtlVector< int > *pValues ) = 0;
	virtual void unk805( CUtlVector< CUtlString > *pKeys, CUtlVector< float > *pValues ) = 0;
	virtual void unk806( CUtlVector< CUtlString > *pKeys, CUtlVector< CUtlString > *pValues ) = 0;
	// AMNOTE: NULL for an asset that is not an image
	virtual IBitmapAsset *unk807() = 0;
	// AMNOTE: A KV3 value of a per-asset side file by key: unk808 reads it into pValue, unk809 writes pValue
	// (NULL removes the key); false on a failure
	virtual bool unk808( const char *pszKey, KeyValues3 *pValue ) = 0;
	virtual bool unk809( const char *pszKey, const KeyValues3 *pValue ) = 0;

	// The text of CompileState: why the asset is not up to date ("No Game File", ...)
	virtual const char *GetCompileStateReason_Transient() = 0;

	// AMNOTE: The asset's sub-assets: their count, and the name and a flag of the nIndex-th; false for a bad index
	virtual int unk901() = 0;
	virtual bool unk902( int nIndex, CUtlString *pName, bool *pFlag ) = 0;
	// AMNOTE: A 64-bit value of the asset; unk904 is it masked
	virtual uint64 unk903() = 0;
	virtual uint64 unk904() = 0;
	// AMNOTE: Return the 4-byte value by value; -1 when there is none. unk906 is the asset's mod index
	virtual int *unk905( int *pResult ) = 0;
	virtual int *unk906( int *pResult ) = 0;
	// AMNOTE: Whether a file of the asset is in a mod with an index of at least nMod (any for -1); true without files
	virtual bool unk907( int nMod ) = 0;
	// AMNOTE: Whether a file of the asset is in one of the mods whose bit is set in pMods, a bit vector: an int bit
	// count, an int word count, then the 32-bit words (inline up to two, otherwise a pointer to them)
	virtual bool unk908( const void *pMods ) = 0;
	virtual bool unk909() = 0;
	// AMNOTE: True when the asset is a child resource whose type is not a non-trivial child type
	virtual bool unk9010() = 0;
	virtual bool unk9011() = 0;

	// The asset's tags (see IAssetSystem::GetTagName)
	virtual bool HasTag( uint16 nTag ) = 0;
	virtual void GetTags( CUtlVector< uint16 > *pTags ) = 0;

	// AMNOTE: The tag records of the asset's tags (see IAssetSystem::GetTagInfo); the list is replaced
	virtual void unk1001( CUtlVector< const void * > *pTags ) = 0;

	// False when the asset does not have the tag
	virtual bool RemoveTag( uint16 nTag ) = 0;
	virtual void AddTag( uint16 nTag ) = 0;

	virtual bool unk1101() = 0;
	// AMNOTE: The number of files of the asset in the location, and the name of the nIndex-th
	virtual int unk1102( AssetLocation_t nLocation ) = 0;
	virtual const char *unk1103( AssetLocation_t nLocation, int16 nIndex ) = 0;
	// AMNOTE: Appends the asset type's engine commands, made for this asset
	virtual void unk1104( CUtlVector< AssetEngineCommand_t > *pCommands ) = 0;

	// Counts: a change on disk does not recompile the asset while it is suppressed
	virtual void SetAutoRecompileSuppressed( bool bSuppressed ) = 0;
	virtual bool IsAutoRecompileSuppressed() = 0;

	// Logs the asset's dependencies and compile state
	virtual void CheckCompileState() = 0;

	// AMNOTE: Replaces the list's contents with the asset's sub-assets when pSubassets is not NULL
	virtual void unk1201( CUtlVector< ISubasset * > *pSubassets ) = 0;
	// AMNOTE: pEntries, when not NULL, is replaced with a CUtlVector of 16-byte entries: a sub-asset of the asset and the
	// 16-bit value unk1203 returns for it
	virtual void unk1202( void *pEntries ) = 0;
	// AMNOTE: The 16-bit value the asset keeps for the sub-asset, 0 when it keeps none
	virtual uint16 unk1203( ISubasset *pSubasset ) = 0;
	// AMNOTE: The asset to recompile for this one: found through its parents and its name, the asset itself when
	// there is none
	virtual IAsset *unk1204() = 0;
	// AMNOTE: Parts of the asset's key as strings
	virtual const char *unk1205() = 0;
	virtual const char *unk1206() = 0;
	// AMNOTE: Visits the asset's files and returns how many there are; pCallback is an object with virtuals, its second
	// and third called for each file when nFlags has 4 and 8. *pTotal, when pTotal is not NULL, gets the sum of a
	// 64-bit value the file system returns for each file
	virtual int unk1207( int nFlags, void *pCallback, uint64 *pTotal ) = 0;

	// Whether the asset has a dependency on the file with the CRC and the two flags
	virtual bool Test_DoIDependOnAssetWithCRC( const char *pszFileName, uint32 nCRC, bool bUnk, bool bUnk2 ) = 0;

	virtual uint64 unk1301() = 0;
	// AMNOTE: The directory the asset is in, and whether it is pDir (or one below it with bRecursive)
	virtual IAssetDir *unk1302() = 0;
	virtual bool unk1303( IAssetDir *pDir, bool bRecursive ) = 0;
	// AMNOTE: pEntries is replaced with a CUtlVector of the 16-byte (unk1304) or 8-byte entries of the dependency block
	virtual void unk1304( void *pEntries ) = 0;
	virtual void unk1305( void *pEntries ) = 0;
	virtual void unk1306( void *pEntries ) = 0;
	// AMNOTE: Marks the asset out of date for the reason and passes it on to the assets that depend on it; pUnk is
	// a list of the assets visited
	virtual bool unk1307( const char *pszReason, void *pUnk ) = 0;

	// AMNOTE: Declared here as the last virtual of the asset class before its own; the binary does not show
	// whether the interface declares it
	virtual ~IAsset() {}
};

//-----------------------------------------------------------------------------
// An asset type: one per entry of the asset types files, with the entry's settings (CSimpleAssetTypeInfo)
//-----------------------------------------------------------------------------
abstract_class IAssetType
{
public:
	// IAssetSystem::FindAssetTypeByName compares it
	virtual const char *GetFriendlyName() = 0;

	// AMNOTE: Appends one 272-byte entry per extension to the CUtlVector pEntries: an AssetLocation_t (content, and
	// game only for a type present in the game tree), the extension as char[260], then a pointer to the type info's
	// m_SuppressSubstrings
	virtual void unk101( void *pEntries ) = 0;

	// 0 for a type that is not a compiled resource
	virtual ResourceType_t GetResourceType() = 0;
	virtual const char *GetIconLg() = 0;
	virtual const char *GetIconSm() = 0;
	virtual bool HideTypeByDefault() = 0;
	virtual bool IgnoreCompiledState() = 0;
	virtual bool ContentFileIsText() = 0;

	// AMNOTE: Returns true; its arguments are not known
	virtual bool unk201() = 0;

	virtual bool PrefersLivePreview() = 0;

	// AMNOTE: Returns false; its arguments are not known
	virtual bool unk301() = 0;
	virtual int unk302() = 0;

	// The number of extensions GetExtensions writes into ppExtensions: m_Ext, for a resource or map type the
	// compiled ones, then the additional extensions
	virtual int GetExtensionCount() = 0;
	virtual void GetExtensions( const char **ppExtensions ) = 0;

	virtual bool IsNontrivialChildAssetType() = 0;
	virtual const char *GetExt() = 0;

	virtual bool unk401() = 0;
	// AMNOTE: A string of the type info, IAssetSystem::unk1001 compares it
	virtual const char *unk402() = 0;
	virtual bool unk403() = 0;

	virtual bool ShouldCompileErrorFallbackToDisk() = 0;
	virtual bool ErrorOnUnrecognizedOutboundRefs() = 0;
	virtual const CUtlVector< CUtlString > *GetUnrecognizedOutboundRefsErrorTypeExceptions() = 0;
	virtual const char *GetPreviewThumbnailOverlayIcon() = 0;
	virtual CSimpleAssetTypeInfo *GetAssetTypeInfo() = 0;

	virtual int unk501() = 0;
	// AMNOTE: Appends m_Ext and the additional extensions
	virtual void unk502( CUtlVector< CUtlString > *pExtensions ) = 0;

	// AMNOTE: Declared here as the last virtual of the asset type class before its own; the binary does not show
	// whether the interface declares it
	virtual ~IAssetType() {}
};

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
