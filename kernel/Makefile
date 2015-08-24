CFLAGS = -m32 -ffreestanding -fno-builtin -nostdlib
LFLAGS = -Ttext 0x1000 -o kernel.bin -m elf_i386 --entry start --oformat binary

kernel.bin: ks.o kernel.o
	ld $(LFLAGS) ks.o kernel.o screen.o io.o

ks.o: kernel_start.asm
	nasm -f aout kernel_start.asm -o ks.o

kernel.o: kernel.c logo.h screen.o
	gcc -c $< -o $@  $(CFLAGS)


screen.o: screen.c screen.h io.o
	gcc -c $< -o $@ $(CFLAGS)

io.o: io.c io.h
	gcc -c $< -o $@ $(CFLAGS)

.PHONY: clean
clean:
	@rm *.o
	@rm *.bin