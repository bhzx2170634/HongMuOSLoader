#include "Graphics.h"

STATUS
EFIAPI
SetDefinition(EFI_GRAPHICS_OUTPUT_PROTOCL GOP,int hight,int wide)
{
	EFI_STATUS status = EFI_SUCCESS;
	UINTN SizeOfInfo = 0;
	EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* info;
	for(int i;i < GOP->Mode->MaxMode;i++){
		status = GOP->QureyMode(
			GOP,
			i,
			&SizeOfInfo,
			&info
		);
		if(EFI_ERROR(status)){
			Print(L"Failed to QureyMode");
			return status;
		}
		if(
		info->HorizontalResolution == wide
		&&
		info->VerticalResolution == hight)
		{
			return GOP->SetMode(GOP,i);
		}
	}
	Print(L"Can turn definition");
	return EFI_PROTOCL_ERROR;
}
