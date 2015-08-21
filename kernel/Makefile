kernel.bin: ks.o kernel.o
	ld -Ttext 0x1000 -o kernel.bin ks.o kernel.o -m elf_i386 --entry start --oformat binary

ks.o:
	nasm -f aout kernel_start.asm -o ks.o

kernel.o: kernel.c
	gcc -c kernel.c -o kernel.o -m32 -ffreestanding -fno-builtin -nostdlib

.PHONY: clean
clean:
	@rm *.o
	@rm *.bin