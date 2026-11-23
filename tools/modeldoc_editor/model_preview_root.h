//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The model editor tool (ModelDoc): the preview of the compiled model and its parts
//
//===========================================================================//

#ifndef MODEL_PREVIEW_ROOT_H
#define MODEL_PREVIEW_ROOT_H
#ifdef _WIN32
#pragma once
#endif

#include "modeldoc_lib/imodelconfigpreviewhost.h"
#include "modeldoc_lib/modeldocnode.h"
#include "tier0/utlstring.h"
#include "tier0/utlvector.h"
#include "tier0/platform.h"

class CModelDocEditorSession;
class CModelPreviewRoot;

// AMNOTE: Incomplete class, only the tree members are known. A part of the preview the editor builds from the compiled
// model (bones, meshes, sequences, physics shapes, cloth nodes, ...), shown in the preview outliner
class CModelPreviewPart : public CModelDocAtom
{
public:
	// AMNOTE: The image the preview outliner shows for the part
	virtual const char *unk021() { return ""; }
	// AMNOTE: The text the preview outliner shows for the part instead of unk024's; false when it has none
	virtual bool unk022( CUtlString *pText ) { return false; }
	virtual void unk023( CUtlString *pText ) {}
	virtual const char *unk024() { return ""; }
	// AMNOTE: Its arguments are not proven: no body reads one and no call site was read
	virtual bool unk025() { return false; }
	// AMNOTE: Called with false and with true as the preview root changes its selection
	virtual void unk026( bool bUnk ) {}
	// AMNOTE: The preview root the part is in
	virtual CModelPreviewRoot *unk027() { return m_unk011->unk027(); }
	// AMNOTE: Its arguments are not proven: no body reads one and no call site was read
	virtual bool unk028() { return false; }
	virtual bool unk029() { return false; }
	virtual bool unk0210() { return false; }
	// AMNOTE: A LOD level part: its LOD is the preview root's
	virtual bool unk0211() { return false; }
	// AMNOTE: A LOD level part makes its LOD the preview root's
	virtual void unk0212() {}
	virtual void unk0213() {}
	// AMNOTE: The part's type name ("Root", "Bone", ...), which CModelDocAtom::unk1115 returns
	virtual const char *unk0214() = 0;
	virtual bool unk0215() { return false; }
	virtual bool unk0216() { return true; }
	// AMNOTE: Its arguments are not proven: no body reads one and no call site was read
	virtual void unk0217() {}
	// AMNOTE: Its arguments are not proven: no body reads one and no call site was read
	virtual bool unk0218() { return false; }
	// AMNOTE: Appends the part's context menu entries to pEntries, a CUtlVector of 32-byte entries: the command name,
	// the label, the icon and an enabled bool
	virtual void unk0219( void *pEntries ) {}
	virtual void *unk0220() { return NULL; }
	// AMNOTE: Runs the context menu command pszCommand, one of the names unk0219 added
	virtual void unk0221( const char *pszCommand ) {}
	virtual bool unk0222( void *pUnk, CUtlVector< CModelPreviewPart * > *pParts ) { return false; }
	virtual bool unk0223() { return false; }
	virtual void unk0224( void *pUnk ) {}

public:
	// AMNOTE: The parent part, NULL for the preview root. CModelDocAtom::unk114 returns it
	CModelPreviewPart *m_unk011;
	// AMNOTE: The child parts; the constructor appends the part to its parent's
	CUtlVector< CModelPreviewPart * > m_unk012;
	// AMNOTE: The part's name, CModelDocAtom::unk1114
	CUtlString m_unk013;
};

// AMNOTE: Incomplete class, only the session, the selection and the LOD are known. The preview of a session's compiled
// model, rebuilt when the compiled model changes
class CModelPreviewRoot : public CModelPreviewPart, public IModelConfigPreviewHost
{
public:
	// AMNOTE: CToolEventMapRegistrationHelper< CModelPreviewRoot >, the root's event bindings
	uint64 m_unk021[6];
	CModelDocEditorSession *m_unk022;
	uint8 m_unk023[968];
	// AMNOTE: The selected parts; each is told through CModelPreviewPart::unk026
	CUtlVector< CModelPreviewPart * > m_unk024;
	// AMNOTE: The parts CModelDocAtom::unk117 finds a part in
	CUtlVector< CModelPreviewPart * > m_unk025;
	uint8 m_unk026[60];
	// AMNOTE: The LOD the preview shows; the LOD level parts compare with it and set it
	int m_unk027;
	uint8 m_unk028[576];
};

#endif // MODEL_PREVIEW_ROOT_H
