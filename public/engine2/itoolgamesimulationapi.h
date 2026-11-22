//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose:
//
// $NoKeywords: $
//
//===========================================================================//

#ifndef ITOOLGAMESIMULATIONAPI_H
#define ITOOLGAMESIMULATIONAPI_H

#ifdef _WIN32
#pragma once
#endif

#include "entityhandle.h"
#include "gametrace.h"
#include "mathlib/vector.h"
#include "mathlib/transform.h"
#include "tier0/keyvalues.h"
#include "tier0/keyvalues3.h"
#include "tier0/utlstring.h"
#include "tier0/utlvector.h"
#include "entity2/entitykeyvalues.h"

class ISceneWorld;
class CEconItemPreviewDataBlock;

// AMNOTE: The hit of a trace, copied out of the trace's CGameTrace
struct ToolGameSimulationTrace_t
{
	// AMNOTE: Invalid when the trace hit no entity
	CEntityHandle m_hEnt;
	Vector m_vEndPos;
	Vector m_vHitNormal;
	HPhysicsBody m_hBody;
};

struct ToolGameSimulationEntityInfo_t
{
	CEntityHandle m_unk001;
	// AMNOTE: The entity's hierarchy parent
	CEntityHandle m_unk002;
	// AMNOTE: The entity's owner
	CEntityHandle m_unk003;
	// AMNOTE: The entity's Hammer unique id
	CUtlString m_unk004;
	CEntityKeyValues *m_pKeyValues;
	// AMNOTE: The entity's absolute origin
	Vector m_unk101;
	// AMNOTE: The entity's absolute angles
	QAngle m_unk102;
	// AMNOTE: Bounds, both the origin when the entity has no model
	Vector m_unk103;
	Vector m_unk104;
	Vector m_unk105;
	CUtlString m_name;
	CUtlString m_designerName;
	// AMNOTE: The entity's C++ class name, "<no class info>" without class info
	CUtlString m_unk201;
	CUtlString m_unk202;
	uint64 m_unk203;
};

// AMNOTE: Incomplete, members past the ones written are not known
struct ToolGameSimulationSceneInfo_t
{
	CUtlString m_unk001;
	// AMNOTE: The scene entity's Hammer unique id
	CUtlString m_unk002;
	void *m_unk003;
	// AMNOTE: 0 when m_unk003 is null
	float m_unk004;
	bool m_unk005;
	bool m_unk006;
};

// AMNOTE: A physics grab made by IToolGameSimulationAPI::unk201
abstract_class IToolGameSimulationAPI_IPhysicsGrab
{
public:
	// AMNOTE: Moves the grab target to vecTarget
	virtual void unk001( const Vector &vecTarget ) = 0;
	// AMNOTE: Lets the body go and frees the grab
	virtual void Release() = 0;
};

// AMNOTE: The game simulation interface the tools drive the running game with,
// unk* methods that act on the player use the listen server host and do nothing on a dedicated server
abstract_class IToolGameSimulationAPI
{
public:
	// AMNOTE: Traces from vecStart to vecEnd and pushes the physics body it hits along the ray
	virtual void unk001( const Vector &vecStart, const Vector &vecEnd ) = 0;
	// AMNOTE: Fires the weapon pszWeaponName from vecOrigin along vecDirection, false when the weapon is not known;
	// the last argument is not read
	virtual bool unk002( const Vector &vecOrigin, const Vector &vecDirection, const char *pszWeaponName, int ) = 0;
	// AMNOTE: Hull trace from vecStart to vecEnd
	virtual void unk003( const Vector &vecStart, const Vector &vecEnd, const Vector &vecMins, const Vector &vecMaxs, ToolGameSimulationTrace_t *pTrace ) = 0;
	// AMNOTE: Line trace from vecStart to vecEnd
	virtual void unk004( const Vector &vecStart, const Vector &vecEnd, ToolGameSimulationTrace_t *pTrace ) = 0;
	// AMNOTE: unk005 to unk008 read and flip two flag bits (0x4000, 0x8000) of the host player
	virtual bool unk005() = 0;
	virtual void unk006( bool bValue ) = 0;
	virtual bool unk007() = 0;
	virtual void unk008( bool bValue ) = 0;
	// AMNOTE: Queues the spawn of an entity named "modeldoc_preview_ent" with these keys; the returned handle is always invalid
	virtual CEntityHandle unk009( const char *pszClassName, const char *pszModel, const Vector &vecOrigin, const QAngle &angAngles ) = 0;

	// AMNOTE: Strips a leading "maps/" and the extension, copies pOptions (may be null),
	// sets "is_tool_controlled_session" in the copy and requests the load from the host state manager
	virtual void LoadMap( const char *pszMapName, KeyValues *pOptions ) = 0;
	// AMNOTE: The same for a save game
	virtual void LoadSavegame( const char *pszSaveName, KeyValues *pOptions ) = 0;
	// AMNOTE: Runs "save <pszSaveName>"
	virtual void SaveGame( const char *pszSaveName ) = 0;

	// AMNOTE: The options the running map was loaded with, null without them
	virtual KeyValues *unk101() = 0;
	// AMNOTE: Forces rendering for the next frames and returns IRenderService::GetSceneWorld once the world is fully loaded, null before
	virtual ISceneWorld *unk102() = 0;
	// AMNOTE: The object the server's debug drawing goes to
	virtual void *unk103() = 0;
	// AMNOTE: Returns gpGlobals->curtime
	virtual float unk104() = 0;

	// AMNOTE: Runs "disconnect"
	virtual void Disconnect() = 0;

	// AMNOTE: Grabs hBody (the entity's own body when null) at vecGrabPoint, null without the entity
	virtual IToolGameSimulationAPI_IPhysicsGrab *unk201( CEntityHandle hEntity, const Vector &vecGrabPoint, bool bUnk, HPhysicsBody hBody ) = 0;
	// AMNOTE: Plays pszSoundName on the host player, at pOrigin when it is not null
	virtual void unk202( const Vector *pOrigin, const char *pszSoundName ) = 0;
	// AMNOTE: Returns false in CS2
	virtual bool unk203( KeyValues3 *pPose ) = 0;

	// AMNOTE: The entity's name, "" without the entity or a name
	virtual const char *GetEntityName( CEntityHandle hEntity ) = 0;
	// AMNOTE: The entity's designer name, "" without the entity or a name
	virtual const char *GetEntityDesignerName( CEntityHandle hEntity ) = 0;
	// AMNOTE: The entity's C++ class name, "<no class info>" without class info, "" without the entity
	virtual const char *GetEntityClassName( CEntityHandle hEntity ) = 0;

	// AMNOTE: The entity's absolute origin, vec3_origin without the entity
	virtual const Vector &unk301( CEntityHandle hEntity ) = 0;
	virtual void unk302( CEntityHandle hEntity, CUtlVector<const char *> &names ) = 0;
	// AMNOTE: Fires the input pszInput with the string pszValue on the entity, the entity being activator and caller
	virtual void unk303( CEntityHandle hEntity, const char *pszInput, const char *pszValue ) = 0;
	// AMNOTE: Appends the handles of the entities whose name matches pszName
	virtual void unk304( const char *pszName, CUtlVector<CEntityHandle> &entities ) = 0;
	// AMNOTE: The entity's m_pKeyValues, null without the entity
	virtual CEntityKeyValues *unk305( CEntityHandle hEntity ) = 0;
	// AMNOTE: The host player's eye position and eye angles, identity without the host
	virtual void unk306( CTransform &transform ) = 0;
	// AMNOTE: Fills pInfo when the entity is a scene entity
	virtual void unk307( CEntityHandle hEntity, ToolGameSimulationSceneInfo_t *pInfo ) = 0;
	// AMNOTE: Teleports the host player
	virtual void unk308( const Vector &vecPosition, const QAngle *pAngles ) = 0;
	// AMNOTE: The host player's absolute origin and angles, identity without the host
	virtual CTransform unk309() = 0;
	// AMNOTE: Resets and fills pInfo, false without the entity
	virtual bool unk310( CEntityHandle hEntity, ToolGameSimulationEntityInfo_t *pInfo ) = 0;
	// AMNOTE: Appends unk310's info of the entities whose bounds pass a test against pVolume,
	// a structure starting with a Vector origin whose other members are not known
	virtual void unk311( const void *pVolume, CUtlVector<ToolGameSimulationEntityInfo_t> &entities ) = 0;
	// AMNOTE: Appends unk310's info of every entity the interface tracks
	virtual void unk312( CUtlVector<ToolGameSimulationEntityInfo_t> &entities ) = 0;

	// AMNOTE: INetworkGameServer::GetMapName of the running server, "" without one
	virtual const char *GetMapName() = 0;

	// AMNOTE: The entity's hierarchy parent, its root when bRoot is set
	virtual CEntityHandle unk401( CEntityHandle hEntity, bool bRoot ) = 0;
	// AMNOTE: The entity's owner, the last owner of the chain when bRoot is set
	virtual CEntityHandle unk402( CEntityHandle hEntity, bool bRoot ) = 0;
	// AMNOTE: The tracked entity with this Hammer unique id
	virtual CEntityHandle unk403( const char *pszHammerID ) = 0;
	// AMNOTE: Sets effect flag 0x20 on the entity and remembers it for unk405
	virtual void unk404( CEntityHandle hEntity ) = 0;
	// AMNOTE: Clears effect flag 0x20 on every entity unk404 remembered and forgets them
	virtual void unk405() = 0;
	virtual bool unk406() = 0;
	// AMNOTE: Applies the item's attributes to the host player's weapon or wearable, false when pItem is null
	virtual bool unk407( const CEconItemPreviewDataBlock *pItem ) = 0;
	// AMNOTE: Gives the host player the item pszItemName
	virtual bool unk408( const char *pszItemName ) = 0;
};

#endif // ITOOLGAMESIMULATIONAPI_H
