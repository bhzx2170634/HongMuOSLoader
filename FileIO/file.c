#include "file.h"
#include <Library/UefiBootServicesTableLib.h>

EFI_STATUS
GetFileHandle(EFI_HANDLE ImageHandle,CHAR16* FilePath,EFI_FILE_PROTOCOL** FileHandle){
	EFI_STATUS status = EFI_SUCCESS;
	UINTN HandleCount = 0;
	EFI_HANDLE* HandleBuffer;
	status = gBS->LocateHandleBuffer(
		ByProtocol,
		&gEfiSimpleFileSystemProtocolGuid,
		NULL,
		&HandleCount,
		&HandleBuffer
	);
	if(EFI_ERROR(status)){
		Print(L"Can't find FileSystem");
		return status;
	}
	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* FileSystem;
	status = gBS->OpenProtocol(
		HandleBuffer[0],
		&gEfiSimpleFileSystemProtocolGuid,
		(void**) &FileSystem,
		ImageHandle,
		NULL,
		EFI_OPEN_PROTOCOL_GET_PROTOCOL
	);
	gBS->FreePool(HandleBuffer);
	if(EFI_ERROR(status)){
		Print(L"Can't open protocol");
		return status;
	}
	EFI_FILE_PROTOCOL* Root;
	status = FileSystem->OpenVolume(FileSystem,&Root);
	if (EFI_ERROR(status))
	{
		Print(L"Can't open volume");
		return status;
	}
	status = Root->Open(
		Root,
		FileHandle,
		FilePath,
		EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
		EFI_OPEN_PROTOCOL_GET_PROTOCOL
	);
	Root->Close(Root);
	gBS->CloseProtocol(
		FileSystem,
		&gEfiSimpleFileSystemProtocolGuid,
		ImageHandle,
		NULL);
	if (EFI_ERROR(status))
	{
		Print(L"Can't open files");
		return status;
	}
	return status;
}

EFI_STATUS ReadFile(
	EFI_FILE_PROTOCOL* file,
	EFI_PHYSICAL_ADDRESS* FileBase
)
{
	EFI_STATUS status = EFI_SUCCESS;
	EFI_FILE_INFO* FileInfo;
	UINTN InfoSize = sizeof(EFI_FILE_INFO) + 128;
	status = gBS->AllocatePool(
		EfiLoaderData,
		InfoSize,
		(void**) &FileInfo
	);
	if(EFI_ERROR(status)){
		Print(L"Allocate pool failed");
		return status;
	}
	status = file->GetInfo(
		file,
		&gEfiFileInfoGuid,
		&InfoSize,
		(void**) &FileInfo
	);
	if(EFI_ERROR(status))
	{
		Print(L"Can't get info of file");
		return status;
	}
	UINTN FilePages = (FileInfo->FileSize >> 12) + 1;
	status = gBS->AllocatePages(
		AllocateAnyPages,
		EfiLoaderData,
		FilePages,
		FileBase
	);
	if(EFI_ERROR(status))
	{
		Print(L"Can't allocate pages");
		return status;
	}
	status = file->Read(
		file,
		&FileInfo->FileSize,
		&FileBase
	);
	if(EFI_ERROR(status))
	{
		Print(L"Read failed");
		return status;
	}
	gBS->FreePool(FileInfo);
	return status;
}
