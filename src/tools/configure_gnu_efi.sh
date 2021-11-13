#!/bin/bash

git clone https://git.code.sf.net/p/gnu-efi/code gnu-efi
cd gnu-efi
make
cd gnuefi
make
cd ../lib
make