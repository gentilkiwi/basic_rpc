#include <Windows.h>
#include <stdio.h>
#include "generic_rpc.h"
#include "KiwiInterface.h"

void printHex(PVOID data, DWORD size);
void printStruct(PMYSTRUCT_TYPE myStruct);

int wmain(int argc, wchar_t * argv[])
{
	MYSTRUCT_TYPE myStruct = {42, L"Un test de Kiwi", 7, NULL}, myStructDecoded = {0};
	PVOID encodedData;
	DWORD encodedSize;

	if(myStruct.elements = (PDWORD) LocalAlloc(LPTR, myStruct.cbElements * sizeof(DWORD)))
	{
		myStruct.elements[0] = 123;
		myStruct.elements[myStruct.cbElements - 1] = 456;
		
		wprintf(L"myStruct:\n");
		printStruct(&myStruct);
		wprintf(L"myStructDecoded:\n");
		printStruct(&myStructDecoded);

		if(generic_rpc_Encode(&myStruct, &encodedData, &encodedSize, (PGENERIC_RPC_ENCODE) MYSTRUCT_TYPE_Encode, (PGENERIC_RPC_ALIGNSIZE) MYSTRUCT_TYPE_AlignSize))
		{
			wprintf(L"NDR Encoded data (%u):\n", encodedSize);
			printHex(encodedData, encodedSize);

			if(generic_rpc_Decode(encodedData, encodedSize, &myStructDecoded, (PGENERIC_RPC_DECODE) MYSTRUCT_TYPE_Decode))
			{
				wprintf(L"myStructDecoded:\n");
				printStruct(&myStructDecoded);
				generic_rpc_Free(&myStructDecoded, (PGENERIC_RPC_FREE) MYSTRUCT_TYPE_Free);
			}
			LocalFree(encodedData);
		}
		LocalFree(myStruct.elements);
	}
	return ERROR_SUCCESS;
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

void printStruct(PMYSTRUCT_TYPE myStruct)
{
	DWORD i;
	wprintf(L"\t.simpleValue= %u\n", myStruct->simpleValue);
	wprintf(L"\t.Name       = %s\n", myStruct->Name);
	wprintf(L"\t.cbElements = %u\n", myStruct->cbElements);
	for(i = 0; i < myStruct->cbElements; i++)
		wprintf(L"\t.elements[%u] = %u\n", i, myStruct->elements[i]);
	wprintf(L"\n");
}