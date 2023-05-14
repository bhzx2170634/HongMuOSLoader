#ifndef included
#define included 1
#include <Uefi.h>
#include <Library/UefiLib.h>
#endif
#include <Protocol/SimpleFileSystem.h>
#include <Guid/FileInfo.h>

EFI_STATUS GetFileHandle(
	EFI_HANDLE,
	CHAR16*,
	EFI_FILE_PROTOCOL**
);

EFI_STATUS ReadFile(
	EFI_FILE_PROTOCOL*,
	EFI_PHYSICAL_ADDRESS*
);
