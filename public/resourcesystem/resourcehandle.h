#ifndef RESOURCEHANDLE_H
#define RESOURCEHANDLE_H

#ifdef COMPILER_MSVC
#pragma once
#endif

#include "interfaces/interfaces.h"
#include "resourcefile/resourcetype.h"
#include "resourcesystem/resourcesystemtypes.h"

struct ResourceSerialHandle_t
{
	ResourceSerialHandle_t() : m_Value( 0 ) {}
	ResourceSerialHandle_t( uint64 nValue ) : m_Value( nValue ) {}

	uint64 m_Value;
};

abstract_class IResourceHandleUtils
{
public:
	virtual ResourceHandle_t FindOrRegisterResourceByName( const CResourceName &name ) = 0;
	virtual ResourceHandle_t FindResourceById( ResourceId_t id, ResourceType_t nType ) = 0;
	virtual void DeleteResource( ResourceHandle_t hResource ) = 0;
	virtual void ResourceReferenceLeakTracking_AddRef( ResourceHandle_t hResource, ResourceLeakTrackingGroup_t eGroup, uintp nContext ) = 0;
	virtual void ResourceReferenceLeakTracking_Release( ResourceHandle_t hResource, ResourceLeakTrackingGroup_t eGroup, uintp nContext ) = 0;
	virtual void ResourceReferenceLeakTracking_ReportReferences( ResourceHandle_t hResource ) = 0;
	virtual ResourceStatus_t GetResourceStatus( ResourceHandle_t hResource ) = 0;
	virtual ResourceType_t GetResourceHandleType( ResourceHandle_t hResource ) = 0;
	// AMNOTE: Runs the handle allocator self-test
	virtual void unk101() = 0;
	// AMNOTE: Returns hResource as a serial handle
	virtual ResourceSerialHandle_t unk102( ResourceHandle_t hResource ) = 0;
	virtual ResourceHandle_t HandleUtils_Deref( ResourceSerialHandle_t hSerial ) = 0;
};

// AMNOTE: Holds one reference on the binding; releasing the last one passes it to IResourceHandleUtils::DeleteResource
template < typename T >
class CStrongHandle
{
public:
	CStrongHandle() : m_pBinding( nullptr ) {}
	CStrongHandle( const CStrongHandle &other ) : m_pBinding( other.m_pBinding ) { AddRef(); }
	~CStrongHandle() { Release(); }

	CStrongHandle &operator=( const CStrongHandle &other );

	bool IsValid() const { return m_pBinding != nullptr; }
	ResourceHandle_t GetBinding() const { return m_pBinding; }

private:
	void AddRef();
	void Release();

	ResourceHandle_t m_pBinding;
};

template < typename T >
inline CStrongHandle< T > &CStrongHandle< T >::operator=( const CStrongHandle &other )
{
	if ( m_pBinding != other.m_pBinding )
	{
		Release();
		m_pBinding = other.m_pBinding;
		AddRef();
	}
	return *this;
}

template < typename T >
inline void CStrongHandle< T >::AddRef()
{
	if ( m_pBinding )
		++const_cast< ResourceBindingBase_t * >( m_pBinding )->m_nRefCount;
}

template < typename T >
inline void CStrongHandle< T >::Release()
{
	if ( m_pBinding && g_pResourceHandleUtils )
	{
		ResourceBindingBase_t *pBinding = const_cast< ResourceBindingBase_t * >( m_pBinding );
		--pBinding->m_nRefCount;
		if ( pBinding->m_nRefCount == 0 )
			g_pResourceHandleUtils->DeleteResource( m_pBinding );
	}
	m_pBinding = nullptr;
}

#endif // RESOURCEHANDLE_H
