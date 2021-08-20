#!/bin/bash
# disk_name=disk.img
disk_name=$1
expect -c "
  set timeout -1
  spawn sudo gdisk $disk_name
  expect \"sudo\"
  send \"tayu01101440\n\"
  expect \"Command\"
  send \"n\n\"
  expect \"Partition\"
  send \"1\n\"
  expect \"First\"
  send \"2048\n\"
  expect \"Last\"
  send \"409600\n\"
  expect \"GUID\"
  send \"ef00\n\"
  expect \"Command\"
  send \"n\n\"
  expect \"Partition\"
  send \"2\n\"
  expect \"First\"
  send \"411648\n\"
  expect \"Last\"
  send \"614366\n\"
  expect \"GUID\"
  send \"8300\n\"
  expect \"Command\"
  send \"w\n\"
  expect \"(Y/N)\"
  send \"y\n\"
"
timeout=5


exit 0