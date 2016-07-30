/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include <rpc.h>
#include <midles.h>
#include <stdio.h>

#ifndef NT_SUCCESS
#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)
#endif

typedef struct _KULL_M_RPC_FCNSTRUCT {
	PVOID addr;
	size_t size;
} KULL_M_RPC_FCNSTRUCT, *PKULL_M_RPC_FCNSTRUCT;

typedef void (* PGENERIC_RPC_DECODE) (IN handle_t pHandle, IN PVOID pObject);
typedef void (* PGENERIC_RPC_ENCODE) (IN handle_t pHandle, IN PVOID pObject);
typedef void (* PGENERIC_RPC_FREE) (IN handle_t pHandle, IN PVOID pObject);
typedef size_t (* PGENERIC_RPC_ALIGNSIZE) (IN handle_t pHandle, IN PVOID pObject);

void __RPC_FAR * __RPC_USER midl_user_allocate(size_t cBytes);
void __RPC_USER midl_user_free(void __RPC_FAR * p);

BOOL generic_rpc_Decode(PVOID data, DWORD size, PVOID pObject, PGENERIC_RPC_DECODE fDecode);
void generic_rpc_Free(PVOID pObject, PGENERIC_RPC_FREE fFree);
BOOL generic_rpc_Encode(PVOID pObject, PVOID *data, DWORD *size, PGENERIC_RPC_ENCODE fEncode, PGENERIC_RPC_ALIGNSIZE fAlignSize);