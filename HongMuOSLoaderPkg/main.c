#include <Uefi.h>
#include <Library/UefiLib.h>
#include "Graphics/Graphics.h"

EFI_STATUS EFIAPI UefiMain(
		IN EFI_HANDLE ImageHandle,
		IN EFI_STSTEM_TABLE* SystemTable
){
	EFI_STATUS status = EFI_SUCCESS;
	EFI_BOOT_SERVICES* gBS = SystemTable->BootServices;
	UINTN NoHandle = 0
		EFI_HANDLE* GraphicsProtocol;
	status = gBS->LocatetHandleBuffer(
			ByProTocol,
			&gEfiGraphicsOutputProtocolGuid,
			NULL,
			&NoHandle,
			&GraphicsProtocol
	);
	Print(L"status = %d\nNoHandle = %d",status,NoHandle);
	if(EFI_ERROR(status)){
		Print(L"Failed to LocateHandleBuffer\n");
		return status;
	}
	EFI_GRAPHICS_OUTPUT_PROTOCOL* GOP;
	status = gBS->OpenProtocl(
		GraphicsProtocol[1],
		&gEfiGraphicsOutputProtocolGuid,
		(void**) &GOP,
		NULL,
		EFI_OPEN_PROTOCOL_GET_PROTOCOL
	);
	status = SetDefinition(GOP,1080,1920);
	return status;
}
