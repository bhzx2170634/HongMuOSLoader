#ifndef included
#define included 1
#include <Uefi.h>
#include <Library/UefiLib.h>
#endif

EFI_STATUS
EFI_API
GetFileHandle(
	IN EFI_HANDLE,
	IN CHAR16*,
	OUT EFI_FILE_PROTOCOL**
);
EFI_STATUS
EFI_API
ReadFile(
	IN EFI_FILE_PROTOCOL,
	OUT EFI_PHYSICAL_ADDRESS*
);
