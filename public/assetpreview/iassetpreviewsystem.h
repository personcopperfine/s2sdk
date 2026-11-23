//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The tools' asset previews: thumbnail widgets, live preview panes, the sound player,
//          the thumbnail cache and off-screen renders of an asset
//
//===========================================================================//

#ifndef IASSETPREVIEWSYSTEM_H
#define IASSETPREVIEWSYSTEM_H
#ifdef _WIN32
#pragma once
#endif

#include "appframework/iappsystem.h"
#include "color.h"
#include "rendersystem/rendersystemtypes.h"
#include "toolscenenodes/toolscene.h"

class QObject;
class QPixmap;
class QWidget;
class CQToolSceneWidget;
class IAsset;
class KeyValues3;

// AMNOTE: An asset and its thumbnail fingerprint
struct AssetThumbnailFingerprintUnk_t
{
	IAsset *m_unk001;
	uint32 m_unk002;
};

// AMNOTE: An array of assets passed by value: the elements and their count
struct AssetThumbnailAssetsUnk_t
{
	IAsset **m_unk001;
	int64 m_unk002;
};

// AMNOTE: An array of AssetThumbnailFingerprintUnk_t passed by value: the elements and their count
struct AssetThumbnailFingerprintsUnk_t
{
	AssetThumbnailFingerprintUnk_t *m_unk001;
	int64 m_unk002;
};

// AMNOTE: An asset whose stored thumbnail fingerprint LookupThumbnailFingerprints reads
struct AssetThumbnailLookupUnk_t
{
	// AMNOTE: The stored fingerprint, written by the lookup
	uint32 m_unk001;
	// AMNOTE: Written by the lookup: true when a thumbnail is stored for the asset
	bool m_unk002;
	IAsset *m_unk003;
};

// AMNOTE: An array of AssetThumbnailLookupUnk_t passed by value: the elements and their count
struct AssetThumbnailLookupsUnk_t
{
	AssetThumbnailLookupUnk_t *m_unk001;
	int64 m_unk002;
};

//-----------------------------------------------------------------------------
// A preview of one asset, made by IAssetPreviewSystem
//-----------------------------------------------------------------------------
abstract_class IAssetPreviewBase
{
public:
	// The widget to add to a layout; NULL for an external preview
	virtual QWidget *GetWidget() = 0;
	virtual IAsset *GetAsset() = 0;
	virtual void SetAsset( IAsset *pAsset ) = 0;

	virtual ~IAssetPreviewBase() {}
};

// A thumbnail widget: the cached thumbnail of the asset, or a live scene when live previews are enabled
abstract_class IAssetPreviewEmbedded : public IAssetPreviewBase
{
public:
	// AMNOTE: Stores bUnk in the thumbnail widget
	virtual void unk001( bool bUnk ) = 0;
};

// A preview pane: the asset's text, or its tool scene
abstract_class IAssetPreviewLive : public IAssetPreviewBase
{
public:
	virtual CQToolSceneWidget *GetSceneWidget() = 0;
};

// A preview without a widget: plays a sound asset when the asset browser's options allow it
abstract_class IAssetPreviewExternal : public IAssetPreviewBase
{
};

// Told when live previews are switched on or off
abstract_class ILiveEmbeddedPreviewStateListener
{
public:
	virtual void OnLiveEmbeddedPreviewStateChanged( bool bEnabled ) = 0;
};

// Told after a preview setting changes (camera lock, menu, animation slider, overlay icons, vertex framing)
abstract_class IAssetPreviewSettingsChangedListener
{
public:
	virtual void OnAssetPreviewSettingsChanged() = 0;
};

// Makes the controller widget that a preview pane shows for a tool scene node of one class
// (IAssetPreviewSystem::RegisterControllerFactory)
abstract_class IToolSceneNodeControllerFactory
{
public:
	// AMNOTE: The model and material controllers keep pUnk, the others do not read it
	virtual QWidget *CreateWidget( QWidget *pParent, QObject *pUnk ) = 0;
	// Points a widget made by CreateWidget at pNode
	virtual void SetNode( QWidget *pWidget, CToolSceneNode *pNode ) = 0;
};

//-----------------------------------------------------------------------------
// The asset preview system ("AssetPreviewSystem_001")
//-----------------------------------------------------------------------------
abstract_class IAssetPreviewSystem : public IAppSystem
{
public:
	// AMNOTE: The preview keeps nUnk and pUnk; with nUnk 0 an empty preview shows "(None)". pUnk is handed to the
	// asset browser with the preview's assets
	virtual IAssetPreviewEmbedded *CreateEmbeddedPreview( QWidget *pParent, int nUnk, void *pUnk ) = 0;
	virtual void DestroyEmbeddedPreview( IAssetPreviewEmbedded *pPreview ) = 0;
	virtual IAssetPreviewLive *CreateLivePreview( QWidget *pParent ) = 0;
	virtual void DestroyLivePreview( IAssetPreviewLive *pPreview ) = 0;
	virtual IAssetPreviewExternal *CreateExternalPreview() = 0;
	virtual void DestroyExternalPreview( IAssetPreviewExternal *pPreview ) = 0;

	// Creates the two light rigs thumbnails are rendered with; bOpenDatabase also opens the thumbnail database
	virtual void CreateThumbnailLightRigs( bool bOpenDatabase ) = 0;
	// Shows the non-modal "Manage Thumbnail Cache" dialog
	virtual void ShowManageThumbnailCacheDialog() = 0;

	// Renders the asset's preview scene off screen into pPixels
	// AMNOTE: nUnk is not read, the callers pass 2. pUnk is optional: its values are copied into the preview scene
	// before the render
	virtual void RenderAssetToBuffer( IAsset *pAsset, int nWidth, int nHeight, int nUnk, void *pPixels, const void *pUnk, SwapChainHandle_t hSwapChain ) = 0;
	// Renders a material (vmat) asset into pPixels, 4 bytes a pixel for nFormat 0 and 3 for nFormat 2. False for any
	// other asset or format, a NULL buffer or a size of 0 or less
	virtual bool RenderMaterialToBuffer( IAsset *pAsset, int nWidth, int nHeight, int nFormat, void *pPixels ) = 0;

	virtual void RunFrame() = 0;

	// The factory of the controller widget shown under a preview of a tool scene node of the class
	virtual void RegisterControllerFactory( IToolSceneNodeControllerFactory *pFactory, const char *pszNodeClassName ) = 0;

	// The asset's thumbnail into pPixmap; when it is not ready, the type's icon, the asset queued for rendering and
	// false. False for NULL
	virtual bool GetThumbnail( IAsset *pAsset, QPixmap *pPixmap ) = 0;
	// Fills in the stored fingerprint of each asset; false when the thumbnail database is not open
	virtual bool LookupThumbnailFingerprints( AssetThumbnailLookupsUnk_t assets ) = 0;

	virtual bool IsLivePreviewEnabled() = 0;
	// Switches every thumbnail widget between its thumbnail and a live scene and tells the
	// ILiveEmbeddedPreviewStateListeners; live previews stay off while IsLivePreviewAllowedByCommandLine is false
	virtual void SetLivePreviewEnabled( bool bEnabled ) = 0;
	virtual Color GetBackgroundColor() = 0;
	virtual void SetBackgroundColor( Color color ) = 0;

	// The preview settings ("live_preview", "background_color", "preview_camera_locked", "preview_menu_enabled",
	// "preview_anim_slider_enabled", "preview_overlay_icons_enabled", "preview_model_vertex_framing_enabled")
	virtual void SaveSettings( KeyValues3 *pSettings ) = 0;
	virtual void LoadSettings( const KeyValues3 *pSettings ) = 0;

	virtual void AddLiveEmbeddedPreviewStateListener( ILiveEmbeddedPreviewStateListener *pListener ) = 0;
	virtual void RemoveLiveEmbeddedPreviewStateListener( ILiveEmbeddedPreviewStateListener *pListener ) = 0;

	virtual void ResetBackgroundColor() = 0;

	virtual void AddSettingsChangedListener( IAssetPreviewSettingsChangedListener *pListener ) = 0;
	virtual void RemoveSettingsChangedListener( IAssetPreviewSettingsChangedListener *pListener ) = 0;

	// Forgets the assets' thumbnails and renders them again
	virtual void UpdateThumbnails( AssetThumbnailAssetsUnk_t assets ) = 0;
	// AMNOTE: The second array is handed to the thumbnail database
	virtual void MaybeUpdateThumbnail( AssetThumbnailFingerprintsUnk_t assets, AssetThumbnailFingerprintsUnk_t unk ) = 0;

	virtual bool IsPreviewCameraLocked() = 0;
	virtual void SetPreviewCameraLocked( bool bLocked ) = 0;
	virtual bool IsPreviewMenuEnabled() = 0;
	virtual void SetPreviewMenuEnabled( bool bEnabled ) = 0;
	virtual bool IsPreviewAnimSliderEnabled() = 0;
	virtual void SetPreviewAnimSliderEnabled( bool bEnabled ) = 0;
	virtual bool IsPreviewOverlayIconsEnabled() = 0;
	virtual void SetPreviewOverlayIconsEnabled( bool bEnabled ) = 0;
	virtual bool IsPreviewModelVertexFramingEnabled() = 0;
	virtual void SetPreviewModelVertexFramingEnabled( bool bEnabled ) = 0;

	// Both thumbnail light rigs read toolscenelightrigs.vdata again
	virtual void ReloadThumbnailLightRigs() = 0;
	// Empties the thumbnail database (the command assetsystem_clear_thumbnail_cache)
	virtual void ClearThumbnailCache() = 0;

	// AMNOTE: The result of a command-line parameter test, cached
	virtual bool IsLivePreviewAllowedByCommandLine() = 0;

	// Whether the preview's tool scene widget draws the sky box; false for NULL
	virtual bool GetLivePreviewDrawSkybox( IAssetPreviewLive *pPreview ) = 0;
	virtual void SetLivePreviewDrawSkybox( IAssetPreviewLive *pPreview, bool bDraw ) = 0;

	// AMNOTE: Prunes stale assets from the thumbnail database
	virtual void PruneStaleAssets() = 0;
	virtual void AddThumbnailPendingRequest( IAsset *pAsset ) = 0;

	// Renders the stale thumbnails of the assets whose name contains pszFilter, for at most nTimeLimit seconds;
	// bClearFirst runs ClearThumbnailCache first. False when the stored thumbnail fingerprints cannot be read
	virtual bool GenerateThumbnails( const char *pszFilter, int nTimeLimit, bool bClearFirst ) = 0;

	// AMNOTE: The implementation's last virtual is its destructor; whether the interface or only the implementing class declares it is not known
	virtual ~IAssetPreviewSystem() {}
};

#endif // IASSETPREVIEWSYSTEM_H
