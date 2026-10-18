//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: Particle system manager interface
//
//===========================================================================//

#ifndef IPARTICLESYSTEMMGR_H
#define IPARTICLESYSTEMMGR_H
#ifdef _WIN32
#pragma once
#endif

#include "schemasystem/minschema.h"

//-----------------------------------------------------------------------------
// A particle system can only have 1 operator using a particular ID
//-----------------------------------------------------------------------------
enum ParticleOperatorId_t
{
	OPERATOR_GENERIC = -2,		// Can have as many of these as you want
	OPERATOR_SINGLETON = -1,	// Can only have 1 operator with the same name as this one
};

// AMNOTE: A registered particle function class (emitter, initializer, operator, ...); the manager keeps one static instance per class
abstract_class IParticleFunctionDefinition
{
public:
	virtual const char *GetName() const = 0;
	virtual ParticleOperatorId_t GetId() const = 0;
	virtual SchemaMetaInfoHandle_t< CSchemaClassInfo > GetSchemaBinding() const = 0;
};

#endif // IPARTICLESYSTEMMGR_H
