//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
//=============================================================================//

#ifndef IRENDERSERVICE_H
#define IRENDERSERVICE_H
#ifdef _WIN32
#pragma once
#endif

#include "engine2/iengineservicemgr.h"
#include "rendersystem/rendersystemtypes.h"
#include "tier0/utlstringtoken.h"
#include "worldrenderer/world_defs.h"

class IRenderHandler;
class ISceneWorld;
struct EventClientPreOutput_t;

abstract_class IRenderService : public IEngineService
{
public:
	// AMNOTE: Handlers are kept sorted by descending nPriority
	virtual void InstallRenderHandler( const char *pszName, int nPriority, IRenderHandler *pHandler ) = 0;
	virtual void RemoveRenderHandler( IRenderHandler *pHandler ) = 0;
	virtual void ChangeVideoMode( RenderDeviceInfo_t &info ) = 0;
	virtual CUtlStringToken GetRenderingPipeline() = 0;
	virtual RenderMultisampleType_t GetMultisampleType() = 0;
	virtual void GetSplitScreenViewport( const RenderViewport_t &viewport, CSplitScreenSlot nSlot, RenderViewport_t *pOutViewport ) = 0;
	// AMNOTE: Scene world of the active rendering world session, NULL without one
	virtual ISceneWorld *GetSceneWorld() = 0;
	virtual bool IsFullyLoadedForPlayer( WorldGroupId_t hWorldGroupId, CSplitScreenSlot nSlot ) = 0;
	// Same methods as ISource2Engine
	virtual void *FindOrCreateWorldSession( const char *pszWorldName, const char *, void * ) = 0;

	virtual void LaunchAsyncBeginRenderingViewsJob( const EventClientPreOutput_t &event, bool bAddViews ) = 0;
	virtual bool FinishAsyncBeginRenderingViewsJob( bool *pbAddedViews ) = 0;
	virtual bool ShouldRenderAllWindows() = 0;
	virtual void RequestAllWindowsRenderNextFrame() = 0;
	virtual void ForceRenderForNextFrames() = 0;
	virtual bool ShouldRender() = 0;
	virtual bool unk101() = 0;
};

#endif // IRENDERSERVICE_H
