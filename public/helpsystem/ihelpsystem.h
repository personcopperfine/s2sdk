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

#include "appframework/iappsystem.h"
#include "tier0/utlstring.h"

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

//-----------------------------------------------------------------------------
// The help system ("HelpSystem_001"). Contexts and entries are found by name, case-insensitively.
//-----------------------------------------------------------------------------
abstract_class IHelpSystem : public IAppSystem
{
public:
	// Loads the context's file unless the context is loaded already. nMode 1 searches the file in GAME,
	// any other value in MOD; with 2 the name may start with one directory ("dir/name").
	virtual void LoadHelpContext( const char *pszContext, int nMode ) = 0;
	// Loads the contexts an FGD names and sets the default texts of the entries "Element.<class>" and
	// "Attribute.<class>.<key>" from the descriptions of its classes and keys
	// AMNOTE: pGameData is the FGD a tool loaded; its class is in no binary
	virtual void AddGameDataHelp( const void *pGameData ) = 0;

	virtual IHelpDisplayWidget *CreateHelpDisplayWidget( QWidget *pParent ) = 0;
	// Deletes the widget once control returns to the event loop
	virtual void DestroyHelpDisplayWidget( IHelpDisplayWidget *pWidget ) = 0;

	// Nothing happens when the listener is added already
	virtual void AddHelpListener( IHelpChangeListener *pListener ) = 0;
	virtual void RemoveHelpListener( IHelpChangeListener *pListener ) = 0;

	// Tags the widget with an entry, in its Qt properties "HelpSystem_AssociatedContextPointer" and
	// "HelpSystem_AssociatedHelpId"
	virtual void SetWidgetHelp( QWidget *pWidget, const char *pszContext, const char *pszHelpId ) = 0;
	// False when the widget is not tagged
	virtual bool GetWidgetHelp( QWidget *pWidget, CUtlString *pContext, CUtlString *pHelpId ) = 0;
	virtual void ClearWidgetHelp( QWidget *pWidget ) = 0;

	// The entry as the HTML of a tooltip: its name, pszTag in brackets at the right when it is not empty,
	// and its help text. bShowHelpBinding adds the key bound to the full help when the entry has one.
	// False and an empty text when the context or the entry does not exist.
	virtual bool GetHelpTooltip( const char *pszContext, const char *pszHelpId, const char *pszTag, CUtlString *pText, bool bShowHelpBinding ) = 0;
	// Opens the help editor on the entry; on a customer machine only a message box that says editing is disabled
	virtual void EditHelpEntry( QWidget *pParent, const char *pszContext, const char *pszHelpId ) = 0;
	// Opens the "Help Display" window on the entry
	virtual void ShowHelpDisplay( QWidget *pParent, const char *pszContext, const char *pszHelpId ) = 0;
	// Whether any text of the entry, its own or a default one, contains pszText (case-insensitive)
	virtual bool HelpEntryContainsText( const char *pszContext, const char *pszHelpId, const char *pszText ) = 0;
	// nText: 0 the name, 1 the short help, 2 the full help. Creates the entry when the context has none.
	virtual void SetHelpText( const char *pszContext, const char *pszHelpId, int nText, const char *pszText ) = 0;
	// Writes the context back to its file
	virtual void SaveHelpContext( const char *pszContext ) = 0;
	// The entry's name or default name; the help id and false when it has neither
	virtual bool GetHelpName( const char *pszContext, const char *pszHelpId, CUtlString *pName ) = 0;
	// The entry's default texts, the ones a tool sets in code; creates the entry when the context has none
	virtual void SetDefaultHelpTexts( const char *pszContext, const char *pszHelpId, const char *pszName, const char *pszHelp, const char *pszShortHelp ) = 0;
	virtual bool HasHelpEntry( const char *pszContext, const char *pszHelpId ) = 0;

	// AMNOTE: The implementation's last virtual is its destructor; whether the interface or only the implementing class declares it is not known
	virtual ~IHelpSystem() {}
};

#endif // IHELPSYSTEM_H
