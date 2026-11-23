//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The Asset Browser: the tools' asset list window, the asset and sub-asset menus,
//          and the pickers and browsers the other tools embed
//
//===========================================================================//

#ifndef IASSETBROWSERSYSTEM_H
#define IASSETBROWSERSYSTEM_H
#ifdef _WIN32
#pragma once
#endif

#include "appframework/iappsystem.h"
#include "qcontrols/toolcontextmenuitem.h"
#include "tier0/utlstring.h"
#include "tier0/utlvector.h"

#include <functional>

class QMenu;
class QWidget;
class CQAssetBrowserPage;
class CQAssetComboBox;
class CQSubassetComboBox;
class IAsset;
class IAssetType;
class ISubasset;
class ISubassetType;
class IWorkingSet;

//-----------------------------------------------------------------------------
// What a tool gives the asset menu to add its own commands to it
//-----------------------------------------------------------------------------
abstract_class IAssetMenuCustomCommandContext
{
public:
	// AMNOTE: Appends the tool's own entries for the selected assets to pItems
	virtual void unk001( const CUtlVector< IAsset * > &assets, CUtlVector< ToolContextMenuItem_t > *pItems ) = 0;
	// AMNOTE: Reports where the cursor is over an asset preview: the two floats are its position as fractions of the
	// preview's width and height. The pointer is the preview's object; its type is not known
	virtual void unk002( void *pUnk, float flX, float flY ) = 0;
	// AMNOTE: Whether the menu offers "Push To Global Browser"
	virtual bool unk003() = 0;
};

// The browser's options, saved in the "asset_browser" block of the tool settings under "options.<member>"
struct AssetBrowserOptionsUnk_t
{
	bool m_bShowAllAssets = false;
	bool m_bShowRejectedAssets = true;
	// AMNOTE: When set, the preview plays a sound asset when it is shown
	bool m_unk101 = true;
	bool m_bUsePerforceIntegration = false;
	bool m_bModSpecificBrowserTabSettings = false;
	bool m_bShowSkyBox = true;
	bool m_bDrawBoneNames = true;
	bool m_bRevHelperShowUnmodified = false;
	bool m_bShowRefCountColumn = false;
};

// What a browser page shows: its working set, filters and selection
struct AssetBrowseParamsUnk_t
{
	CUtlString m_unk001;
	CUtlString m_unk002;
	// AMNOTE: The filter of the page's working set, the same text CreateAssetComboBox takes
	CUtlString m_unk003;
	// AMNOTE: Which of the page's two views it shows
	int m_unk004 = 1;
	// The page lists only assets of these types; none lists every type
	CUtlVector< IAssetType * > m_AssetTypes;
	bool m_unk101 = false;
	// AMNOTE: The asset the page selects once it is open
	IAsset *m_unk102 = nullptr;
	// The working set the page shows; NULL shows the all-assets set
	IWorkingSet *m_pWorkingSet = nullptr;
	// The text the page's search box starts with
	CUtlString m_SearchText;
	// AMNOTE: When set, the page shows only the assets of this asset's mod
	IAsset *m_unk201 = nullptr;
	bool m_unk202 = false;
	bool m_unk203 = false;
	bool m_unk204 = false;
	int m_unk205 = -1;
	// The context that adds its own commands to the page's asset menu
	IAssetMenuCustomCommandContext *m_pCustomCommandContext = nullptr;
};

// What a browser reports when the user accepts assets in it
struct AssetSelectionInfo_t
{
	CUtlVector< IAsset * > m_Assets;
	int m_unk101;
	// The text of the page's search box
	CUtlString m_SearchText;
	// AMNOTE: Which of the page's two views was shown
	int m_unk201;
};

//-----------------------------------------------------------------------------
// Gets the assets a browser or picker accepts
//-----------------------------------------------------------------------------
abstract_class IAssetSelectionListener
{
public:
	virtual void unk001( const AssetSelectionInfo_t &info ) = 0;
};

// The callback a browser calls with the assets the user accepts
class CAssetSelectionListenerHelper
{
public:
	CAssetSelectionListenerHelper() = default;
	CAssetSelectionListenerHelper( IAssetSelectionListener *pListener ) :
		m_unk001( [pListener]( const AssetSelectionInfo_t &info ) { pListener->unk001( info ); } ),
		m_unk002( true )
	{
	}

	std::function< void( const AssetSelectionInfo_t & ) > m_unk001;
	// AMNOTE: The browser calls m_unk001 only when this is set; otherwise accepting an asset opens it in its tool
	bool m_unk002 = false;
};

// AMNOTE: A page of an embedded browser, returned by value
struct AssetBrowserPageUnk_t
{
	CQAssetBrowserPage *m_unk001;
};

//-----------------------------------------------------------------------------
// An asset browser inside another tool's window
//-----------------------------------------------------------------------------
abstract_class IEmbeddedAssetBrowser
{
public:
	virtual QWidget *GetWidget() = 0;
	// The assets selected in the current page
	virtual void GetSelectedAssets( CUtlVector< IAsset * > *pAssets ) = 0;
	// Shows the browser and selects the assets, in every page when bAllPages is set, else in
	// the page of the all-assets set; bClearSearch empties the search box first
	virtual void SelectAssets( IAsset * const *ppAssets, int nCount, bool bClearSearch, bool bAllPages ) = 0;
	virtual AssetBrowserPageUnk_t OpenPage( const AssetBrowseParamsUnk_t &params ) = 0;
	virtual void SetCurrentPage( CQAssetBrowserPage *pPage ) = 0;
	virtual void ClosePage( CQAssetBrowserPage *pPage ) = 0;
	virtual void CloseAllPages() = 0;
	virtual void SelectAssetsInPage( CQAssetBrowserPage *pPage, IAsset * const *ppAssets, int nCount ) = 0;

	// AMNOTE: Hands the assets to every page's list model
	virtual void unk101( IAsset * const *ppAssets, int nCount ) = 0;

	virtual void FocusSearch() = 0;

	// AMNOTE: When set, SelectAssetsInPage empties the search box first
	virtual void unk201( bool bUnk ) = 0;
	// AMNOTE: Every page shows only the assets of pAsset's mod, every mod when NULL
	virtual void unk202( IAsset *pAsset ) = 0;
	// AMNOTE: Every page shows only the assets of the mod with this index
	virtual void unk203( int nUnk ) = 0;
	virtual void unk204( bool bUnk ) = 0;

	virtual void SetSelectionCallback( const CAssetSelectionListenerHelper &callback ) = 0;

	virtual ~IEmbeddedAssetBrowser() {}
};

//-----------------------------------------------------------------------------
// An asset field with browse, clear, pull, push and menu buttons inside another tool's window
//-----------------------------------------------------------------------------
abstract_class IEmbeddedAssetPicker
{
public:
	virtual QWidget *GetWidget() = 0;
	virtual IAsset *GetAsset() = 0;
	// Does nothing when the asset fails the picker's type filter; bNotify calls the selection
	// callback with the asset
	virtual void SetAsset( IAsset *pAsset, bool bNotify ) = 0;
	virtual void SetSelectionCallback( const CAssetSelectionListenerHelper &callback ) = 0;

	// AMNOTE: Shows or hides the asset name
	virtual void unk101( bool bUnk ) = 0;
	// AMNOTE: When cleared the name shows only the file name
	virtual void unk102( bool bUnk ) = 0;
	// AMNOTE: When cleared the name shows no extension
	virtual void unk103( bool bUnk ) = 0;
	// AMNOTE: Opens the picker window, as the Browse button does
	virtual void unk104() = 0;
	// AMNOTE: Shows the remove button
	virtual void unk105() = 0;
	// AMNOTE: Clears autoDefault on the picker's push buttons
	virtual void unk106() = 0;
	// AMNOTE: When set, the picker window starts with its search text selected
	virtual void unk107( bool bUnk ) = 0;

	virtual ~IEmbeddedAssetPicker() {}
};

//-----------------------------------------------------------------------------
// An asset browser window opened to pick assets
//-----------------------------------------------------------------------------
abstract_class ISemiModalAssetBrowser
{
public:
	virtual void SetSearchText( const char *pszText ) = 0;
	virtual void SelectSearchText() = 0;
	virtual void SelectAssets( IAsset * const *ppAssets, int nCount, bool bClearSearch, bool bAllPages ) = 0;

	// AMNOTE: Which of the current page's two views it shows
	virtual void unk101( int nUnk ) = 0;
	// AMNOTE: Brackets changes to the pages' lists; the list models update when the last bracket closes
	virtual void unk102( bool bBegin ) = 0;
};

//-----------------------------------------------------------------------------
// The asset browser system ("AssetBrowserSystem_001")
//-----------------------------------------------------------------------------
abstract_class IAssetBrowserSystem : public IAppSystem
{
public:
	// AMNOTE: The tools pass 0; nothing reads it
	virtual void StartAssetBrowserSystem( int nUnk ) = 0;

	// AMNOTE: Runs every frame: updates the windows and saves the options when they changed
	virtual void unk101() = 0;

	virtual QMenu *CreateAssetMenu( const CUtlVector< IAsset * > &assets, IAssetMenuCustomCommandContext *pContext ) = 0;
	virtual void FillAssetMenu( QMenu *pMenu, const CUtlVector< IAsset * > &assets, IAssetMenuCustomCommandContext *pContext ) = 0;
	virtual void ShowAssetMenuAtCursor( IAsset * const *ppAssets, int nCount ) = 0;

	virtual IEmbeddedAssetPicker *CreateEmbeddedAssetPicker( QWidget *pParent, const AssetBrowseParamsUnk_t &params, const char *pszName ) = 0;
	virtual void DestroyEmbeddedAssetPicker( IEmbeddedAssetPicker *pPicker ) = 0;
	virtual IEmbeddedAssetBrowser *CreateEmbeddedAssetBrowser( QWidget *pParent, bool bUnk ) = 0;
	virtual void DestroyEmbeddedAssetBrowser( IEmbeddedAssetBrowser *pBrowser ) = 0;

	// A browser window that shows params and calls callback with the assets the user accepts;
	// pszTitle also names the window's saved layout
	virtual ISemiModalAssetBrowser *OpenSemiModalAssetBrowser( const CAssetSelectionListenerHelper &callback, QWidget *pParent, const AssetBrowseParamsUnk_t &params, const char *pszTitle, bool bUnk ) = 0;

	// AMNOTE: The native window id of the main window
	virtual uintp unk201() = 0;

	virtual void ShowAssetBrowser() = 0;
	virtual AssetBrowserOptionsUnk_t *GetOptions() = 0;
	// The revision helper window for the assets
	virtual void ShowRevisionHelper( const CUtlVector< IAsset * > &assets, bool bUnk ) = 0;

	// Appends the assets that pass AssetPassesFilter
	virtual void FilterAssets( const CUtlVector< IAsset * > &assets, const AssetBrowseParamsUnk_t &params, CUtlVector< IAsset * > *pPassed ) = 0;
	virtual bool AssetPassesFilter( IAsset *pAsset, const AssetBrowseParamsUnk_t &params ) = 0;

	// Hides the window and deletes it later
	virtual void CloseSemiModalAssetBrowser( ISemiModalAssetBrowser *pBrowser ) = 0;

	// The selection of the main window, the "global" browser
	virtual void GetSelectedAssets( CUtlVector< IAsset * > *pAssets ) = 0;
	// ISemiModalAssetBrowser::SelectAssets of the main window, with bClearSearch set
	virtual void SelectAssets( IAsset * const *ppAssets, int nCount ) = 0;

	// A table of the assets; ppszNotes, NULL or one per asset, fills a fourth column
	virtual void ShowAssetList( const char *pszText, int nCount, IAsset * const *ppAssets, const char * const *ppszNotes ) = 0;

	// pszFilter filters the assets the combo box lists
	virtual CQAssetComboBox *CreateAssetComboBox( QWidget *pParent, const char *pszName, const char *pszFilter ) = 0;
	virtual CQSubassetComboBox *CreateSubassetComboBox( QWidget *pParent, ISubassetType *pType ) = 0;

	// Each page and working-set list showing the set refreshes
	virtual void OnWorkingSetChanged( IWorkingSet *pWorkingSet ) = 0;
	virtual void OnWorkingSetCreated( IWorkingSet *pWorkingSet ) = 0;
	virtual void OnWorkingSetDeleted( IWorkingSet *pWorkingSet ) = 0;

	virtual QMenu *CreateSubassetMenu( const CUtlVector< ISubasset * > &subassets ) = 0;
	virtual void FillSubassetMenu( QMenu *pMenu, const CUtlVector< ISubasset * > &subassets ) = 0;
};

#endif // IASSETBROWSERSYSTEM_H
