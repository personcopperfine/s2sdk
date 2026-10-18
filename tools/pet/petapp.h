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

#include "toolutils2/baseeditorapp.h"
#include "toolutils2/baseeditorsession.h"
#include "toolutils2/ibindtarget.h"
#include "toolutils2/itoolsresourcelistener.h"

class CPetDoc;
class CQPetMainWnd;

// AMNOTE: Incomplete class, only the document is known
class CPetSession : public CSimpleSharedWindowEditorSession, public IBindTarget
{
public:
	virtual bool unk031() = 0;

public:
	uint8 m_unk031[136];
	CPetDoc *m_pDoc;
	uint8 m_unk131[432];
};

// AMNOTE: Incomplete class, its own members are not known
class CPetApp : public CSimpleEditorSharedWindowApp< CPetSession, CQPetMainWnd >, public IToolsResourceListener
{
public:
	uint8 m_unk031[56];
};

#endif // PETAPP_H
