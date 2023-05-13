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
	if(EFI_ERROR(status)){
		Print(L"Can't open protocol");
		return status;
	}
	EFI_FILE_PROTOCOL* Root;
	status = FileSystem->OpenVolume(FileSystem,&Root);
	if (EFI_ERROT(status))
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
	if (EFI_ERROR(status))
	{
		Print(L"Can't open files");
		return status;
	}
	return status;
}
