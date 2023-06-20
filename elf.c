#include <Uefi.h>
#include <stdbool.h>
#include "FileIO/file.h"
#include "elf.h"

EFI_PHYSICAL_ADDRESS reload(EFI_PHYSICAL_ADDRESS);
bool is_elf_exec_file(EFI_PHYSICAL_ADDRESS);

int enter_core(
	IN EFI_HANDLE ImageHandle,
	IN EFI_SYSTEM_TABLE* SystemTable,
	IN Contra_Table table
)
{
	EFI_BOOT_SERVICES* gBS = SystemTable->
		BootServices;
	EFI_FILE_PROTOCOL* File;
	GetFileHandle(
		ImageHandle,
		L"\\system\\core.elf",
		&File
	);
	EFI_PHYSICAL_ADDRESS file_data;
	ReadFile(
		File,
		&file_data
	);
	File->Close(File);
	EFI_PHYSICAL_ADDRESS EnterAddress;
	if(is_elf_exec_file(file_data))
	{
		 EnterAddress = reload(file_data);
	}else
	{
		return 0;
	}
	int (*enter_core) (EFI_HANDLE ImageHandle,EFI_SYSTEM_TABLE* SystemTable,Contra_Table table) = (int (*) (EFI_HANDLE ImageHandle,EFI_SYSTEM_TABLE* SystemTable,Contra_Table table)) EnterAddress;
	return enter_core(ImageHandle,SystemTable,table);
}

bool is_elf_exec_file(EFI_PHYSICAL_ADDRESS data)
{
	elf_header_64* header = (elf_header_64*) data;
	int test = *(int*) header->ident;
	if(test == 0x464c457F)
	{
		if(header->class == X86_64)
		{
			if(header->type == ET_EXEC)
			{
				return true;
			}else
			{
				return false;
			}
		}else if(header->class == X86)
		{
			return false;//暂不支持
		}
	}else
	{
		return false;
	}
	return true;
}

EFI_PHYSICAL_ADDRESS reload(
	EFI_PHYSICAL_ADDRESS file_data
)
{
	elf_header_64* elf_header =
		(elf_header_64*) file_data;
	program_header_64* program_header =
		(program_header_64*)
		(file_data+elf_header->phoff);
	EFI_PHYSICAL_ADDRESS Max =
		0xFFFFFFFFFFFFFFFF,
		Mini = 0;
	for(int i = 0;i < elf_header->phnum;++i)
	{
		if(program_header[i].type ==
			PT_LOAD)
		{
			if(Max >
				program_header[i].paddr)
			{
				Max = program_header[i].paddr;
			}
			if(Mini <
				(program_header[i].paddr + program_header[i].memsz))
			{
				Mini = program_header[i].paddr + program_header[i].memsz;
			}
		}
	}
}
