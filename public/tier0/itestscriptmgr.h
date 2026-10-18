//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: Runs automated test scripts passed with -testscript
//
//===========================================================================//

#ifndef TIER0_ITESTSCRIPTMGR_H
#define TIER0_ITESTSCRIPTMGR_H
#ifdef _WIN32
#pragma once
#endif

#include "appframework/iappsystem.h"

// Receives the commands a test script issues
class ITestScriptCommandProcessor;

abstract_class ITestScriptMgr : public IAppSystem
{
public:
	// Loads the scripts given with -testscript and -testscript_inline
	virtual void InitFromCommandLine( ITestScriptCommandProcessor *pProcessor ) = 0;

	// Reports that the engine reached the named checkpoint
	virtual void CheckPoint( const char *pName ) = 0;

	// True once a script has commands
	virtual bool IsRunningTestScript() = 0;

	// Reports the "frame_end" checkpoint
	virtual void OnFrameEnd() = 0;

	// With bOnce, a checkpoint that was already reached is not waited for
	virtual void SetWaitCheckPoint( const char *pName, bool bOnce ) = 0;

	// Inserts the commands before the script's wait on pCheckPointName, or appends them when it is null
	// or not found; "//" comments are stripped
	virtual void InsertCommandsBeforeCheckpoint( const char *pCommands, const char *pCheckPointName ) = 0;

	virtual ~ITestScriptMgr() {}
};

#endif // TIER0_ITESTSCRIPTMGR_H
