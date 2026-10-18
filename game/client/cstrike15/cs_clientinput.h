//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: Counter-Strike client input
//
//=============================================================================//

#ifndef CS_CLIENTINPUT_H
#define CS_CLIENTINPUT_H
#ifdef _WIN32
#pragma once
#endif

#include "../clientinput.h"
#include "engine2/iinputservice.h"

// AMNOTE: Incomplete class, its own members are not known
class CCSGOInput : public CClientInput, public IKeybindChangeListener, public IInputHandler
{
public:
	uint8 m_unk011[128];
};

#endif // CS_CLIENTINPUT_H
