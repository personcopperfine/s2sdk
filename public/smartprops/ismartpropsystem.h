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
#include "tier0/utlstring.h"
#include "tier0/utlvector.h"
#include "mathlib/mathlib.h"
#include "mathlib/transform.h"
#include "mathlib/vector.h"
#include "mathlib/vector2d.h"
#include "mathlib/vector4d.h"
#include "resourcefile/resourcetype.h"
#include "color.h"

class KeyValues3;

//-----------------------------------------------------------------------------
// A smart prop (.vsmart): a CSmartPropRoot and the state gathered from it
//-----------------------------------------------------------------------------
abstract_class ISmartProp
{
public:
	// AMNOTE: Returns whether hResource is a smart prop this one references, directly or through the smart props it references
	virtual bool unk001( ResourceHandle_t hResource ) = 0;

	// The name the smart prop was created with
	virtual const CBufferString *GetName() = 0;

	// AMNOTE: Returns the table of class versions gathered after the last load; Hammer compares it with the copy it keeps
	// to tell that the definition changed
	virtual const void *unk101() = 0;
	// AMNOTE: Clears names, then fills it with names from the root. nMode 3 takes the names of the root's variables, filtered by
	// nUnk1 (-1 any, otherwise the variable's kind; kind 4 also matches pszUnk against a string of the variable when not NULL)
	// and nUnk2 (0 any); modes 1 and 2 collect names through the root's modifiers and one more list of the root
	virtual void unk102( int nMode, int nUnk1, int nUnk2, const char *pszUnk, CUtlVector< CUtlString > &names ) = 0;
	// AMNOTE: Fills a CUtlVector of 16-byte records ({ CUtlString; int }), sorted and without duplicate names, from the root
	virtual void unk103( void *pOut ) = 0;
	// AMNOTE: Fills a CUtlVector of 168-byte records from the root
	virtual void unk104( void *pOut ) = 0;
	// AMNOTE: Looks up the root's variable named pszVariableName (case-insensitive) and returns whether it exists. Each pointer
	// is written when not NULL: two ints and a string from the variable, its default value, and its m_bExposeAsParameter
	virtual bool unk105( const char *pszVariableName, int *pUnk1, CUtlString *pUnk2, int *pUnk3, KeyValues3 *pDefaultValue, bool *pExposeAsParameter ) = 0;
	// AMNOTE: Compiles pszExpression against the smart prop's variables; false on failure, with the message in pError
	virtual bool unk106( const char *pszExpression, CBufferString *pError ) = 0;
	// AMNOTE: Fills a CUtlVector of 224-byte records from the root
	virtual void unk107( void *pOut ) = 0;
	// AMNOTE: Set once the state after a load has been gathered
	virtual bool unk108() = 0;

	// The resources the smart prop references, gathered after the last load
	virtual void GetResourceReferences( CUtlVector< ResourceHandle_t > &references ) = 0;

	// AMNOTE: Adds a CSmartPropElement_Model child of the model pszModelName at transform, scaled by vScale, to the root
	virtual bool unk201( const char *pszModelName, const CTransform &transform, const Vector &vScale ) = 0;
	// AMNOTE: Adds a CSmartPropElement_SmartProp child of the smart prop pszSmartPropName at transform to the root
	virtual bool unk202( const char *pszSmartPropName, const CTransform &transform ) = 0;
	// AMNOTE: Gathers the state a load gathers again (references, class versions), after the root was edited
	virtual void unk203() = 0;

	virtual ~ISmartProp() {}
};

//-----------------------------------------------------------------------------
// A shape an evaluation places on (CSmartPropElement_PlaceOnPath, CSmartPropElement_PlaceOnMesh),
// implemented by the host
//-----------------------------------------------------------------------------
abstract_class ISmartPropShape
{
public:
	virtual ~ISmartPropShape() {}

	// AMNOTE: 0 for an ISmartPropShapePath, 1 for an ISmartPropShapeMesh
	virtual int GetShapeType() = 0;
};

abstract_class ISmartPropShapePath : public ISmartPropShape
{
public:
	// AMNOTE: The path the placement follows; its type is not declared
	virtual const void *GetPath() = 0;
};

// AMNOTE: A mesh shape (Hammer's mesh objects); faces and edges are passed as indices
abstract_class ISmartPropShapeMesh : public ISmartPropShape
{
public:
	// AMNOTE: Fills faces with every face of the mesh; false when the list could not be grown
	virtual bool unk001( CUtlVector< int > &faces ) = 0;
	// AMNOTE: Whether the shape has a mesh
	virtual bool unk002() = 0;
	// AMNOTE: The number of vertices of the face nFace
	virtual int unk003( int nFace ) = 0;
	// AMNOTE: Counts the edges of the face nFace that are open (closed when bClosedEdges); with bSharedVert only those
	// next to another such edge of the face, without it only those that are not
	virtual int unk004( int nFace, bool bClosedEdges, bool bSharedVert ) = 0;
	// AMNOTE: Appends to faces the faces whose material is pszMaterial, or the others when bInvert; false when the list
	// could not be grown
	virtual bool unk005( const char *pszMaterial, bool bInvert, CUtlVector< int > &faces ) = 0;
	// AMNOTE: Writes a frame of the face nFace oriented by a texture coordinate channel (nUnk 5 the first channel,
	// 6 the second) and the face's extent along the frame's two axes to the floats; returns true
	virtual bool unk006( int nFace, int nUnk, matrix3x4_t *pFrame, float *pflUnk1, float *pflUnk2 ) = 0;
	// AMNOTE: Writes a frame of the face nFace oriented by its first open edge (its first closed edge when bOpenEdge
	// is false) and the face's extent along the frame's two axes to the floats
	virtual bool unk007( int nFace, bool bOpenEdge, matrix3x4_t *pFrame, float *pflUnk1, float *pflUnk2 ) = 0;
	// AMNOTE: Appends to edges the closed edges whose angle between their two faces is within flMinAngle and flMaxAngle
	// (degrees), or outside them when bInvert
	virtual void unk008( float flMinAngle, float flMaxAngle, bool bInvert, CUtlVector< int > &edges ) = 0;
	// AMNOTE: Writes a frame on the edge nEdge, and the edge's length to both floats
	virtual bool unk009( int nEdge, matrix3x4_t *pFrame, float *pflUnk1, float *pflUnk2 ) = 0;
	// AMNOTE: Fills vertices with the positions of the face nFace's vertices in the space of frame
	virtual void unk0010( int nFace, const matrix3x4_t &frame, CUtlVector< Vector > &vertices ) = 0;
};

//-----------------------------------------------------------------------------
// What an evaluation asks of the host (Hammer's map document, the asset preview's scene)
//-----------------------------------------------------------------------------
abstract_class ISmartPropEvaluationEnvironment
{
public:
	// AMNOTE: Traces a ray and returns whether it hit. pRay is { Vector start; Vector direction; float length; uint32 flags },
	// the flags 1 ignore tool materials, 2 sky, 4 nodraw, 8 translucent, 0x10 models, 0x20 entities, 0x40 cables.
	// pResult is { Vector position; Vector normal; void *pHit }, written on a hit; the pointer is kept as the
	// surface of the last trace
	virtual bool unk001( const void *pRay, void *pResult ) = 0;
	// AMNOTE: Whether elements and modifiers whose class is marked experimental (MVDataExperimentalNodeSet) are evaluated
	virtual bool unk002() = 0;
};

//-----------------------------------------------------------------------------
// The values an attribute reads while it is evaluated: the variables by name, and expressions over them
//-----------------------------------------------------------------------------
abstract_class IAttributeEvaluationContext
{
public:
	// The value of the variable pszName, converted to each type; an unknown variable reads as an empty value
	virtual const char *GetVariableString( const char *pszName ) = 0;
	virtual bool GetVariableBool( const char *pszName ) = 0;
	virtual int GetVariableInt( const char *pszName ) = 0;
	virtual float GetVariableFloat( const char *pszName ) = 0;
	virtual Vector2D GetVariableVector2D( const char *pszName ) = 0;
	virtual Vector GetVariableVector( const char *pszName ) = 0;
	virtual Vector4D GetVariableVector4D( const char *pszName ) = 0;
	virtual Color GetVariableColor( const char *pszName ) = 0;
	virtual QAngle GetVariableQAngle( const char *pszName ) = 0;

	// Evaluates pszExpression; 0 when it does not compile
	virtual float EvaluateFloatExpression( const char *pszExpression ) = 0;
	// EvaluateFloatExpression, true when the absolute value is above 0.0001
	virtual bool EvaluateBoolExpression( const char *pszExpression ) = 0;
};

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
	// AMNOTE: The opaque arguments are, in order: a table of variable values keyed by variable; a list copied into the
	// evaluation when not NULL; the shapes, a list of 64-byte records that path and mesh placements look up by name
	// (case-insensitive), each with a transform at +16 and an ISmartPropShape * at +48; the per-element state in; a
	// pointer kept for the evaluation; the per-element state out, written when not NULL; two output lists; and the
	// output container of the evaluation (at most 10000 entries). A NULL pSmartProp evaluates nothing
	virtual void EvaluateSmartProp( ISmartPropEvaluationEnvironment *pEnvironment, ISmartProp *pSmartProp, const CTransform &transform, const Color &color,
		const void *pVariableValues, const void *pUnk1, const void *pShapes, const void *pElementStateIn, void *pUnk2,
		void *pElementStateOut, void *pUnk3, void *pUnk4, void *pOutput ) = 0;
};

#endif // ISMARTPROPSYSTEM_H
