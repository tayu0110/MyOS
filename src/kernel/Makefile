TARGET	= kernel.elf

CC			= gcc
LD			= ld
NASM		= nasm
OBJCOPY	= objcopy

SRC 		= ..
TOOLS 	= $(SRC)/tools

OBJS		= main.o hankaku16.o font.o graphics.o util.o

CFLAGS	= -nostdinc -ffreestanding -m64 -mno-red-zone -fno-exceptions
INC			= -I$(TOOLS)/newlib-cygwin/newlib/libc/include -I/usr/lib/gcc/x86_64-linux-gnu/9/include
LDFLAGS = -z norelro --entry main -static -T./ld.scr
LDLIBS	= -L$(TOOLS)/build-newlib -lc

$(TARGET) : $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

%.o : %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

%.o : %.asm
	$(NASM) -f elf64 -o $@ $<

%.o : %.bin
	$(OBJCOPY) -I binary -O elf64-x86-64 -B i386 $< $@

%.bin :
	cp $(SRC)/resources/fonts/hankaku16.bin hankaku16.bin

.PHONY : all
all : $(TARGET)

.PHONY : clean
clean :
	rm *.o *.elf