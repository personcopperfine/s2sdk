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
class CToolAttrPropertyDomain;
class CToolEditContextQuery_Base;
class IPropertyAttributeEditorFactory;
class IPropertyCustomCommandFactory;
class IPropertyEditDomain;
class IPropertyEditor;
struct PropEdSpecificAttr_t;
struct ToolAttrGenericChoice_t;

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

// AMNOTE: An attribute of a target; the first member of PropEdSpecificAttr_t
struct PropEdAttrUnk_t
{
	// AMNOTE: The target
	HToolAttrTableInstance m_unk001;
	const IBaseToolAttr *m_unk002;
};

// AMNOTE: An attribute and the array indices that lead to the element below it
struct PropEdAttrPathUnk_t
{
	const PropEdAttrUnk_t *m_unk001;
	const CUtlVector< int > *m_unk002;
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
// What a property editor edits, implemented by the host tool. A target is an object with an
// attribute table; an attribute below an array is reached through the array indices in nPath.
//-----------------------------------------------------------------------------
abstract_class IPropertyEditDomain
{
public:
	virtual ~IPropertyEditDomain()
	{
		if ( g_pPropertyEditorSystem )
			g_pPropertyEditorSystem->ReleaseDomain( this );
	}

	// AMNOTE: The text of the target's row; when this returns false the editor shows unk103's instead
	virtual bool unk101( const HToolAttrTableInstance &target, CUtlString *pText ) = 0;
	// AMNOTE: True when the target is not valid
	virtual bool unk102( const HToolAttrTableInstance &target ) = 0;
	virtual CUtlString unk103( const HToolAttrTableInstance &target ) = 0;
	// AMNOTE: Replaces pAttrs' contents with the attributes of the target the editor shows rows for
	virtual void unk104( const HToolAttrTableInstance &target, CUtlVector< PropEdAttrUnk_t > *pAttrs ) = 0;
	// AMNOTE: The attribute's type, which picks its editor when nothing else does
	virtual int unk105( const PropEdAttrUnk_t &attr ) = 0;
	// AMNOTE: Fills the 184 bytes that follow the attribute in PropEdSpecificAttr_t: type, name, editor and commands
	virtual bool unk106( const PropEdAttrUnk_t &attr, const CUtlVector< int > &nPath, void *pInfo ) = 0;

	// An edit of nAttrs attributes begins; the domain makes the undo label from pszDisplayName when bUndo is set
	virtual void BeginModify( const PropEdAttrUnk_t *pAttrs, int nAttrs, const char *pszDisplayName, PropEdModifyType_t nType, bool bUndo ) = 0;
	virtual void EndModify( PropEdModifyType_t nType ) = 0;
	virtual void SetAttributeValueFromString( const PropEdAttrUnk_t &attr, const CUtlVector< int > &nPath, const CUtlString &value, PropEdModifyType_t nType ) = 0;
	virtual void GetAttributeValueString( const PropEdAttrUnk_t &attr, const CUtlVector< int > &nPath, CUtlString *pValue ) = 0;

	// AMNOTE: The value as the editor shows it: the friendly name of a choice, else the text
	virtual void unk201( const PropEdAttrUnk_t &attr, const CUtlVector< int > &nPath, CUtlString *pText ) = 0;
	// AMNOTE: The target of the attribute's element
	virtual void unk202( const PropEdAttrUnk_t &attr, const CUtlVector< int > &nPath, HToolAttrTableInstance *pTarget ) = 0;
	// AMNOTE: Replaces pChoices' contents with the choices of the attribute
	virtual void unk203( const PropEdAttrUnk_t &attr, CUtlVector< ToolAttrGenericChoice_t > *pChoices ) = 0;
	// AMNOTE: An array operation, nOperation 0 adds an item; nArg1 and nArg2 are the operation's
	virtual bool unk204( const PropEdAttrUnk_t &attr, const CUtlVector< int > &nPath, int nOperation, int nArg1, int nArg2 ) = 0;
	// AMNOTE: Element nIndex of the array the attribute is
	virtual bool unk205( const PropEdAttrUnk_t &attr, const CUtlVector< int > &nPath, int nIndex, PropEdAttrUnk_t *pElement ) { return false; }
	// AMNOTE: The element count of the array the attribute is
	virtual void unk206( const PropEdAttrUnk_t &attr, const CUtlVector< int > &nPath, int *pCount ) = 0;

	// Runs a row's command on each of the attributes
	virtual void ExecuteAttributeCommand( const char *pszCommand, const CUtlVector< PropEdAttrPathUnk_t > &attrs ) = 0;

	// Asked after each edit: true when the editor has to rebuild its rows
	virtual bool IsEditorRebuildNeeded() = 0;
	virtual void SetEditorRebuildNeeded() = 0;
	virtual void ClearEditorRebuildNeeded() = 0;

	// AMNOTE: The help text of the target
	virtual bool unk301( const HToolAttrTableInstance &target, CUtlString *pUnk, CUtlString *pUnk2 ) = 0;
	// AMNOTE: True when the attribute takes its value as KeyValues3 (SetAttributeValueFromKV3)
	virtual bool unk302( const PropEdAttrUnk_t &attr, const CUtlVector< int > &nPath ) = 0;

	virtual void SetAttributeValueFromKV3( const PropEdAttrUnk_t &attr, const CUtlVector< int > &nPath, const KeyValues3 *pValue, PropEdModifyType_t nType ) = 0;
	virtual void GetAttributeValueKV3( const PropEdAttrUnk_t &attr, const CUtlVector< int > &nPath, KeyValues3 *pValue ) = 0;

	// AMNOTE: The element of the map the attribute is under the key, made when it is missing
	virtual bool unk401( const PropEdAttrUnk_t &attr, const CUtlVector< int > &nPath, const char *pszKey, PropEdAttrUnk_t *pElement ) = 0;
	// AMNOTE: The attribute nPath leads to, and its target
	virtual IBaseToolAttr *unk402( const PropEdAttrUnk_t &attr, const CUtlVector< int > &nPath, HToolAttrTableInstance *pTarget ) = 0;
	// AMNOTE: CToolAttrPropertyDomain returns itself
	virtual CToolAttrPropertyDomain *unk403() { return NULL; }

	// The context a picker of the attribute opens with
	virtual void FillEditContextQuery( const PropEdAttrUnk_t &attr, const CUtlVector< int > &nPath, CToolEditContextQuery_Base *pQuery ) = 0;

	// AMNOTE: Answers a query no attribute answered
	virtual void unk501( CToolEditContextQuery_Base *pQuery ) = 0;

	// The rows are marked read-only and pasting is refused
	virtual bool IsReadOnly() = 0;
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
	virtual void SetTarget( const HToolAttrTableInstance &target ) = 0;
	// Rebuilds the rows
	virtual void SetTargets( const CUtlVector< HToolAttrTableInstance > &targets ) = 0;
	// Does nothing for NULL
	virtual void GetTargets( CUtlVector< HToolAttrTableInstance > *pTargets ) = 0;
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
