//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: Name of a tool document's node type
//
//===========================================================================//

#ifndef TOOLNODETYPENAME_H
#define TOOLNODETYPENAME_H
#ifdef _WIN32
#pragma once
#endif

#include "tier0/utlstringtoken.h"

class CToolNodeTypeName
{
public:
	// AMNOTE: Token of the lowercased name
	CUtlStringToken m_Token;
	const char *m_pszName;
};

#endif // TOOLNODETYPENAME_H
