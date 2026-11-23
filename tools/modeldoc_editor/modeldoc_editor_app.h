//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The model editor tool (ModelDoc): application and document session
//
//===========================================================================//

#ifndef MODELDOC_EDITOR_APP_H
#define MODELDOC_EDITOR_APP_H
#ifdef _WIN32
#pragma once
#endif

#include "modeldoc_lib/modeldoc.h"
#include "resourcesystem/resourcehandle.h"
#include "toolutils2/baseeditorapp.h"
#include "toolutils2/baseeditorsession.h"
#include "toolutils2/ibindtarget.h"
#include "toolutils2/itoolsresourcelistener.h"
#include "toolutils2/toolnodetypename.h"
#include "tier0/errorlistener.h"
#include "tier0/utlstring.h"
#include "tier0/utlvector.h"

class CBaseModelDocEditorTool;
class CModelDocEditorSession;
class CModelDocEditorTool_Selection;
class CModelPreviewRoot;
class CQModelDocEditorWnd;
class IAsset;
class IToolGameSimulationAPI;
struct InfoForResourceTypeCModel;

// How the session's preview views the model
enum class ModelDocViewMode_t
{
	INVALID = 0,
	PERSPECTIVE,
	ORTHO_TOP,
	ORTHO_BOTTOM,
	ORTHO_FRONT,
	ORTHO_BACK,
	ORTHO_RIGHT,
	ORTHO_LEFT,
	ATTACHMENT,
	UV_MAP,
};

abstract_class IAssetFingerprintListener
{
public:
	// AMNOTE: Called from IAssetSystem::RunFrame with pAsset, the asset the listener was added for
	virtual void unk001( IAsset *pAsset ) = 0;
};

// AMNOTE: Incomplete class, only these members are known. A file the session's model reads; a change of its asset's
// fingerprint rebuilds the document of the session's CModelDocEditorInputSkeleton
class CModelDocEditorInputAssetFile : public IAssetFingerprintListener
{
public:
	virtual ~CModelDocEditorInputAssetFile();

public:
	// AMNOTE: The session's input object whose list owns it; that object's first member is the session
	void *m_unk011;
	uint8 m_unk012[16];
	// AMNOTE: The asset the fingerprint listener is added for, NULL when there is none
	IAsset *m_unk013;
	uint8 m_unk014[80];
};

// AMNOTE: Incomplete class, only these members are known. A document of the session's own, rebuilt from the session's
// input files when one of them changes
class CModelDocEditorInputSkeleton
{
public:
	// AMNOTE: CToolEventMapRegistrationHelper< CModelDocEditorInputSkeleton >, its event bindings
	uint64 m_unk001[6];
	CModelDocEditorSession *m_unk002;
	CModelDoc m_unk003;
	uint8 m_unk004[64];
};

// AMNOTE: Incomplete class, its own members are not known. Collects the errors of a document's nodes
class CModelDocAnalysis : public IErrorListener
{
public:
	virtual void ReportMessage( const ErrorListenerMessage_t &message ) override;
	virtual bool FormatMessageLocation( const ErrorListenerMessage_t &message, CBufferString &sOutLocation, const char *pszSuffix ) override;
	virtual const char *GetSourceName( int *pLineAndColumn ) override;
	virtual bool AppendContextPath( CBufferString &sOutContextPath ) override;
	virtual ErrorContextHandle_t PushContext( PRINTF_FORMAT_STRING const char *pszFormat, ... ) FMTFUNCTION( 2, 3 ) override;
	virtual void PopContext( int nContextLength ) override;

public:
	uint8 m_unk001[144];
};

// AMNOTE: Placeholder name, the binary has none: the game preview state of a session, made when the gameinfo turns on
// the ModelDoc feature "gamepreview"
struct ModelDocGamePreviewUnk_t
{
	CModelDocEditorSession *m_unk001;
	// AMNOTE: The game simulation interface IToolService hands out, fetched when the session is set up
	IToolGameSimulationAPI *m_unk002;
	// AMNOTE: 0 to 3, updated by the session's frame from the running game
	int m_unk003;
};

// AMNOTE: Placeholder name, the binary has none. Incomplete struct, only these members are known: the session's display
// and preview settings
struct ModelDocDisplaySettingsUnk_t
{
	CModelDocEditorSession *m_unk001;
	uint8 m_unk002[24];
	// AMNOTE: The model rotation the RotateModel command changes
	float m_unk003;
	uint8 m_unk004[8];
	// AMNOTE: The preview's view mode, PERSPECTIVE by default
	ModelDocViewMode_t m_unk005;
	uint8 m_unk006[440];
	// AMNOTE: The preview outliner's category order and its expanded categories; clearing them marks the app's settings
	// dirty
	CUtlVector< CUtlString > m_unk007;
	CUtlVector< CUtlString > m_unk008;
	int m_unk009;
};

// AMNOTE: Incomplete class, only these members are known
class CModelDocEditorSession : public CSimpleBaseEditorSession, public IBindTarget, public IAssetFingerprintListener, public IToolsResourceListener
{
public:
	// AMNOTE: CToolEventMapRegistrationHelper< CModelDocEditorSession >, the session's event bindings
	uint64 m_unk021[6];
	// AMNOTE: The event target that receives the session's events after m_unk023
	void *m_unk022;
	uint8 m_unk023[72];
	// AMNOTE: No event is posted while it is above 0
	int m_unk024;
	CQModelDocEditorWnd *m_pMainWnd;
	// AMNOTE: Replaced on every load and reload
	CModelDoc *m_pDoc;
	// AMNOTE: The Compile Debugger's step document, shown instead of m_pDoc while it is set
	CModelDoc *m_unk121;
	uint8 m_unk122[80];
	int m_unk123;
	// AMNOTE: The document the listener list in m_unk122 is registered with
	CModelDoc *m_unk124;
	// AMNOTE: The changed files the session's frame hands to its file changed dialog, emptied each frame
	CUtlVector< CUtlString > m_unk125;
	// AMNOTE: Assets of files the model references, collected by the check-out step before a save; their auto recompile
	// is suppressed until the document is replaced
	CUtlVector< IAsset * > m_unk126;
	// AMNOTE: Set by the fingerprint listener; the session's frame posts an event and clears it
	bool m_unk127;
	// AMNOTE: An object that holds the session, a CModelDoc and the session's CModelDocEditorInputAssetFile objects
	uint64 m_unk128[155];
	CModelDocEditorInputSkeleton m_unk129;
	bool m_unk1210;
	// AMNOTE: The CModelDocHelperManager
	uint64 m_unk1211[9];
	uint8 m_unk1212[4];
	int m_unk1213;
	// AMNOTE: The mode the SetManipulationMode_* commands set: 0 Selection, 1 Translate, 2 Rotate, 3 Scale; SetManipulationMode
	// also takes 4
	int m_unk1214;
	// AMNOTE: The space the SetManipulationSpace_* commands set: 0 World, 1 Local
	int m_unk1215;
	int m_unk1216;
	uint8 m_unk1217[36];
	CModelPreviewRoot *m_unk1218;
	// AMNOTE: The compiled model of the session's .vmdl; a change of its resource state rebuilds the preview
	CStrongHandle< InfoForResourceTypeCModel > m_unk1219;
	bool m_unk1220;
	// AMNOTE: The resource state of m_unk1219 the preview was last built for
	int m_unk1221;
	bool m_unk1222;
	// AMNOTE: Asset system object of the session's file, NULL when the file has none
	IAsset *m_pAsset;
	// AMNOTE: NULL unless the gameinfo turns on the ModelDoc feature "gamepreview"
	ModelDocGamePreviewUnk_t *m_unk221;
	// AMNOTE: Rebuilds the preview on the next frame
	bool m_unk222;
	uint32 m_unk223;
	// AMNOTE: The view mode the UV map view returns to
	ModelDocViewMode_t m_unk224;
	// AMNOTE: Node types; a node's type is compared with each
	CUtlVector< CToolNodeTypeName > m_unk225;
	// AMNOTE: A CModelDocNodeSet
	uint8 m_unk226[72];
	void *m_unk227;
	void *m_unk228;
	// AMNOTE: Owned, destroyed with the session
	CUtlVector< void * > m_unk229;
	void *m_unk2210;
	void *m_unk2211;
	// AMNOTE: The physics simulation mode; SetManipulationMode sets it to 0 for every mode but 4
	int m_unk2212;
	bool m_unk2213;
	int m_unk2214;
	bool m_unk2215;
	uint64 m_unk2216;
	// AMNOTE: Plat_FloatTime of the session's last frame
	double m_unk2217;
	uint64 m_unk2218;
	// AMNOTE: The active tool set, 0 or 1, and each set's index into m_unk2222
	int m_unk2219;
	int m_unk2220[2];
	uint64 m_unk2221[2];
	// AMNOTE: Owned, the viewport tools; SetActiveTool deactivates one and activates another
	CBaseModelDocEditorTool *m_unk2222[6];
	// AMNOTE: The selection tool, the first of m_unk2222
	CModelDocEditorTool_Selection *m_unk2223;
	// AMNOTE: CBindTargetProxy, made to point at the active viewport tool
	uint64 m_unk2224[3];
	CUtlString m_unk2225;
	bool m_unk2226;
	// AMNOTE: Cleared by a compile that succeeds
	bool m_unk2227;
	// AMNOTE: Passed to the compile as the compiler hint _ModelDocCompileProgressListener
	void *m_unk2228;
	ModelDocDisplaySettingsUnk_t m_unk2229;
	uint8 m_unk2230[24];
	// AMNOTE: The error listener the session's compile reports to
	CModelDocAnalysis m_Analysis;
	uint8 m_unk321[88];
};

class CModelDocEditorApp : public CBaseEditorSeparateWindowApp
{
public:
	// AMNOTE: Owned, made by the tool init (unk176) and freed by the tool shutdown (unk179); handed to each new session's
	// set-up, and the node editor's property editor registers its event handlers with the object 8 bytes into it
	void *m_unk021;
	// AMNOTE: Owned, the entity FGD the tool init (unk176) loads and hands to IHelpSystem::AddGameDataHelp
	void *m_unk022;
	// AMNOTE: The app's display settings, made with no session: the tool settings are read into and written from it, and
	// each new session copies it into its own
	ModelDocDisplaySettingsUnk_t m_unk023;
};

#endif // MODELDOC_EDITOR_APP_H
