//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose:
//
// $NoKeywords: $
//
//===========================================================================//

#ifndef ITOOLCLIENTSIMULATIONAPI_H
#define ITOOLCLIENTSIMULATIONAPI_H

#ifdef _WIN32
#pragma once
#endif

#include <functional>
#include <memory>

#include "mathlib/vector.h"
#include "tier0/keyvalues3.h"

class CEconItemPreviewDataBlock;

// AMNOTE: The client half of the tool simulation interface, mostly the item preview the tools show
abstract_class IToolClientSimulationAPI
{
public:
	// AMNOTE: The client physics tick interval, 1/64 s
	virtual float unk001() = 0;
	// AMNOTE: The number of client physics substeps per tick, 1
	virtual int unk002() = 0;
	// AMNOTE: The client physics substep interval, 1/64 s
	virtual float unk003() = 0;
	// AMNOTE: Returns sv_gravity
	virtual float unk004() = 0;
	// AMNOTE: Stores both positions and sets a flag unk006 clears
	virtual void unk005( Vector vecUnk1, Vector vecUnk2 ) = 0;
	virtual void unk006() = 0;
	// AMNOTE: Returns an empty pointer in CS2; the pointee is polymorphic, its type is not known
	virtual std::shared_ptr<void> unk007() = 0;
	// AMNOTE: Reloads the item schema, from "scripts/items/items_game_workshop.txt" when the file exists
	virtual bool unk008() = 0;
	// AMNOTE: unk009 to unk011 build the item pItem describes and keep it with a copy of pOptions (may be null)
	// for the item preview, then return true; unk010 applies "can_sticker", unk011 "can_keychain"
	virtual bool unk009( const CEconItemPreviewDataBlock *pItem, const KeyValues3 *pOptions ) = 0;
	virtual bool unk010( const CEconItemPreviewDataBlock *pItem, const KeyValues3 *pOptions ) = 0;
	virtual bool unk011( const CEconItemPreviewDataBlock *pItem, const KeyValues3 *pOptions ) = 0;
	// AMNOTE: Unregisters and frees the schema reservation listener unk016 made,
	// then reloads the item schema with unk008 when unk008 to unk011 ran since
	virtual void unk012() = 0;
	virtual void unk013() = 0;
	// AMNOTE: True when an "ItemPreviewPanel" or "CharPreviewPanel" panel exists and reports true
	virtual bool unk014() = 0;
	// AMNOTE: Requests a screenshot of the item preview panel into pszFileName, false when no panel takes the request
	virtual bool unk015( const char *pszFileName ) = 0;
	// AMNOTE: Sends a CMsgGCDev_SchemaReservationRequest with these fields to the GC and returns whether it was sent;
	// the first call registers a listener that keeps callback, later calls keep the first callback
	virtual bool unk016( const char *pszSchemaTypename, const char *pszInstanceName, uint64 nContext, const std::function<void( const char *, const char *, int64, uint32 )> &callback ) = 0;
	// AMNOTE: Sets the item preview UI's external modality, sending "RequestExternalModality: <bValue>" to it when the value changes;
	// unk018 queues nothing while it is false
	virtual void unk017( bool bValue ) = 0;
	// AMNOTE: Builds a preview item from pItem's "name", "item_id", "sticker_id", "keychain_id" and "patch_material"
	// and queues its render with a copy of pOptions (may be null), pUnk1 and pUnk2 kept with the request;
	// returns the request, null when it is not queued. Without bFullRefresh the item built for the same "name"
	// last time is reused; with it the item is rebuilt and "Full Refresh" is sent to the item preview UI
	virtual void *unk018( const KeyValues3 *pItem, const KeyValues3 *pOptions, void *pUnk1, void *pUnk2, bool bFullRefresh ) = 0;
	// AMNOTE: Queues an icon render of the item pItem describes, pUnk1 and pUnk2 kept with the request;
	// returns the request, null when the item is not known
	virtual void *unk019( const CEconItemPreviewDataBlock *pItem, void *pUnk1, void *pUnk2 ) = 0;
};

#endif // ITOOLCLIENTSIMULATIONAPI_H
