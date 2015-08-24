KERNEL = ./kernel/
MBR = ./mbr/
EFLAGS = -hda osome.hdd -monitor stdio
EMU = qemu-system-i386

all: osome.hdd

run: all
	$(EMU) $(EFLAGS)
	
osome.hdd: mbr kernel
	dd if=/dev/zero of=osome.hdd bs=512 count=20000
	dd if=$(MBR)boot.bin of=osome.hdd bs=512 count=1 conv=notrunc
	dd if=$(KERNEL)kernel.bin of=osome.hdd bs=512 seek=1 conv=notrunc

kernel:
	$(MAKE) -C $(KERNEL) kernel.bin

mbr:
	$(MAKE) -C $(MBR) boot.bin

.PHONY: kernel mbr clean osome.hdd
clean:	
	@rm *.hdd
	$(MAKE) -C $(MBR) clean
	$(MAKE) -C $(KERNEL) clean