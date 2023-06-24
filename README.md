# HongMuOSLoader
HongMuOS的efi加载器

##

##编译
准备内容
```
git clone https://github.com/tianocore/ekd2
cd edk2
git submodule update --init
git clone https://github.com/CodeMaster114514/HongMuOSLoader
make -C BaseTools
export EDK_TOOLS_PATH=$HOME/src/edk2/BaseTools
. edksetup.sh BaseTools
build
build -p HongMuOSLoaderPkg/HongMuOSLoaderPkg.dsc
```
