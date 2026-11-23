//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The host a ModelDoc model config preview asks about the previewed model
//
//===========================================================================//

#ifndef IMODELCONFIGPREVIEWHOST_H
#define IMODELCONFIGPREVIEWHOST_H
#ifdef _WIN32
#pragma once
#endif

#include "tier0/platform.h"

// AMNOTE: Implemented by the ModelDoc editor's preview root
abstract_class IModelConfigPreviewHost
{
public:
	virtual ~IModelConfigPreviewHost() {}
	virtual void *unk101() = 0;
	// AMNOTE: The editor looks pszName up as an Attachment node of its document; true when found. pUnk points to 32 bytes
	// it copies, and it writes 32 bytes to pOut either way. pUnk2 is not read by the editor's body
	virtual bool unk102( const void *pUnk, void *pUnk2, const char *pszName, void *pOut ) = 0;
	virtual void *unk103() = 0;
};

#endif // IMODELCONFIGPREVIEWHOST_H
