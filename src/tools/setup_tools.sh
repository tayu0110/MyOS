#!/bin/bash

ls | grep -Ev "^.*\.sh$" | xargs rm -rf
bash get_newlib.sh
bash compile_newlib.sh
bash configure_gnu_efi.sh
bash configure_OVMF.sh
