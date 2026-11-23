//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The post-processing editor's document session: the .vpost layer stack, its undo document and the preview
//
//===========================================================================//

#ifndef POSTPROCESSEDITORSESSION_H
#define POSTPROCESSEDITORSESSION_H
#ifdef _WIN32
#pragma once
#endif

#include "tier0/utlstring.h"
#include "tier0/utlvector.h"
#include "tier0/platform.h"
#include "mathlib/vector.h"
#include "schemasystem/minschema.h"
#include "resourcesystem/resourcehandle.h"
#include "toolutils2/ibindtarget.h"
#include "toolutils2/undohistory.h"
#include "toolutils2/undoableeditorsession.h"

class CKV3TransferLoadContext;
class CKV3TransferSaveContext;
class CPostProcessEditorApp;
class CQToolSceneWidgetAutoUpdate;
struct InfoForResourceTypeCTextureBase;

// AMNOTE: Not saved: a layer's class gives its type
enum LayerType_t
{
	LAYER_TYPE_LEVELS = 0,
	LAYER_TYPE_VIBRANCE,
	LAYER_TYPE_BRIGHTNESS_CONTRAST,
	LAYER_TYPE_LUT,
	LAYER_TYPE_COLOR_BALANCE,
	LAYER_TYPE_COLOR_TINT,
	LAYER_TYPE_HUE_SATURATION,
	LAYER_TYPE_CURVES,
	LAYER_TYPE_TONEMAPPING,
	LAYER_TYPE_BLOOM,
	LAYER_TYPE_VIGNETTE,
	LAYER_TYPE_LOCAL_CONTRAST,
	LAYER_TYPE_FOG_SCATTERING,
	LAYER_TYPE_LOCAL_EXPOSURE,
	MAX_LAYER_TYPES,
};

// AMNOTE: The luminosity mask of a layer; "Add Mask" makes it with the center 128, the width 82, the shape 0
class CLayerMask
{
public:
	virtual SchemaMetaInfoHandle_t<CSchemaClassInfo> Schema_DynamicBinding() = 0;
	virtual void KV3TransferSave( CKV3TransferSaveContext *pContext ) const = 0;
	virtual void KV3TransferLoad( CKV3TransferLoadContext *pContext ) = 0;
	virtual const char *GetClassname() = 0;

public:
	int m_nLumMaskCenter;
	int m_nLumMaskWidth;
	int m_nLumMaskShape;
	bool m_bInverted;
};

// AMNOTE: The base of the layer classes of a .vpost (CToneMappingLayer, CBloomLayer, CLevelsColorCorrectionLayer, ...),
// whose own members are schema fields
class CColorCorrectionLayer
{
public:
	virtual SchemaMetaInfoHandle_t<CSchemaClassInfo> Schema_DynamicBinding() = 0;
	virtual void KV3TransferSave( CKV3TransferSaveContext *pContext ) const = 0;
	virtual void KV3TransferLoad( CKV3TransferLoadContext *pContext ) = 0;
	virtual const char *GetClassname() = 0;
	virtual ~CColorCorrectionLayer() = 0;
	// AMNOTE: Applies the layer to the nCount colours of pColors in place (a colour lookup volume). The six parameter
	// layers (tone mapping, bloom, vignette, local contrast, fog scattering, local exposure) change nothing and return false
	virtual bool unk101( Vector *pColors, int nCount ) = 0;

public:
	CUtlString m_name;
	int m_nOpacityPercent;
	bool m_bVisible;
	CLayerMask *m_pLayerMask;
	// AMNOTE: Set by the constructor of the layer's class
	LayerType_t m_unk101;
};

// AMNOTE: The root object of a .vpost
class CPostProcessData
{
public:
	virtual SchemaMetaInfoHandle_t<CSchemaClassInfo> Schema_DynamicBinding();
	virtual void KV3TransferSave( CKV3TransferSaveContext *pContext ) const;
	virtual void KV3TransferLoad( CKV3TransferLoadContext *pContext );
	virtual const char *GetClassname();

public:
	// AMNOTE: The first layer is the top row of the editor's list and is applied last
	CUtlVector< CColorCorrectionLayer * > m_layers;
};

// AMNOTE: What an undo step records of a session: unk001 copies the whole document into a new one, unk002 copies one back
class CPostProcessDoc : public CBaseUndoable
{
public:
	virtual IUndoable *unk001() override;
	virtual void unk002( IUndoable *pSource ) override;
	virtual void unk003() override;
	virtual void unk004() override;
	virtual void unk005() override;
	virtual void unk006( bool bUnk ) override;
	virtual void unk007() override;
	virtual bool unk008() override;
	virtual void *unk009() override;
	virtual void unk0010( void *pUnk ) override;
	virtual int unk0011() override;
	virtual void unk0012() override;

public:
	CPostProcessData m_unk001;
	// AMNOTE: Parallel to m_unk001.m_layers: true for a selected layer
	CUtlVectorFixedGrowable< bool, 32 > m_unk002;
	// AMNOTE: Set by an edit, cleared by a save and a load; an undo restores it and sets the session's modified flag
	// from it
	bool m_unk003;
};

// AMNOTE: Incomplete class, it adds no virtual of its own. The constructor starts the document with one tone mapping layer
class CPostProcessEditorSession : public CUndoableEditorSessionBase, public IBindTarget, public IUndoListener
{
public:
	CPostProcessEditorApp *m_unk051;
	// AMNOTE: The preview viewport, which is given the preview resource and the 32^3 texture
	CQToolSceneWidgetAutoUpdate *m_unk052;
	// AMNOTE: The 16^3 and 32^3 colour lookup volumes of the preview, made from the visible layers; m_unk055 and m_unk056
	// are their textures
	uint32 m_unk053[4096];
	uint32 m_unk054[32768];
	CStrongHandle< InfoForResourceTypeCTextureBase > m_unk055;
	CStrongHandle< InfoForResourceTypeCTextureBase > m_unk056;
	// AMNOTE: The preview's PostProcessingResource_t, filled from the visible layers
	uint8 m_unk057[344];
	CPostProcessDoc m_unk058;
};

#endif // POSTPROCESSEDITORSESSION_H
