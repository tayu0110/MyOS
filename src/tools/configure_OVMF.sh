#!/bin/bash

git clone https://github.com/tianocore/edk2.git
cd edk2/
git submodule update --init

source edksetup.sh
make -C BaseTools
sed -r 's/ACTIVE_PLATFORM.*/ACTIVE_PLATFORM = OvmfPkg\/OvmfPkgX64.dsc/' -i Conf/target.txt
sed -r 's/TOOL_CHAIN_TAG.*/TOOL_CHAIN_TAG = GCC5/' -i Conf/target.txt
sed -r 's/TARGET_ARCH.*/TARGET_ARCH = X64/' -i Conf/target.txt

build
