#include "control.h"

#define X86_64 2
#define X86 1

#define ET_NONE		0
#define ET_REL		1
#define ET_EXEC		2
#define ET_DYN		3
#define ET_CORE		4
#define	ET_NUM		5
#define ET_LOOS		0xfe00
#define ET_HIOS		0xfeff
#define ET_LOPROC	0xff00
#define ET_HIPROC	0xffff

#define SHT_NULL	  0
#define SHT_PROGBITS	  1
#define SHT_SYMTAB	  2
#define SHT_STRTAB	  3
#define SHT_RELA	  4
#define SHT_HASH	  5
#define SHT_DYNAMIC	  6
#define SHT_NOTE	  7
#define SHT_NOBITS	  8
#define SHT_REL		  9
#define SHT_SHLIB	  10
#define SHT_DYNSYM	  11

#define	PT_NULL		0
#define PT_LOAD		1
#define PT_DYNAMIC	2
#define PT_INTERP	3
#define PT_NOTE		4
#define PT_SHLIB	5
#define PT_PHDR		6
#define PT_TLS		7
#define	PT_NUM		8
#define PT_LOOS		0x60000000
#define PT_GNU_EH_FRAME	0x6474e550
#define PT_GNU_STACK	0x6474e551
#define PT_GNU_RELRO	0x6474e552
#define PT_GNU_PROPERTY	0x6474e553
#define PT_LOSUNW	0x6ffffffa
#define PT_SUNWBSS	0x6ffffffa
#define PT_SUNWSTACK	0x6ffffffb
#define PT_HISUNW	0x6fffffff
#define PT_HIOS		0x6fffffff
#define PT_LOPROC	0x70000000
#define PT_HIPROC	0x7fffffff

typedef struct
{
	unsigned char ident[4];
	UINT8 class;
	UINT8 data;
	UINT8 version;
	UINT8 ABI;
	UINT8 ABI_version;
	UINT8 null[7];
	UINT16 type;
	UINT16 machine;
	UINT32 e_version;
	UINT64 enter_address;
	UINT64 phoff;
	UINT64 shoff;
	UINT32 eflags;
	UINT16 ehsize;
	UINT16 phsize;
	UINT16 phnum;
	UINT16 shsize;
	UINT16 shnum;
	UINT16 shstrdx;
} elf_header_64;

typedef struct
{
	unsigned char ident[4];
	UINT8 class;
	UINT8 data;
	UINT8 version;
	UINT8 ABI;
	UINT8 ABI_version;
	UINT8 null[7];
	UINT16 type;
	UINT16 machine;
	UINT32 e_version;
	UINT32 enter_address;
	UINT32 phoff;
	UINT32 shoff;
	UINT32 eflags;
	UINT16 ehsize;
	UINT16 phsize;
	UINT16 phnum;
	UINT16 shsize;
	UINT16 shnum;
	UINT16 shstrdx;
} elf_header_32;

typedef struct
{
	UINT32 type;
	UINT32 flags;
	UINT64 offset;
	UINT64 vaddr;
	UINT64 paddr;
	UINT64 filesz;
	UINT64 memsz;
	UINT64 align;
} program_header_64;

typedef struct
{
	UINT32 type;
	UINT32 offset;
	UINT32 vaddr;
	UINT32 paddr;
	UINT32 filesz;
	UINT32 memsz;
	UINT32 flags;
	UINT32 align;
} program_header_32;

int enter_core(
	IN EFI_HANDLE ImageHandle,
	IN EFI_SYSTEM_TABLE* SystemTable,
	IN Contra_Table table
);
