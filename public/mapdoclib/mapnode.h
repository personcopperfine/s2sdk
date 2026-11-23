//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: Base classes of the nodes of a Hammer map document
//
//===========================================================================//

#ifndef MAPNODE_H
#define MAPNODE_H
#ifdef _WIN32
#pragma once
#endif

#include "datamodel/dmattribute.h"
#include "datamodel/dmelement.h"
#include "mathlib/vector.h"
#include "mathlib/vector2d.h"
#include "mathlib/mathlib.h"
#include "mathlib/vmatrix.h"
#include "mathlib/vplane.h"
#include "color.h"
#include "tier0/utlstring.h"
#include "tier0/utlvector.h"
#include "tier0/platform.h"
#include "toolutils2/toolattr.h"
#include "toolutils2/undohistory.h"

class CBaseHelper;
class CMapNode;
class CToolRenderContext;
class IToolRenderableViewHost;
class ITransformationBaseline;

// AMNOTE: Name and layout not known, 8 bytes
struct MapNodeUnk8_t
{
	uint8 m_unk001[8];
};

// AMNOTE: Name and layout not known, 4 bytes
struct MapNodeUnk4_t
{
	uint8 m_unk001[4];
};

abstract_class IToolRenderCallbacks
{
public:
	// AMNOTE: Fills pLayers, a CUtlVector of 160-byte layer entries, with the layers unk003 draws one by one; the int is 1 or 2
	virtual void unk001( void *pLayers, void *, int ) = 0;
	// AMNOTE: Called before unk003
	virtual void unk002( CToolRenderContext *pContext ) = 0;
	// AMNOTE: Draws the object into pContext
	virtual void unk003( CToolRenderContext *pContext ) = 0;
	// AMNOTE: Called after unk003
	virtual void unk004( CToolRenderContext *pContext ) = 0;
	// AMNOTE: Called instead of the other callbacks when the object is not drawn
	virtual void unk005( void * ) = 0;
	virtual void unk006( float ) = 0;
};

// AMNOTE: Placeholder name; an 80-byte entry of PickContextUnk_t, built from the view and the tested position
struct ALIGN16 PickContextRayUnk_t
{
	uint8 m_unk001[80];
} ALIGN16_POST;

// AMNOTE: Placeholder name; a hit a hit test adds to PickContextUnk_t, 208 bytes
struct PickContextHitUnk_t
{
	uint64 m_unk001[26];
};

// AMNOTE: Placeholder name; what a map view's hit test hands the tools and the IHitTestable objects it asks
struct PickContextUnk_t
{
	// AMNOTE: The view that tests, a CMapView
	IToolRenderableViewHost *m_unk001;
	// AMNOTE: The tested position in the view
	Vector2D m_unk002;
	// AMNOTE: Set by the constructor
	bool m_unk003;
	// AMNOTE: The hit-test mask the view's caller passes
	int m_unk004;
	CUtlVectorFixedGrowable< PickContextRayUnk_t, 4 > m_unk005;
	// AMNOTE: The hits; the view sorts them into its caller's result
	CUtlVectorFixedGrowable< PickContextHitUnk_t, 64 > m_unk006;
};

abstract_class IHitTestable
{
public:
	// AMNOTE: Adds the object's hits to pContext
	virtual void unk001( PickContextUnk_t *pContext ) = 0;
	virtual bool unk002() = 0;
	virtual bool unk003() = 0;
	virtual bool unk004() = 0;
	virtual void *unk005() = 0;
	virtual void unk006() = 0;
	// AMNOTE: True when it wrote its value to pUnk
	virtual bool unk007( int *pUnk ) = 0;
	virtual void *unk008() = 0;
};

// A helper the editor's manipulators act on
abstract_class IManipulatorTarget
{
public:
	// AMNOTE: The bind target name of the helper's manipulator ("BoxManipulator", "sphereManipulator", "gizmo"), NULL when it has
	// none. No call site found, the arguments are not proven
	virtual const char *unk001() = 0;
};

abstract_class ITransformable
{
public:
	virtual void unk001( int, int ) = 0;
	virtual void unk002() = 0;
	// AMNOTE: Allocates a snapshot of the transform
	virtual ITransformationBaseline *unk003() = 0;
	virtual void unk004( ITransformationBaseline * ) = 0;
};

abstract_class IMapNodeToolAttrRoot : public IToolAttr_Table
{
public:
	// AMNOTE: The node this table belongs to
	virtual CMapNode *unk011() = 0;
};

abstract_class IRaytraceEnvironmentOwner
{
public:
	virtual void *unk001() = 0;
	virtual bool unk002() = 0;
	virtual void unk003( void * ) = 0;
	virtual void unk004( void * ) = 0;
	virtual void unk005( void *, void * ) = 0;
	virtual Color unk006() = 0;
	virtual int unk007() = 0;
};

class CMapAtom : public CDmElement
{
public:
	virtual void unk011() = 0;
	virtual void unk012( int ) = 0;

public:
	// AMNOTE: Taken from a global counter on construction
	int m_unk011;
	uint8 m_unk012[4];
};

class CMapPoint : public CMapAtom
{
public:
	virtual void SetOrigin( const Vector &vecOrigin ) = 0;
	// AMNOTE: Snaps components below 0.001 to 0 and keeps the yaw in [0, 360)
	virtual void SetAngles( const QAngle &angAngles ) = 0;
	virtual void SetScales( const Vector &vecScales ) = 0;
	// AMNOTE: Rotation and translation only, the scales are not applied
	virtual void GetWorldTransform( matrix3x4_t &matrix ) = 0;
	// AMNOTE: The inverse of GetWorldTransform
	virtual void unk121( matrix3x4_t & ) = 0;
	// AMNOTE: GetWorldTransform with the scales applied when unk222 is true
	virtual void unk122( matrix3x4_t & ) = 0;
	// AMNOTE: The inverse of unk122
	virtual void unk123( matrix3x4_t & ) = 0;
	virtual void unk124() = 0;
	// AMNOTE: Transforms the origin by the matrix. nFlags: 0x10 also applies the scale, 0x40 the rotation, 0x8 applies
	// them in the node's own space, 0x100 leaves the attached nodes alone; the texture lock options add 1, 2 and 4
	virtual void DoTransform( const VMatrix &matrix, int nFlags ) = 0;
	virtual void unk221( void * ) = 0;
	virtual bool unk222() = 0;

public:
	Vector m_Origin;
	QAngle m_Angles;
	Vector m_Scales;
};

// AMNOTE: Incomplete class, only the helpers, the parent and the children are known
class CMapNode : public CMapPoint, public IUndoable, public IToolRenderCallbacks, public IHitTestable, public ITransformable, public IMapNodeToolAttrRoot, public IToolAttrNotifyRoot, public IRaytraceEnvironmentOwner
{
public:
	virtual const void *unk031() = 0;
	virtual void unk032( CUtlVector< IBaseToolAttr * > * ) = 0;
	virtual int unk033() = 0;
	virtual void *unk034( const char * ) = 0;
	virtual bool unk035() = 0;
	virtual bool unk036() = 0;
	virtual bool unk037() = 0;
	virtual bool unk038() = 0;
	virtual bool unk039() = 0;
	virtual bool unk0310() = 0;
	// AMNOTE: NULL unless this is the subclass that returns itself
	virtual void *unk0311() = 0;
	// AMNOTE: NULL unless this is the subclass that returns itself
	virtual void *unk0312() = 0;
	virtual bool unk0313( CUtlString * ) = 0;
	virtual bool unk0314( CUtlString * ) = 0;
	virtual bool unk0315() = 0;
	virtual bool unk0316() = 0;
	virtual bool unk0317() = 0;
	virtual bool unk0318() = 0;
	virtual bool unk0319() = 0;
	virtual bool unk0320() = 0;
	virtual bool unk0321() = 0;
	virtual bool unk0322() = 0;
	virtual bool unk0323() = 0;
	virtual bool unk0324() = 0;
	virtual bool unk0325() = 0;
	virtual bool unk0326() = 0;
	virtual void unk0327( void * ) = 0;
	virtual bool unk0328() = 0;
	virtual bool unk0329() = 0;
	// AMNOTE: Detaches pChild from its parent first. Returns false for NULL, a cycle or the current parent
	virtual bool AddChild( CMapNode *pChild ) = 0;
	virtual void unk131( CMapNode *, bool ) = 0;
	virtual bool unk132() = 0;
	virtual bool unk133( CMapNode * ) = 0;
	virtual bool unk134( CMapNode * ) = 0;
	virtual int unk135( CMapNode * ) = 0;
	virtual void SetParent( CMapNode *pParent ) = 0;
	virtual void unk231() = 0;
	virtual void unk232( void *, void * ) = 0;
	virtual void unk233( void *, void *, void * ) = 0;
	virtual bool unk234() = 0;
	virtual void unk235( bool ) = 0;
	virtual void unk236( void * ) = 0;
	virtual void unk237( void * ) = 0;
	virtual bool unk238( void * ) = 0;
	virtual void unk239( void * ) = 0;
	virtual void unk2310( void * ) = 0;
	virtual int unk2311() = 0;
	virtual bool unk2312() = 0;
	virtual void unk2313( void *, void *, void * ) = 0;
	virtual void unk2314( void *, void *, void * ) = 0;
	virtual void unk2315( void *, void * ) = 0;
	virtual void unk2316( void *, void * ) = 0;
	virtual void unk2317( void *, int ) = 0;
	virtual void unk2318( void * ) = 0;
	virtual void unk2319() = 0;
	virtual void unk2320( void * ) = 0;
	virtual void unk2321( void * ) = 0;
	virtual void unk2322( void *, int ) = 0;
	virtual void unk2323() = 0;
	virtual void unk2324( int ) = 0;
	virtual void unk2325( void *, bool ) = 0;
	virtual void unk2326( void * ) = 0;
	virtual bool unk2327() = 0;
	virtual bool unk2328( void *, void *, void * ) = 0;
	virtual bool unk2329() = 0;
	virtual void unk2330( void *, void *, void *, void *, void * ) = 0;
	virtual void *unk2331( int ) = 0;
	virtual bool unk2332( void *, int ) = 0;
	virtual bool unk2333() = 0;
	virtual bool unk2334() = 0;
	virtual bool unk2335() = 0;
	virtual bool unk2336() = 0;
	virtual void unk2337( void *, int ) = 0;
	virtual bool unk2338() = 0;
	virtual int unk2339() = 0;
	virtual void unk2340( void * ) = 0;
	virtual void unk2341() = 0;
	virtual bool unk2342() = 0;
	virtual void unk2343( void *, void * ) = 0;
	virtual bool unk2344( int ) = 0;
	virtual bool unk2345() = 0;
	virtual bool unk2346() = 0;
	virtual bool unk2347() = 0;
	virtual bool unk2348() = 0;
	virtual bool unk2349() = 0;
	virtual bool unk2350() = 0;
	virtual bool unk2351() = 0;
	virtual bool unk2352() = 0;
	virtual bool unk2353() = 0;
	virtual bool unk2354() = 0;
	virtual bool unk2355() = 0;
	// AMNOTE: Name of the node class, "MAPCLASS_ERROR" in the base
	virtual const char *unk2356() = 0;
	// AMNOTE: Compares the argument with the node class names this class answers to
	virtual bool unk2357( const char * ) = 0;
	virtual const void *unk2358() = 0;
	virtual const void *unk2359() = 0;
	virtual void unk2360( void *, bool ) = 0;
	virtual bool unk2361() = 0;
	virtual void unk2362() = 0;
	virtual void unk2363() = 0;
	virtual bool unk2364() = 0;
	virtual bool unk2365() = 0;
	virtual bool unk2366() = 0;
	virtual bool unk2367() = 0;
	virtual bool unk2368() = 0;
	virtual bool unk2369( void *, void *, void *, void * ) = 0;
	virtual bool unk2370() = 0;
	virtual void unk2371( bool ) = 0;
	virtual bool unk2372() = 0;
	virtual bool unk2373() = 0;
	virtual bool unk2374() = 0;
	virtual bool unk2375() = 0;
	virtual bool unk2376() = 0;
	// AMNOTE: Moves the origin; a mesh keeps its vertices where they are in the world
	virtual void SetPivotPosition( const Vector &vecPivot ) = 0;
	virtual Vector unk331() = 0;
	virtual bool unk332() = 0;
	virtual void unk333( float *, float *, void * ) = 0;
	virtual bool unk334( bool ) = 0;
	virtual bool unk335() = 0;
	virtual bool unk336() = 0;
	virtual int unk337() = 0;
	virtual int unk338() = 0;
	virtual bool unk339( void *, int ) = 0;
	virtual bool unk3310() = 0;
	virtual void unk3311( void *, void * ) = 0;
	virtual MapNodeUnk8_t unk3312( void * ) = 0;
	virtual void unk3313( void *, void *, void * ) = 0;
	virtual void unk3314( bool, void * ) = 0;
	virtual void unk3315( int ) = 0;
	virtual void *unk3316( void *, void * ) = 0;
	virtual void unk3317( const char *, void * ) = 0;
	virtual void unk3318( void *, void * ) = 0;
	virtual void *unk3319( int ) = 0;
	virtual void *unk3320() = 0;
	virtual void unk3321( void *, void * ) = 0;
	virtual void unk3322( void *, int ) = 0;
	virtual void unk3323( void *, void * ) = 0;
	virtual void unk3324( void *, void * ) = 0;
	virtual void unk3325( void *, void *, bool ) = 0;
	virtual void unk3326() = 0;
	virtual void unk3327( void * ) = 0;
	virtual void unk3328( void * ) = 0;
	virtual bool unk3329( void * ) = 0;
	virtual bool unk3330( void * ) = 0;
	virtual void unk3331( void *, void *, void *, bool ) = 0;
	virtual void unk3332( void *, void *, void * ) = 0;
	virtual void *unk3333( void *, void * ) = 0;
	// AMNOTE: Reflects the node and its attached nodes across the plane: the origin and the angles, a mesh's geometry,
	// a lattice's control points
	virtual void Mirror( const VPlane &plane ) = 0;
	virtual void unk431( void * ) = 0;
	virtual bool unk432() = 0;
	virtual bool unk433( void * ) = 0;
	virtual void unk434() = 0;
	virtual int unk435() = 0;
	virtual void unk436( int ) = 0;
	virtual void unk437( int ) = 0;
	virtual void unk438() = 0;
	virtual bool unk439( void *, void * ) = 0;
	virtual bool unk4310( void *, void * ) = 0;
	virtual bool unk4311() = 0;
	virtual int unk4312() = 0;
	virtual void unk4313( void * ) = 0;
	virtual void unk4314( float *, float * ) = 0;
	virtual void unk4315( void * ) = 0;
	virtual void unk4316( void * ) = 0;
	virtual void unk4317( void *, void *, void *, void *, void *, void *, void *, void * ) = 0;
	// AMNOTE: The parent unless a subclass has its own
	virtual CMapNode *unk4318() = 0;
	virtual void unk4319( void * ) = 0;
	virtual bool unk4320() = 0;
	virtual Color unk4321() = 0;
	virtual void unk4322( int ) = 0;
	virtual Color unk4323() = 0;
	virtual void unk4324() = 0;
	virtual void unk4325( int ) = 0;
	virtual bool unk4326( int, int, void * ) = 0;
	virtual void unk4327( void *, void * ) = 0;
	virtual bool unk4328( void * ) = 0;
	virtual bool unk4329( void * ) = 0;
	virtual bool unk4330( void * ) = 0;
	virtual void unk4331( void *, void *, bool ) = 0;
	virtual Vector unk4332( int ) = 0;
	virtual const void *unk4333() = 0;
	virtual int unk4334() = 0;
	virtual const void *unk4335() = 0;
	virtual const void *unk4336() = 0;
	virtual const void *unk4337() = 0;
	virtual const void *unk4338() = 0;
	virtual const void *unk4339() = 0;
	virtual void unk4340( void *, void * ) = 0;
	virtual float unk4341() = 0;
	virtual float unk4342() = 0;
	virtual bool unk4343( void * ) = 0;
	virtual void unk4344( void * ) = 0;
	virtual bool unk4345() = 0;
	virtual void unk4346( void * ) = 0;
	virtual void unk4347( void * ) = 0;
	virtual void unk4348() = 0;
	virtual void unk4349( void *, void * ) = 0;
	virtual bool unk4350( void * ) = 0;
	virtual void unk4351( void *, void *, void * ) = 0;
	virtual float unk4352() = 0;
	virtual void unk4353( void *, int, void *, void *, void *, void *, void *, void * ) = 0;
	virtual bool unk4354() = 0;
	virtual void *unk4355() = 0;
	virtual int unk4356() = 0;
	virtual bool unk4357( void * ) = 0;
	virtual void unk4358( void * ) = 0;
	virtual void unk4359( void * ) = 0;
	virtual void unk4360() = 0;
	virtual void unk4361() = 0;
	virtual void unk4362( int ) = 0;
	virtual void unk4363( int ) = 0;
	virtual bool unk4364( const char * ) = 0;
	virtual bool unk4365( const char * ) = 0;
	virtual bool unk4366() = 0;
	virtual bool unk4367() = 0;
	virtual bool unk4368() = 0;
	virtual void unk4369() = 0;
	virtual void unk4370( const char *, void *, void * ) = 0;
	virtual void unk4371( void * ) = 0;
	virtual void *unk4372( void * ) = 0;
	virtual void unk4373( void * ) = 0;
	virtual void *unk4374( void * ) = 0;
	virtual const void *unk4375() = 0;
	virtual void unk4376( void * ) = 0;
	virtual void unk4377( void *, int, void * ) = 0;

public:
	uint8 m_unk031[128];
	// AMNOTE: The node's helpers; they are not children
	CUtlVector< CBaseHelper * > m_unk032;
	CMapNode *m_pParent;
	uint8 m_unk131[88];
	CUtlVector< DmElementHandle_t > m_Children;
	uint8 m_unk231[8];
	// AMNOTE: The datamodel attribute of m_Children
	CDmAttribute *m_unk232;
	uint8 m_unk233[632];
};

#endif // MAPNODE_H
