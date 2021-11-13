TARGET	= ./loader.efi
DISKIMG	= ./disk.img
RUNENV	= ./mnt

SRC 		= ..
GNUEFI	= $(SRC)/tools/gnu-efi
LIBDIR	= $(SRC)/tools/gnu-efi/gnuefi
OVMFDIR	= $(SRC)/tools/edk2/Build/OvmfX64/DEBUG_GCC5/FV

CC			= gcc
AS			= as
LD 			= ld
AR			= ar
RABLIB	= ranlib
OBJCOPY = objcopy

FORMAT		= --target efi-app-x86_64

OBJS 			= main.o util.o fs.o load.o

CFLAGS		= -I. -I$(GNUEFI)/inc -I$(GNUEFI)/inc/x86_64 -I$(GNUEFI)/inc/protocol -Wno-error=pragmas -mno-red-zone -mno-avx -fpic -g -O2 -Wall -Wextra -Werror -fshort-wchar -fno-strict-aliasing -ffreestanding -fno-stack-protector -fno-stack-check -fno-stack-check -fno-merge-all-constants -DCONFIG_x86_64 -DGNU_EFI_USE_MS_ABI -maccumulate-outgoing-args --std=c11 -D__KERNEL__ -I/usr/src/sys/build/include
LDFLAGS		= -nostdlib --warn-common --no-undefined --fatal-warnings --build-id=sha1 -shared -Bsymbolic -L$(GNUEFI)/lib -L$(LIBDIR) $(LIBDIR)/crt0-efi-x86_64.o 
LDFLAGS		+= -fPIC
LDLIBS		+= -lefi -lgnuefi /usr/lib/gcc/x86_64-linux-gnu/9/libgcc.a -T $(LIBDIR)/elf_x86_64_efi.lds

.PHONY : all
all : $(TARGET)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

loader.so : $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

$(TARGET) : loader.so
	$(OBJCOPY) -j .text -j .sdata -j .data -j .dynamic -j .dynsym -j .rel \
		    -j .rela -j .rel.* -j .rela.* -j .rel* -j .rela* \
		    -j .reloc $(FORMAT) $< $@

# To use the mkfs.vfat command with the --offset option, dosfstools 4.2 or later version is required.
$(DISKIMG) : $(TARGET)
	sudo dd if=/dev/zero of=$@ bs=1048576 count=300
	bash make_disk.sh $@
	sudo mkfs.vfat -n "TYNIX" -s 2 -S 512 --offset 2048 -R 32 -F 32 $@

# offset -> 512(logical sector size) * 2048(the offset of put EFI system partition)
$(RUNENV) : $(DISKIMG)
	mkdir $@ -p
	sudo mount -t vfat -o loop,offset=1048576 $< $@/
	sudo mkdir $@/EFI/BOOT -p
	sudo cp $(TARGET) $@/EFI/BOOT/BOOTX64.EFI
	sleep 0.5
	sudo umount $@

.PHONY : clean
clean :
	rm *.o
	rm *.so
	rm *.efi
	rm *.img
	sudo rm $(RUNENV) -rf

.PHONY : image
image : $(DISKIMG)

.PHONY : runenv
runenv : $(RUNENV)

.PHONY : boot
boot : $(RUNENV)
	sudo mount -t vfat -o loop,offset=1048576 disk.img mnt/
	sudo cp ../kernel/kernel.elf mnt/
	sudo umount mnt/
	sudo qemu-system-x86_64 \
		-m 1G \
		-boot menu=on \
		-drive if=pflash,format=raw,readonly,file=$(OVMFDIR)/OVMF_CODE.fd \
		-drive if=pflash,format=raw,file=$(OVMFDIR)/OVMF_VARS.fd \
		-drive if=ide,index=0,media=disk,format=raw,file=$(DISKIMG) \
		-device nec-usb-xhci,id=xhci \
		-device usb-mouse \
		-device usb-kbd \
		-monitor stdio
