

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sat Jul 30 20:38:55 2016
 */
/* Compiler settings for KiwiInterface.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#include "midles.h"

#ifndef __KiwiInterface_h__
#define __KiwiInterface_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __KiwiInterface_INTERFACE_DEFINED__
#define __KiwiInterface_INTERFACE_DEFINED__

/* interface KiwiInterface */
/* [explicit_handle][nocode][unique][version][uuid] */ 

typedef /* [decode][encode] */ struct _MYSTRUCT_TYPE
    {
    DWORD simpleValue;
    WCHAR *Name;
    DWORD cbElements;
    DWORD *elements;
    } 	MYSTRUCT_TYPE;

typedef struct _MYSTRUCT_TYPE *PMYSTRUCT_TYPE;



extern RPC_IF_HANDLE KiwiInterface_v1_0_c_ifspec;
extern RPC_IF_HANDLE KiwiInterface_v1_0_s_ifspec;
#endif /* __KiwiInterface_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */


size_t
MYSTRUCT_TYPE_AlignSize(
    handle_t _MidlEsHandle,
    MYSTRUCT_TYPE * _pType);


void
MYSTRUCT_TYPE_Encode(
    handle_t _MidlEsHandle,
    MYSTRUCT_TYPE * _pType);


void
MYSTRUCT_TYPE_Decode(
    handle_t _MidlEsHandle,
    MYSTRUCT_TYPE * _pType);


void
MYSTRUCT_TYPE_Free(
    handle_t _MidlEsHandle,
    MYSTRUCT_TYPE * _pType);

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


