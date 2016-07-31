#include <Windows.h>
#include <stdio.h>
#include "generic_rpc.h"
#include "ms-bkrp.h"

const GUID
	BACKUPKEY_BACKUP_GUID = {0x7f752b10, 0x178e, 0x11d1, {0xab, 0x8f, 0x00, 0x80, 0x5f, 0x14, 0xdb, 0x40}},
	BACKUPKEY_RESTORE_GUID_WIN2K = {0x7fe94d50, 0x178e, 0x11d1, {0xab, 0x8f, 0x00, 0x80, 0x5f, 0x14, 0xdb, 0x40}},
	BACKUPKEY_RETRIEVE_BACKUP_KEY_GUID = {0x018ff48a, 0xeaba, 0x40c6, {0x8f, 0x6d, 0x72, 0x37, 0x02, 0x40, 0xe9, 0x67}},
	BACKUPKEY_RESTORE_GUID = {0x47270c64, 0x2fc7, 0x499b, {0xac, 0x5b, 0x0e, 0x37, 0xcd, 0xce, 0x89, 0x9a}};

BOOL kull_m_rpc_bkrp_generic(RPC_BINDING_HANDLE *hBinding, const GUID * pGuid, PVOID DataIn, DWORD dwDataIn, PVOID *pDataOut, DWORD *pdwDataOut);
void printHex(PVOID data, DWORD size);

int wmain(int argc, wchar_t * argv[])
{
	RPC_BINDING_HANDLE hBinding;
	wchar_t dataIn[] = L"a cleartext message!";
	PVOID pDataOut, pDataOut2;
	DWORD dwDataOut, dwDataOut2;

	if(argc > 1)
	{
		wprintf(L"Will use \'%s\' for DC name...\n", argv[1]);
		if(kull_m_rpc_createBinding(L"ncacn_np", argv[1], L"\\pipe\\protected_storage", L"ProtectedStorage", RPC_C_IMP_LEVEL_IMPERSONATE, &hBinding, NULL))
		{
			wprintf(L"\n* Retrieve RSA Public Key\n");
			if(kull_m_rpc_bkrp_generic(&hBinding, &BACKUPKEY_RETRIEVE_BACKUP_KEY_GUID, (PVOID) 0xbadc00fe, 0, &pDataOut, &dwDataOut)) // don't ask me why dummy data is needed here (not used).
			{
				wprintf(L"  > pDataOut @ 0x%p (%u)\n", pDataOut, dwDataOut);
				//printHex(pDataOut, dwDataOut);
				MIDL_user_free(pDataOut);
			}

			wprintf(L"\n* Backup a secret (%s)\n", dataIn);
			if(kull_m_rpc_bkrp_generic(&hBinding, &BACKUPKEY_BACKUP_GUID, &dataIn, sizeof(dataIn), &pDataOut, &dwDataOut))
			{
				wprintf(L"  > pDataOut @ 0x%p (%u)\n", pDataOut, dwDataOut);
				printHex(pDataOut, dwDataOut);

				wprintf(L"\n* Restore a secret\n");
				if(kull_m_rpc_bkrp_generic(&hBinding, &BACKUPKEY_RESTORE_GUID, pDataOut, dwDataOut, &pDataOut2, &dwDataOut2))
				{
					wprintf(L"  > pDataOut2 @ 0x%p (%u)\n", pDataOut, dwDataOut);
					wprintf(L"  > Secret : %s\n", pDataOut2);
					MIDL_user_free(pDataOut2);
				}
				MIDL_user_free(pDataOut);
			}

			kull_m_rpc_deleteBinding(&hBinding);
		}
	}
	else wprintf(L"[ERROR] A DC name is needed in argument\n");
	return ERROR_SUCCESS;
}

BOOL kull_m_rpc_bkrp_generic(RPC_BINDING_HANDLE *hBinding, const GUID * pGuid, PVOID DataIn, DWORD dwDataIn, PVOID *pDataOut, DWORD *pdwDataOut)
{
	BOOL status = FALSE;
	NET_API_STATUS netStatus;
	*pDataOut = NULL;
	*pdwDataOut = 0;
	RpcTryExcept
	{
		netStatus = BackuprKey(*hBinding, (GUID *) pGuid, (PBYTE) DataIn, dwDataIn, (PBYTE *) pDataOut, pdwDataOut, 0);
		if(!(status = (netStatus == 0)))
			wprintf(L"[ERROR] BackuprKey: 0x%08x (%u)\n", netStatus, netStatus);
	}
	RpcExcept(RPC_EXCEPTION)
		wprintf(L"[ERROR] RPC Exception: 0x%08x (%u)\n", RpcExceptionCode(), RpcExceptionCode());
	RpcEndExcept
	return status;
}

void printHex(PVOID data, DWORD size)
{
	DWORD i;
	for(i = 0; i < size; i++)
	{
		wprintf(L"%02x ", ((PBYTE) data)[i]);
		if(!((i + 1) % 16))
			wprintf(L"\n");
	}
	wprintf(L"\n");
}