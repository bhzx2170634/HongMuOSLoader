[Defines]
	PLATFORM_NAME = HongMuOSLoaderPkg
	PLATFORM_GUID = 0b3a6781-5c7c-47b8-83c4-5c97a77368b0
	PLATFORM_VERSION = 0.1
	DSC_SPECIFICATION = 0x00010005
	SUPPORTED_ARCHITECTURES = X64
	BUILD_TARGETS = DEBUG|RELEASE

[LibraryClasses]
	UefiLib|MdePkg/Library/UefiLib.inf
	UefiApplicationEntryPoint|MdePkg/Library/UefiApplicationEntryPoint.inf

[Components]
	HongMuOSLoaderPkg/HongMuOSLoader.inf
