//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The tools' help texts: the entries behind tooltips, the help display and the help editor
//
//===========================================================================//

#ifndef IHELPSYSTEM_H
#define IHELPSYSTEM_H
#ifdef _WIN32
#pragma once
#endif

#include "tier0/platform.h"

class QWidget;

// A help context (a name such as "met") holds entries keyed by a help id. Each entry has three texts, a
// name, a short help and a full help, loaded from resource/toolhelp_<context>_<language>.txt, and the
// default texts a tool sets in code.

//-----------------------------------------------------------------------------
// Told when an entry's texts were changed in the help editor and saved
//-----------------------------------------------------------------------------
abstract_class IHelpChangeListener
{
public:
	virtual void OnHelpChanged( const char *pszContext, const char *pszHelpId ) = 0;
};

//-----------------------------------------------------------------------------
// A widget that shows one help entry, made by IHelpSystem::CreateHelpDisplayWidget
//-----------------------------------------------------------------------------
abstract_class IHelpDisplayWidget
{
public:
	// The widget to add to a layout
	virtual QWidget *GetWidget() = 0;
	// Shows the entry and tags the widget with it, as IHelpSystem::SetWidgetHelp does
	virtual void SetHelp( const char *pszContext, const char *pszHelpId ) = 0;
	// Same as SetHelp( NULL, NULL )
	virtual void ClearHelp() = 0;
	// Highlights every occurrence of the nCount strings in the shown text
	virtual void SetHighlightedText( const char **ppszText, int nCount ) = 0;
	// Shows pszText in place of the entry until it is set empty or SetHelp is called
	virtual void SetText( const char *pszText ) = 0;
};

#endif // IHELPSYSTEM_H
