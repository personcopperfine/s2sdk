//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The particle editor tool (pet): application and document session
//
//===========================================================================//

#ifndef PETAPP_H
#define PETAPP_H
#ifdef _WIN32
#pragma once
#endif

#include "assetsystem/iassetsystem.h"
#include "tier0/utlstring.h"
#include "toolutils2/baseeditorapp.h"
#include "toolutils2/baseeditorsession.h"
#include "toolutils2/ibindtarget.h"
#include "toolutils2/itoolsresourcelistener.h"

class CPetDoc;
class CQPetMainWnd;

// AMNOTE: Incomplete class, only the document, the selected control point and the asset are known
class CPetSession : public CSimpleSharedWindowEditorSession, public IBindTarget
{
public:
	virtual bool unk031() = 0;

public:
	// AMNOTE: The event target that receives the session's events after its own (CPetApp::m_unk031)
	void *m_unk031;
	uint8 m_unk032[128];
	CPetDoc *m_pDoc;
	uint8 m_unk131[80];
	// AMNOTE: The selected control point of the preview, -1 for none
	int m_unk132;
	uint8 m_unk133[12];
	CUtlString m_unk134;
	CUtlString m_unk135;
	CUtlString m_unk136;
	CUtlString m_unk137;
	uint8 m_unk138[24];
	CUtlVector< CUtlString > m_unk139;
	uint8 m_unk1310[112];
	// AMNOTE: The document's asset; the preview compiles the document into it as an in-memory replacement (unk503)
	IAsset *m_unk1311;
	uint8 m_unk1312[136];
};

// AMNOTE: Incomplete class, its own members are not known
class CPetApp : public CSimpleEditorSharedWindowApp< CPetSession, CQPetMainWnd >, public IToolsResourceListener
{
public:
	uint8 m_unk031[56];
};

#endif // PETAPP_H
