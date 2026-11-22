//===== Copyright (c) 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: The tools' version control interface. Without the Perforce library one of two
//          stand-ins answers every call: file operations return true and queries false, 0, NULL
//          or an empty list; the one a tools session runs on also makes an edited file writable
//          and copies files on disk.
//
//===========================================================================//

#ifndef IP4_H
#define IP4_H
#ifdef _WIN32
#pragma once
#endif

#include "appframework/iappsystem.h"
#include "tier0/buffer_string.h"
#include "tier0/utlstring.h"
#include "tier0/utlsymbol.h"
#include "tier0/utlsymbollarge.h"
#include "tier0/utlvector.h"

// What the server knows about one file
// AMNOTE: The struct's name is in no binary
struct P4FileInfo_t
{
	// AMNOTE: The symbols are read with IP4::unk038
	CUtlSymbolLarge m_unk001;
	CUtlSymbolLarge m_unk002;
	uint8 m_unk003[16];
	CUtlSymbolLarge m_unk004;
	int m_unk005;
	int m_unk006;
	int m_unk007;
	bool m_unk008;
	bool m_unk009;
	bool m_unk010;
	bool m_unk011;
	// AMNOTE: How the file is open: 1 add, 2 edit, 3 delete, 4 integrate
	int m_unk012;
	// AMNOTE: The changelist the file is open in
	int m_unk013;
	int m_unk014;
	uint64 m_unk015[9];
};

// A pending changelist
// AMNOTE: The struct's name is in no binary
struct P4Changelist_t
{
	// AMNOTE: The changelist's number
	int m_unk001;
	uint8 m_unk002[18];
	// AMNOTE: The description, read with IP4::unk039
	CUtlSymbol m_unk003;
};

// One submitted change of a file
// AMNOTE: The struct's name is in no binary
struct P4FileCheckin_t
{
	// AMNOTE: The changelist's number
	int m_unk001;
	// AMNOTE: The date and time: year, month, day, hour and minute
	int m_unk002[5];
	uint8 m_unk003[8];
	CUtlString m_unk004;
	uint8 m_unk005[8];
	CUtlString m_unk006;
};

//-----------------------------------------------------------------------------
// Version control ("VP4003"). File paths are absolute.
//-----------------------------------------------------------------------------
abstract_class IP4 : public IAppSystem
{
public:
	// AMNOTE: True when Perforce can be used; false without the Perforce library
	virtual bool unk001() = 0;
	// AMNOTE: Returns 0 or 1 without the Perforce library; its arguments are not known
	virtual int unk002() = 0;
	// AMNOTE: Selects the implementation: 0 the stand-in that only returns constants, 1 the stand-in
	// that works on local files, 2 the Perforce library when it was loaded (otherwise the first).
	// True when the implementation's Init returns INIT_OK.
	virtual bool unk003( int nImplementation ) = 0;
	// AMNOTE: The address of an object the implementation keeps; its arguments and type are not known
	virtual void *unk004() = 0;
	// AMNOTE: Does nothing without the Perforce library; its arguments are not known
	virtual void unk005() = 0;
	// AMNOTE: Does nothing without the Perforce library
	virtual void unk006() = 0;
	// AMNOTE: Writes text about the file into pOut
	virtual void unk007( CBufferString *pOut, const char *pszPath ) = 0;
	virtual const CUtlVector< P4FileInfo_t > &unk008( const char *pszPath, bool bUnk ) = 0;
	// AMNOTE: Does nothing without the Perforce library; its arguments are not known
	virtual void unk009() = 0;
	// AMNOTE: Appends the open files to pFiles
	virtual void unk010( CUtlVector< P4FileInfo_t > *pFiles, bool bUnk ) = 0;
	// AMNOTE: Appends the open files under the search path ID to pFiles
	virtual void unk011( const char *pszPathID, CUtlVector< P4FileInfo_t > *pFiles ) = 0;
	// AMNOTE: Whether bUnk1 is a bool or an int is not known; the tools pass 50 for nUnk and true for bUnk2
	virtual const CUtlVector< P4FileCheckin_t > &unk012( const char *pszPath, bool bUnk1, int nUnk, bool bUnk2 ) = 0;
	// AMNOTE: Returns an empty list without the Perforce library; its arguments, element type and return type are not known
	virtual void *unk013() = 0;
	// AMNOTE: The pending changelists
	virtual const CUtlVector< P4Changelist_t > &unk014() = 0;
	// AMNOTE: Does nothing without the Perforce library; its arguments are not known
	virtual void unk015() = 0;

	// AMNOTE: The file operations return true without the Perforce library. The tools pass 0 and -1
	// for the two ints; edit (unk017) then makes the file writable when it exists and is in no
	// read-only search path, and returns false otherwise.
	// AMNOTE: Opens the file for add
	virtual bool unk016( const char *pszPath, int nUnk1, int nUnk2 ) = 0;
	// AMNOTE: Opens the file for edit
	virtual bool unk017( const char *pszPath, int nUnk1, int nUnk2 ) = 0;
	// AMNOTE: Opens the file for edit or add: 1 when it is open, 0 when it does not exist, -1 on failure
	virtual int unk018( const char *pszPath, int nUnk1, int nUnk2 ) = 0;
	// AMNOTE: Opens the file for delete
	virtual bool unk019( const char *pszPath ) = 0;
	// AMNOTE: Without the Perforce library, OpenFileForCopy with the same arguments; the tools pass 0 and -1
	// for the two ints, whose types are not shown
	virtual bool unk020( const char *pszPath, const char *pszDest, int nUnk1, int nUnk2 ) = 0;
	// AMNOTE: Returns true without the Perforce library; its arguments are not known
	virtual bool unk021() = 0;
	// AMNOTE: Syncs the file to its head revision; the tools pass -1
	virtual bool unk022( const char *pszPath, int nUnk ) = 0;
	// AMNOTE: Returns true without the Perforce library; its arguments are not known
	virtual bool unk023() = 0;
	// AMNOTE: Reverts the file
	virtual bool unk024( const char *pszPath ) = 0;
	// AMNOTE: The changelist later add, edit and delete calls open files in, by its description; NULL or ""
	// is the default changelist. Ignored without the Perforce library.
	virtual void unk025( const char *pszChangelist ) = 0;
	// AMNOTE: Opens the files for add
	virtual bool unk026( int nCount, const char **ppszPaths ) = 0;
	// AMNOTE: Opens the files for edit; without the Perforce library unk017 on each file, false at the first failure
	virtual bool unk027( int nCount, const char **ppszPaths ) = 0;
	// AMNOTE: Returns true without the Perforce library; its arguments are not known
	virtual bool unk028() = 0;
	// AMNOTE: Submits the files with the description; the tools pass 0 for nUnk
	virtual bool unk029( int nCount, const char **ppszPaths, const char *pszDescription, int nUnk ) = 0;
	// AMNOTE: Reverts the files
	virtual bool unk030( int nCount, const char **ppszPaths ) = 0;
	// AMNOTE: Returns true without the Perforce library; its arguments are not known
	virtual bool unk031() = 0;
	// AMNOTE: Reverts the file when it is unchanged
	virtual bool unk032( const char *pszPath ) = 0;
	// AMNOTE: True when the file is in Perforce
	virtual bool unk033( const char *pszPath ) = 0;
	// AMNOTE: Returns false without the Perforce library; its arguments are not known
	virtual bool unk034() = 0;
	// AMNOTE: The tools pass a path that ends in "#have"
	virtual bool unk035( const char *pszPath ) = 0;
	// AMNOTE: The file's state, 0 without the Perforce library
	virtual int unk036( const char *pszPath ) = 0;
	// AMNOTE: Returns 0 without the Perforce library; its arguments and return type are not known
	virtual void *unk037() = 0;
	// AMNOTE: The text of a symbol in the records above
	virtual const char *unk038( CUtlSymbolLarge symbol ) = 0;
	virtual const char *unk039( CUtlSymbol symbol ) = 0;
	// AMNOTE: unk040 to unk042 call unk056 with false before and with true after the implementation's
	// slot; they return false without the Perforce library
	virtual bool unk040( const char *pszPath, CBufferString *pUnk1, CBufferString *pUnk2 ) = 0;
	// AMNOTE: Their three arguments are passed on as unk040's are; their types are not known
	virtual bool unk041( void *pUnk1, void *pUnk2, void *pUnk3 ) = 0;
	virtual bool unk042( void *pUnk1, void *pUnk2, void *pUnk3 ) = 0;
	// AMNOTE: True when connected to the server
	virtual bool unk043( bool bUnk ) = 0;
	// AMNOTE: Return false without the Perforce library; their arguments are not known
	virtual bool unk044() = 0;
	virtual bool unk045() = 0;
	// AMNOTE: Fills pInfo; false when there is no information
	virtual bool unk046( const char *pszPath, P4FileInfo_t *pInfo ) = 0;
	// AMNOTE: The text of the last error; NULL without the Perforce library
	virtual const char *unk047() = 0;
	// AMNOTE: Does nothing without the Perforce library; its arguments are not known
	virtual void unk048() = 0;
	// AMNOTE: Creates a pending changelist and returns its number, negative on failure
	virtual int unk049( const char *pszDescription ) = 0;
	// AMNOTE: Sets the description of a pending changelist
	virtual bool unk050( int nChangelist, const char *pszDescription ) = 0;
	// AMNOTE: Opens the file for edit; pChangelist, which may be NULL, points to a number unk049 returned.
	// Without the Perforce library unk017.
	virtual bool unk051( const char *pszPath, int *pChangelist, int nUnk1, int nUnk2 ) = 0;
	// AMNOTE: Returns false without the Perforce library
	virtual bool unk052() = 0;
	// AMNOTE: Copies the file to pszDest, then opens the copy for edit as unk017 does
	virtual bool unk053( const char *pszSource, const char *pszDest ) = 0;
	// Without the Perforce library the stand-in of a tools session copies the file on disk
	virtual bool OpenFileForCopy( const char *pszSource, const char *pszDest ) = 0;

	// AMNOTE: Does nothing without the Perforce library; its arguments are not known
	virtual void unk101() = 0;
	// AMNOTE: Does nothing without the Perforce library
	virtual void unk102( bool bUnk ) = 0;
	// AMNOTE: The address of an object the implementation keeps; its arguments and type are not known
	virtual void *unk103() = 0;
	// AMNOTE: The tools pass "tools_keepalive"; returns 0 without the Perforce library
	virtual int unk104( const char *pszUnk ) = 0;
	// AMNOTE: Returns 0 without the Perforce library; its arguments and return type are not known
	virtual void *unk105() = 0;
	// AMNOTE: Returns false without the Perforce library; its arguments are not known
	virtual bool unk106() = 0;
	// AMNOTE: Return false without the Perforce library; their arguments are not known
	virtual bool unk107() = 0;
	// AMNOTE: Does nothing without the Perforce library; its arguments are not known
	virtual void unk108() = 0;
	virtual bool unk109() = 0;
	// AMNOTE: Returns a 24-byte value by value, all zero without the Perforce library; its type and its other
	// arguments are not known
	virtual void *unk110( void *pResult ) = 0;
	// AMNOTE: Returns false without the Perforce library; its arguments are not known
	virtual bool unk111() = 0;
	// AMNOTE: A 64-bit value, 0 without the Perforce library
	virtual uint64 unk112() = 0;
	// AMNOTE: Takes a 16-byte value by value as its first argument; returns false without the Perforce
	// library; its arguments are not known
	virtual bool unk113() = 0;

	// AMNOTE: The implementation's last virtual is its destructor; whether the interface or only the implementing class declares it is not known
	virtual ~IP4() {}
};

#endif // IP4_H
