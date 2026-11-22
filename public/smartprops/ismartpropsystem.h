//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: Creates, loads, saves and evaluates smart props (.vsmart)
//
//===========================================================================//

#ifndef ISMARTPROPSYSTEM_H
#define ISMARTPROPSYSTEM_H
#ifdef _WIN32
#pragma once
#endif

#include <functional>

#include "appframework/iappsystem.h"
#include "tier0/buffer_string.h"
#include "mathlib/transform.h"
#include "color.h"

class ISmartProp;
class ISmartPropEvaluationEnvironment;
class KeyValues3;

//-----------------------------------------------------------------------------
// The smart prop runtime ("SmartPropsSystem_001")
//-----------------------------------------------------------------------------
abstract_class ISmartPropSystem : public IAppSystem
{
public:
	// Creates an empty smart prop with the given name
	virtual ISmartProp *CreateSmartProp( const CBufferString &name ) = 0;

	// Deletes a smart prop made by this system; NULL is ignored
	virtual void DestroySmartProp( ISmartProp *pSmartProp ) = 0;

	// CreateSmartProp, then loads pData (a .vsmart document) into it when it is not NULL
	virtual ISmartProp *CreateSmartPropFromKV3( const CBufferString &name, const KeyValues3 *pData ) = 0;

	// Writes the smart prop as a .vsmart document into pOut
	virtual void SaveSmartPropToKV3( ISmartProp *pSmartProp, KeyValues3 *pOut ) = 0;

	// Writes the smart prop as a .vsmart document to the file, in the "text" encoding
	virtual void SaveSmartPropToFile( ISmartProp *pSmartProp, const char *pszFileName ) = 0;

	// Loads pData (a .vsmart document, skipped when NULL) into a temporary smart prop and calls callback with it;
	// the smart prop is destroyed when callback returns
	virtual void LoadSmartPropWithCallback( const CBufferString &name, const KeyValues3 *pData, const std::function< void( ISmartProp * ) > &callback ) = 0;

	// Evaluates the smart prop at transform (m_vPosition.w is the uniform scale), tinted with color.
	// AMNOTE: The opaque arguments are, in order: a table of variable values keyed by variable; two lists copied
	// into the evaluation when not NULL; the per-element state in; a pointer kept for the evaluation; the per-element
	// state out, written when not NULL; two output lists; and the output container of the evaluation (at most 10000
	// entries). A NULL pSmartProp evaluates nothing
	virtual void EvaluateSmartProp( ISmartPropEvaluationEnvironment *pEnvironment, ISmartProp *pSmartProp, const CTransform &transform, const Color &color,
		const void *pVariableValues, const void *pUnk1, const void *pUnk2, const void *pElementStateIn, void *pUnk3,
		void *pElementStateOut, void *pUnk4, void *pUnk5, void *pOutput ) = 0;
};

#endif // ISMARTPROPSYSTEM_H
