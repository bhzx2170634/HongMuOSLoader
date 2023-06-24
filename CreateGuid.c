#include <Uefi.h>
#include <Library/UefiRuntimeServicesTableLib.h>

UINT32 base = 1;

void srand(EFI_TIME* time)
{
	base = time->Year * time->Month *
		time->Day * time->Hour *
		time->Minute * time->Second *
		time->Nanosecond;
}

double rand()
{
	base = base * 9154037 + 114514;
	return (base*0xffff)%123456;
}

EFI_GUID CreateGuid()
{
	EFI_TIME time;
	EFI_TIME_CAPABILITIES time_capabilities;
	gRT->GetTime(
		&time,
		&time_capabilities
	);
	srand(&time);
	EFI_GUID ret;
	ret.Data1 = rand()*0xffffffff;
	ret.Data2 = rand()*0xffff;
	ret.Data3 = rand()*0xffff;
	for(int i = 0;i < 8;++i)
	{
		ret.Data4[i] = rand()*0xff;
	}
	return ret;
}
