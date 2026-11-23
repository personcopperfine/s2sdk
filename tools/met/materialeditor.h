//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The material editor tool (met): the tool system and the material it edits
//
//===========================================================================//

#ifndef MATERIALEDITOR_H
#define MATERIALEDITOR_H
#ifdef _WIN32
#pragma once
#endif

#include "assetsystem/iassetsystem.h"
#include "materialsystem2/imaterialsystem2.h"
#include "tier0/fileio.h"
#include "tier0/interface.h"
#include "tier0/keyvalues3.h"
#include "tier0/utlbuffer.h"
#include "tier0/utlcommon.h"
#include "tier0/utllinkedlist.h"
#include "tier0/utlstring.h"
#include "tier0/utlvector.h"
#include "toolutils2/baseeditorapp.h"

class KeyValues;
class CQMaterialEditor;
class CQMaterialWidget;

// A variable of the material's shader, with its value in the material
struct EMaterialVariable_t
{
	// AMNOTE: The key in the .vmat
	CUtlString m_Name;
	CUtlString m_ExportName;
	CUtlString m_UiName;
	CUtlString m_UiOptions;
	// AMNOTE: The current shader uses the variable; only such variables are written
	bool m_bEnabled;
	bool m_bHidden;
	// AMNOTE: Set by the constructor
	bool m_unk001;
	// AMNOTE: The variable's UI type, an index into the editor's UI type names (0 unknown, 1 slider, 2 colour, 3 texture, ...)
	int m_unk002;
	CUtlString m_EnumLabel;
	// AMNOTE: -1 for none
	int m_nLayerId;
	bool m_bLayerAllowOverride;
	bool m_bLayerReference;
	CUtlString m_inheritedValue;
	CUtlString m_inheritedValueSource;
	CUtlString m_Group;
	CUtlString m_SubGroup;
	int m_nSortKeyGroup;
	int m_nSortKeySubGroup;
	int m_nSortKeyVariable;
	CUtlString m_error;
	CUtlString m_expression;
	CUtlString m_referencedExpressionPath;
	CUtlString m_referencedValuePath;
	int m_nElements;
	// AMNOTE: The value as it is written into the .vmat
	CUtlString m_value;
	CUtlString m_default;
	CUtlString m_min;
	CUtlString m_max;
	CUtlString m_step;
	CUtlString m_precision;
	bool m_bInitialTextureInput;
	int m_nTextureAutoFillCount;
	CUtlString m_alternateInput;
	CUtlString m_defaultColor;
	CUtlString m_defaultInput;
	CUtlString m_textureSuffix;
	CUtlString m_defaultSlider;
	float m_fDefaultSlider[2];
};

// A layer of a layered shader
struct EMaterialLayer_t
{
	CUtlVector< CUtlString > m_VariableNames;
	// AMNOTE: The engine's element type is std::pair< CUtlString, CUtlString >
	CUtlVector< CUtlKeyValuePair< CUtlString, CUtlString > > m_HiddenVariableUiNames;
	int m_ReferenceVariableIndex;
	CUtlString m_RefType;
	CUtlString m_RefFileEnding;
	bool m_bActive;
	KeyValues3 inheritedVariableValues;
	KeyValues3 inheritedVariableSources;
};

// The variables and layers of a material
struct EMaterialVariables_t
{
	bool m_bIsLayeredShader;
	CUtlVector< EMaterialVariable_t > m_Variables;
	CUtlVector< EMaterialLayer_t > m_Layers;
	// AMNOTE: Owned
	void *m_unk001;
	// AMNOTE: Owned
	KeyValues3 *m_unk002;
};

// AMNOTE: Placeholder name; an option of a feature
struct MetFeatureOptionUnk_t
{
	uint8 m_unk001;
	int m_unk002;
	// AMNOTE: The option's name, written as the comment after the feature's value
	CUtlString m_unk003;
};

// AMNOTE: Placeholder name; a feature (F_*) of the material's shader, with its value in the material
struct MetFeatureUnk_t
{
	int m_unk001;
	// AMNOTE: The key in the .vmat
	CUtlString m_unk002;
	CUtlString m_unk003;
	// AMNOTE: The group the feature is listed and written under
	CUtlString m_unk004;
	// AMNOTE: The first value; the feature is written only when its value differs from it
	int m_unk005;
	// AMNOTE: The value
	int m_unk006;
	int m_unk007;
	uint8 m_unk008;
	// AMNOTE: Turns the option comment after the value off
	bool m_unk009;
	int m_unk0010;
	// AMNOTE: One per value, indexed by the value minus the first value
	CUtlVector< MetFeatureOptionUnk_t > m_unk0011;
};

// AMNOTE: Placeholder name; the features of a material
struct MetFeatureListUnk_t
{
	CUtlString m_unk001;
	CUtlVector< MetFeatureUnk_t > m_unk002;
};

// AMNOTE: Placeholder name; a material open in the editor. The editor window keeps them in a linked list whose
// nodes put the previous and the next node after the material
struct MetMaterialUnk_t
{
	IAsset *m_unk001;
	// AMNOTE: The material's panel
	CQMaterialWidget *m_unk002;
	// AMNOTE: While it exists, the asset's automatic recompile is suppressed (IAsset::SetAutoRecompileSuppressed)
	void *m_unk003;
	uint8 m_unk004;
	// AMNOTE: The file path
	CUtlString m_unk005;
	// AMNOTE: The shader name without its .vfx extension
	CUtlString m_unk006;
	// AMNOTE: The shader's entry in the editor's shader list, -1 for none
	intp m_unk007;
	// AMNOTE: The file text as first read
	CUtlString m_unk008;
	MetFeatureListUnk_t *m_unk009;
	EMaterialVariables_t *m_unk0010;
	void *m_unk0011;
	void *m_unk0012;
	KeyValues3 *m_unk0013;
	// AMNOTE: The file's "StateHistory" block
	KeyValues3 *m_unk0014;
	// AMNOTE: The file's "VariableState" block
	KeyValues3 *m_unk0015;
	CUtlString m_unk0016;
	CUtlString m_unk0017;
	// AMNOTE: The "Attributes", "SystemAttributes", "DecalAttributes" and "ToolAttributes" blocks: name, value. The
	// engine's element type is std::pair< CUtlString, CUtlString >
	CUtlVector< CUtlKeyValuePair< CUtlString, CUtlString > > m_unk0018;
	CUtlVector< CUtlKeyValuePair< CUtlString, CUtlString > > m_unk0019;
	CUtlVector< CUtlKeyValuePair< CUtlString, CUtlString > > m_unk0020;
	CUtlVector< CUtlKeyValuePair< CUtlString, CUtlString > > m_unk0021;
	uint8 m_unk0022[24];
	// AMNOTE: The load status: 0 loaded, -2 the file could not be read
	int m_unk0023;
	// AMNOTE: The log of the last compile
	CUtlBuffer m_unk0024;
	// AMNOTE: Set when the last compile failed
	bool m_unk0025;
	int m_unk0026;
	// AMNOTE: When the next automatic History capture is due
	float m_unk0027;
	// AMNOTE: Counts the modifications; 0 after a load
	int m_unk0028;
	bool m_unk0029;
	bool m_unk0030;
	// AMNOTE: The material has unsaved changes
	bool m_unk0031;
	bool m_unk0032;
	// AMNOTE: The material has no file yet
	bool m_unk0033;
	bool m_unk0034;
	uint8 m_unk0035;
	bool m_unk0036;
	bool m_unk0037;
	bool m_unk0038;
	bool m_unk0039;
	bool m_unk0040;
	bool m_unk0041;
	bool m_unk0042;
};

// AMNOTE: Incomplete class, it adds no virtual of its own. The module's ToolSystem2 object
class CMaterialEditorTool : public CBaseToolSystem2, public IAssetFileListener, public IAssetCacheListener, public IShaderReloadListener
{
public:
	// AMNOTE: The open editor windows
	CUtlLinkedList< CQMaterialEditor *, int > m_unk001;
	uint8 m_unk002[4];
	bool m_unk003;
	// AMNOTE: Set by InitToolSystem when SHADER_SOURCE holds .vfx files; only then is the shader reload listener registered
	bool m_unk004;
	// AMNOTE: Set by the shader reload listener
	bool m_unk005;
	// AMNOTE: The "VFX_DLL_001" interface of the dynamic shader compiler, loaded with Plat_LoadInterface from
	// vfx_vulkan (vfx_dx11 for another render API), and its module
	void *m_unk006;
	HMODULE m_unk007;
	KeyValues *m_unk008;
	KeyValues3 *m_unk009;
	uint8 m_unk0010[24];
	KeyValues3 *m_unk0011;
	uint8 m_unk0012[24];
	CDirTreeWatchManager *m_unk0013;
	CDirTreeWatchManager *m_unk0014;
	// AMNOTE: The asset types of the texture extensions (psd, tga, tif, pfm, mks, png, jpg, exr, vtex)
	CUtlVector< IAssetType * > m_unk0015;
	bool m_unk0016;
	bool m_unk0017;
	CUtlVector< int > m_unk0018;
};

#endif // MATERIALEDITOR_H
