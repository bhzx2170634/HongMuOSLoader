#include <Uefi.h>
#include <Library/UefiLib.h>
#include "Graphics/Graphics.h"
#include "elf.h"
#include "CreateGuid.h"

EFI_STATUS EFIAPI UefiMain(
		IN EFI_HANDLE ImageHandle,
		IN EFI_SYSTEM_TABLE* SystemTable
){
	//需要的变量定义
	EFI_STATUS status = EFI_SUCCESS;
	Contra_Table table;
	EFI_BOOT_SERVICES* gBS = SystemTable->BootServices;
	UINTN NoHandle = 0;
	
	EFI_HANDLE* GraphicsProtocol;
	status = gBS->LocateHandleBuffer(
			ByProtocol,
			&gEfiGraphicsOutputProtocolGuid,
			NULL,
			&NoHandle,
			&GraphicsProtocol
	);
	Print(L"status = %d\nNoHandle = %d",status,NoHandle);
	if(EFI_ERROR(status)){
		Print(L"Failed to Locate HandleBuffer\n");
		return status;
	}
	table.GOP_count = NoHandle;
	EFI_GRAPHICS_OUTPUT_PROTOCOL** GOP;
	status = gBS->AllocatePool(
		EfiLoaderData,
		sizeof(EFI_GRAPHICS_OUTPUT_PROTOCOL*) * NoHandle,
		(void**) &GOP
	);
	if(EFI_ERROR(status))
	{
		Print(L"Failed to creat protocol storage\n");
		return status;
	}
	for(UINTN i = 0;i < NoHandle;++i)
	{
		status = gBS->OpenProtocol(
			GraphicsProtocol[i],
			&gEfiGraphicsOutputProtocolGuid,
			(void**) &GOP[i],
			ImageHandle,
			NULL,
			EFI_OPEN_PROTOCOL_GET_PROTOCOL
		);
		if(EFI_ERROR(status))
		{
			Print(L"Failed to Open Protocol\n");
			return status;
		}
	}
	table.GOP = GOP;
	status = gBS->FreePool(GraphicsProtocol);
	if(EFI_ERROR(status))
	{
		Print(L"Failed to free handle buffer\n");
		return status;
	}

	status = SetDefinition(GOP[0],1080,1920);

	EFI_HANDLE* DiskIoProtocol;
	status = gBS->LocateHandleBuffer(
		ByProtocol,
		&gEfiDiskIoProtocolGuid,
		NULL,
		&NoHandle,
		&DiskIoProtocol
	);
	if(EFI_ERROR(status))
	{
		Print(L"Failed to Locate Handle Buffer\n");
		return status;
	}
	table.DiksIo_count = NoHandle;
	EFI_DISK_IO_PROTOCOL** DiskIo;
	status = gBS->AllocatePool(
		EfiRuntimeServicesData,
		sizeof(EFI_DISK_IO_PROTOCOL*) * NoHandle,
		(void**) &Disk
	);
	for(UINTN i = 0;i < NoHandle,++i)
	{
		status = gBS->OpenProtocol(
			DiskIoProtocol[i],
			&gEfiDiskIoProtocol,
			(void**) &DiskIo[i],
			ImageHandle,
			NULL,
			EFI_OPEN_PROTOCOL_GET_PROTOCOL
		);
		if(EFI_ERROR(status))
		{
			Print(L"Can't open DiskIoProtocol in %dth.\n",i);
			return status;
		}
	}
	table.DiksIo = DiskIo;
	gBS->FreePool(DiskIoProtocol);
	if(EFI_ERROR(status))
	{
		Print(L"Failed to free Handle buffer\n");
		return status;
	}

	EFI_HANDLE* DiskIo2Protocol;
	status = gBS->LocateHandleBuffer(
		ByProtocol,
		&gEfiDiskIo2ProtocolGuid,
		NULL,
		&NoHandle,
		&DiskIo2Protocol
	);
	if(EFI_ERROR(status))
	{
		Print(L"Failed to locate handle buffer\n");
		return status;
	}
	EFI_DISK_IO2_PROTOCOL** DiskIo2;
	status = gBS->AllocatePool(
		EfiRuntimeServiceData,
		sizeof(EFI_DISK_IO2_PROTOCOL*),
		(void**) &DiskIo2
	);
	for(UINTN i = 0;i < NoHandle;++i)
	{
		status = gBS->OpenProtocol(
			DiskIo2Protocol[i],
			&gEfiDiskIo2ProtocolGuid,
			(void**) &DiskIo2[i],
			ImageHandle,
			NULL,
			EFI_OPEN_PROTOCOL_GET_PROTOCOL
		);
		if(EFI_ERROR(status))
		{
			Print(L"Failed to open DiskIo2 Protocol");
			return status;
		}
	}

	EFI_

	UINTN SizeOfMemMap;
	UINTN MemoryKey;
	UINTN DescriptorSize;
	UINT32 DescriptorVersion;
	status = gBS->GetMemoryMap(
		&SizeOfMemMap,
		NULL,
		&MemoryKey,
		&DescriptorSize,
		&DescriptorVersion
	);
	if(EFI_ERROR(status))
	{
		Print(L"Failed to get size of Memory Map\n");
		return status;
	}
	EFI_MEMORY_DESCRIPTOR* MemoryMap;
	status = gBS->AllocatePool(
		EfiRuntimeServicesData,
		SizeOfMemoryMap,
		&MemoryMap
	);
	if(EFI_ERROR(status))
	{
		Print(L"Failed to allocate Memory Map buffer\n");
	}
	status = gBS->GetMemoryMap(
		&SizeOfMemoryMap,
		MemoryMap,
		&MemoryKey,
		&DescriptorSize,
		&DescriptorVersion
	);
	if(EFI_ERROR(status))
	{
		Print(L"Failed to get Memory Map\n");
		return status;
	}
	table.memory.map = MemoryMap;
	table.memory.MapSize = SizeOfMemoryMap;
	table.memory.key = MemoryKey;
	table.memory.size = DescriptorSize;
	table.memory.version = DescriptorVersion;
	enter_core(ImageHandle,SystemTable,table);
	return status;
}
