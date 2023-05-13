#ifndef included
#define included 1
#include <Uefi.h>
#include <Library/UefiLib.h>
#endif
#include <Protocol/SimpleFileSystem.h>

EFI_STATUS GetFileHandle(
	EFI_HANDLE,
	CHAR16*,
	EFI_FILE_PROTOCOL**
);
