#include "Draw.h"

EFI_STATUS DrawPhoto(
	EFI_HANDLE ImageHandle,
	EFI_GRAPHICS_OUTPUT_PROTOCOL* GOP,
	int* step
)
{
	EFI_STATUS status = EFI_SUCCESS;
	EFI_FILE_PROTOCL* file;
	if(
	GOP->Mode->Info->HorizontalResolution * 9
	==
	GOP->Mode_>Info->VerticalResolution * 16){
		status = GetFileHandle(
			ImageHandle,
			L"\\Logo16:9.BMP",
			&file
		);
		if(EFI_ERROR(status))
		{
			Print(L"Can get Logo file handle");
			return status;
		}
	}else{
		Print(L"Can find suitable logo");
		status = 114514;
		return status;
	}
	EFI_PHYSICAL_ADDRESS FileBase;
	status = ReadFile(
		file,
		&FileBase
	);
	if(EFI_ERROR(status))
	{
		Print(L"Failed to read file");
		return status;
	}
	bmp_head* head = (bmp_head*) FileBase;
	EFI_PHYSICAL_ADDRESS bitData;
	if(head->biHeight < 0)
	{
		bitData = FileBase + (EFI_PHYSICAL_ADDRESS) head->bfSize;
	}else if(head->biHeight > 0)
	{
		bitData = FileBase + (EFI_PHYSICAL_ADDRESS) head->bfOffBits;
	}else{
		Print(L"There is no file with a height equal to zero");
		status = 114515;
		return status;
	}
	step = GOP->Mode->Info->VerticalResolution + head->biHeight + 100;
}
