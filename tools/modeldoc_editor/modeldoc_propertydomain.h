//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The model editor tool (ModelDoc): the property editor domain over the document's nodes
//
//===========================================================================//

#ifndef MODELDOC_PROPERTYDOMAIN_H
#define MODELDOC_PROPERTYDOMAIN_H
#ifdef _WIN32
#pragma once
#endif

#include "tier0/platform.h"

// What a ModelDoc property domain asks the editor that shows it
abstract_class IModelDocPropertyHost
{
public:
	// AMNOTE: Asked when an attribute's value is read or set as text; the editor answers with a display setting of the
	// session
	virtual bool unk001() = 0;
	// AMNOTE: Opens an undo step with the text on the session's document
	virtual void unk002( const char *pszText ) = 0;
};

#endif // MODELDOC_PROPERTYDOMAIN_H
