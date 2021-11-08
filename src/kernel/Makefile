TARGET	= kernel.elf

CC			= gcc
LD			= ld
NASM		= nasm
OBJCOPY	= objcopy

SRC 		= ..
TOOLS 	= $(SRC)/tools
OBJDIR	= obj

OBJS		= $(OBJDIR)/main.o $(OBJDIR)/hankaku16.o $(OBJDIR)/font.o $(OBJDIR)/graphics.o $(OBJDIR)/util.o $(OBJDIR)/print.o \
					$(OBJDIR)/pci.o $(OBJDIR)/portio.o $(OBJDIR)/sup_lib.o $(OBJDIR)/xhci.o $(OBJDIR)/context.o

CFLAGS	= -nostdinc -ffreestanding -m64 -mno-red-zone -fno-exceptions
INC			= -I$(TOOLS)/newlib-cygwin/newlib/libc/include -I/usr/lib/gcc/x86_64-linux-gnu/9/include
LDFLAGS = -z norelro --entry main -static -T./ld.scr
LDLIBS	= -L$(TOOLS)/build-newlib -lc

$(TARGET) : $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

$(OBJDIR)/%.o : %.c
	mkdir $(OBJDIR) -p
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJDIR)/%.o : xhci/%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJDIR)/%.o : %.asm
	$(NASM) -f elf64 -o $@ $<

$(OBJDIR)/%.o : %.bin
	$(OBJCOPY) -I binary -O elf64-x86-64 -B i386:x86-64 $< $@

%.bin :
	cp $(SRC)/resources/fonts/hankaku16.bin hankaku16.bin

.PHONY : all
all : $(TARGET)

.PHONY : clean
clean :
	rm $(OBJDIR)/ -rf
	rm *.elf