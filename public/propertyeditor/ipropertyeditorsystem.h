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
#include "tier0/utlstring.h"
#include "tier0/utlvector.h"
#include "toolutils2/toolattr.h"

class QWidget;
class CBasePropItem;
class CQAttributeEditor_Base;
class CToolEditContextQuery_Base;
class IPropertyAttributeEditorFactory;
class IPropertyCustomCommandFactory;
class IPropertyEditDomain;
class IPropertyEditor;
struct PropEdSpecificAttr_t;

// How an edit reaches the domain: once, or as a drag that begins, continues and ends
// AMNOTE: The engine prints the values as "ONE_SHOT", "BEGIN_INCREMENTAL", "INCREMENTAL" and "END_INCREMENTAL"; the
// enumerators' prefix is not known
enum PropEdModifyType_t
{
	PROPEDMODIFY_ONE_SHOT = 0,
	PROPEDMODIFY_BEGIN_INCREMENTAL,
	PROPEDMODIFY_INCREMENTAL,
	PROPEDMODIFY_END_INCREMENTAL,
};

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

//-----------------------------------------------------------------------------
// Told about the edits of a property editor
//-----------------------------------------------------------------------------
abstract_class IPropertyModificationListener
{
public:
	// AMNOTE: An edit begins
	virtual void unk001( PropEdModifyType_t nType ) = 0;
	// AMNOTE: An edit ends; bRebuild is set when the editor rebuilds its rows after it
	virtual void unk002( PropEdModifyType_t nType, bool bRebuild ) = 0;
	// AMNOTE: An attribute was written during the edit
	virtual void unk003( const PropEdSpecificAttr_t &attr, PropEdModifyType_t nType ) = 0;
};

//-----------------------------------------------------------------------------
// A property editor widget, made by IPropertyEditorSystem::CreatePropertyEditor
//-----------------------------------------------------------------------------
abstract_class IPropertyEditor
{
public:
	virtual ~IPropertyEditor() {}

	// SetTargets with this target only
	virtual void SetTarget( const ToolAttrUnk_t &target ) = 0;
	// Rebuilds the rows
	virtual void SetTargets( const CUtlVector< ToolAttrUnk_t > &targets ) = 0;
	// Does nothing for NULL
	virtual void GetTargets( CUtlVector< ToolAttrUnk_t > *pTargets ) = 0;
	// Deletes a domain set with SetDomainOwned and rebuilds the rows
	virtual void SetDomain( IPropertyEditDomain *pDomain ) = 0;
	// SetDomain, and the editor deletes the domain when it replaces it
	virtual void SetDomainOwned( IPropertyEditDomain *pDomain ) = 0;
	virtual IPropertyEditDomain *GetDomain() = 0;
	virtual QWidget *GetWidget() = 0;

	// AMNOTE: Sizes the label column
	virtual void unk101( int nUnk ) = 0;

	// NULL is ignored
	virtual void AddModificationListener( IPropertyModificationListener *pListener ) = 0;
	virtual void RemoveModificationListener( IPropertyModificationListener *pListener ) = 0;
	virtual void RemoveAllModificationListeners() = 0;
	virtual void SetModificationListeners( const CUtlVector< IPropertyModificationListener * > &listeners ) = 0;

	// IPropertyEditorSystem::NotifyDomainDataChanged with the editor's domain
	virtual void NotifyDomainDataChanged() = 0;

	// AMNOTE: True from the start of an edit to its end
	virtual bool unk201() = 0;

	// The splitter state, the member "splitter_state" of pState
	virtual void RestoreState( const KeyValues3 *pState ) = 0;
	virtual void SaveState( KeyValues3 *pState ) = 0;

	// Applies an attribute list (IPropertyEditorSystem::IsAttributeListString) like a paste
	virtual void PasteAttributeListString( const char *pszText ) = 0;
	// Rebuilds the rows
	virtual void SetReadOnly( bool bReadOnly ) = 0;
	// With several targets, only the attributes every target has get a row
	virtual void SetIntersectionMode( bool bIntersection ) = 0;

	// The PropertyManipulation binding: an edit of the selected rows, flDelta from the mouse,
	// times 10 with bFast and 0.1 with bSlow
	virtual void BeginPropertyManipulation() = 0;
	virtual void UpdatePropertyManipulation( float flDelta, bool bFast, bool bSlow ) = 0;
	virtual void EndPropertyManipulation() = 0;

	// IPropertyEditorSystem::RebuildEditorsForDomain with the editor's domain
	virtual void RebuildEditorsForDomain() = 0;
};

//-----------------------------------------------------------------------------
// What the attribute editors of a property editor call
//-----------------------------------------------------------------------------
abstract_class IPropertyEditorInternal : public IPropertyEditor
{
public:
	// Writes the editor's value to the domain inside BeginModify and EndModify
	virtual void UpdateAttributesFromEditor( CQAttributeEditor_Base *pEditor, PropEdModifyType_t nType ) = 0;
	// Tells every modification listener
	virtual void NotifyAttributeModified( const PropEdSpecificAttr_t &attr, PropEdModifyType_t nType ) = 0;

	// The value of the attributes, "<Multiple Different Values>" and *pMixed set when they differ
	virtual void GetAttributeValueString( const CUtlVector< PropEdSpecificAttr_t > &attrs, const CUtlVector< int > &nPath, CUtlString *pValue, CUtlString *pText, bool *pMixed ) = 0;
	// The value of the attributes, a null KeyValues3 and *pMixed set when they differ
	virtual void GetAttributeValueKV3( const CUtlVector< PropEdSpecificAttr_t > &attrs, const CUtlVector< int > &nPath, KeyValues3 *pValue, bool *pMixed ) = 0;

	// The status line under the rows
	virtual void SetHintText( const char *pszText ) = 0;

	// AMNOTE: Answers the query from the item and its parents, else from the domain's unk501
	virtual void unk111( CBasePropItem *pItem, CToolEditContextQuery_Base *pQuery ) = 0;

	// Answers pQuery (unk111) and appends a PropEdCustomCommand_t to the item
	virtual void AddCustomCommand( CBasePropItem *pItem, const char *pszUnk, const char *pszUnk2, bool bUnk, CToolEditContextQuery_Base *pQuery ) = 0;
};

#endif // IPROPERTYEDITORSYSTEM_H
