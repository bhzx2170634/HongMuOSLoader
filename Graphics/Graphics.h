#ifndef included
#define included 1
#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Protocol/GraphicsOutput.h>
#endif

EFI_STATUS
SetDefinition(EFI_GRAPHICS_OUTPUT_PROTOCOL*,int,int);
