//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The property editor the tools embed: the editor widgets, the domain a host
//          implements for them and the system that makes them
//
//===========================================================================//

#ifndef IPROPERTYEDITORSYSTEM_H
#define IPROPERTYEDITORSYSTEM_H
#ifdef _WIN32
#pragma once
#endif

#include "appframework/iappsystem.h"

class QWidget;
class IPropertyAttributeEditorFactory;
class IPropertyCustomCommandFactory;
class IPropertyEditDomain;
class IPropertyEditor;

//-----------------------------------------------------------------------------
// The property editor system ("PropertyEditorSystem_001")
//-----------------------------------------------------------------------------
abstract_class IPropertyEditorSystem : public IAppSystem
{
public:
	// AMNOTE: nFlags is kept by the editor; the tools pass 4
	virtual IPropertyEditor *CreatePropertyEditor( QWidget *pParent, int nFlags ) = 0;
	virtual void DestroyPropertyEditor( IPropertyEditor *pEditor ) = 0;

	// Every editor showing the domain reads its values again, after the running edit when one runs
	virtual void NotifyDomainDataChanged( IPropertyEditDomain *pDomain ) = 0;
	// Every editor showing the domain rebuilds its rows
	virtual void RebuildEditorsForDomain( IPropertyEditDomain *pDomain ) = 0;

	// AMNOTE: The address of a member of the system; every attribute editor asks for it when it is made
	virtual void *unk101() = 0;

	// A factory is found by its name; registering a second factory under a name keeps the first
	virtual void RegisterAttributeEditorFactory( IPropertyAttributeEditorFactory *pFactory ) = 0;
	virtual void UnregisterAttributeEditorFactory( IPropertyAttributeEditorFactory *pFactory ) = 0;

	virtual void RegisterCustomCommandFactory( IPropertyCustomCommandFactory *pFactory ) = 0;
	// NULL when no factory has the name
	virtual IPropertyCustomCommandFactory *FindCustomCommandFactory( const char *pszName ) = 0;
	virtual void UnregisterCustomCommandFactory( IPropertyCustomCommandFactory *pFactory ) = 0;

	// True when the text is a non-empty KeyValues3 table without a header, the editors' copy format
	virtual bool IsAttributeListString( const char *pszText ) = 0;

	// Every editor showing the domain shows no domain afterwards
	virtual void ReleaseDomain( IPropertyEditDomain *pDomain ) = 0;

	// AMNOTE: The implementation's last virtual is its destructor; whether the interface or only the implementing class declares it is not known
	virtual ~IPropertyEditorSystem() {}
};

#endif // IPROPERTYEDITORSYSTEM_H
