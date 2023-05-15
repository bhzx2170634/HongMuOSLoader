#include "../FileIO/file.h"
#include "../Graphics/Graphics.h"

EFI_STATUS DrawPhoto(
	EFI_HANDLE,
	EFI_GRAPHICS_OUTPUT_PROTOCOL*
	int*
);

typedef struct
{
	char bfType[2];
	int bfSize;
	short bfReserved1;
	short bfReserved2;
	int bfOffBits;
	int biSize;
	int biWidth;
	int biHeight;
	short biPlanes;
	short biBitCount;
	int biCompression;
	int biSizeImages;
	int biXPelsPerMeter;
	int biYPelsPerMeter;
	int biClrUsed;
	int biClrImportant;
} bmp_head;
