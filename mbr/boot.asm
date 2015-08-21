;------------------------------------------
; Constant values
;------------------------------------------
KERNEL_ADD equ 0x1000
CODE_SEGM equ 0x08
DATA_SEGM equ 0x10
STACK_ADD equ 0x90000

;------------------------------------------
[BITS 16]
[ORG 0x7C00]


jmp main

main:
	mov ax, 0x00 ;Clear registers
	mov ds, ax

	;Load kernel into memory
	call load_disk

	;Check for A20 line
	call enable_a20

	jmp enter_protected ;Trigger protected mode

;-------------------------------------------
; Load Kernel via CHS BIOS function
;-------------------------------------------
load_disk:
	mov ah, 0 ;Reset drive
	int 0x13
	or ah, ah
	jnz load_disk

	xor ax, ax
	mov es, ax
	mov bx, KERNEL_ADD ;Kernel destination address

	mov ah, 0x02 ;Read sector
	mov al, 0x12 ;Read 18 sectors
	mov ch, 0x00 ;Cylinder
	mov cl, 0x02 ;Sector
	mov dh, 0x00 ;Head
	int 0x13

	or ah, ah
	jnz load_disk

	ret

;-----------------------------------------------------------------
; Routines to enter 32-bit Protected Mode
;-----------------------------------------------------------------
enter_protected:
	cli ; Disable interupts

	xor ax, ax
	mov ds, ax ; Clear registers

	lgdt [gdt_desc] ; Load GDT descriptor

	; Entering PM
	mov eax, cr0
	or eax, 1
	mov cr0, eax

	; Go to kernel segments
	jmp CODE_SEGM:kernel_segments

;---------------------------------------------
; Standard A320 enable (keyboard method)
;---------------------------------------------
enable_a20:
	cli
	call a20wait
	mov al, 0xad
	out 0x64, al

	call a20wait
	mov al, 0xd0
	out 0x64, al

	call a20wait2
	in al, 0x60
	push eax

	call a20wait
	mov al, 0xd1
	out 0x64, al

	call a20wait
	pop eax
	or al, 2
	out 0x60, al

	call a20wait
	mov al, 0xae
	out 0x64, al

	call a20wait
	sti
	ret
a20wait:
	in al, 0x64
	test al, 2
	jnz a20wait
	ret
a20wait2:
	in al, 0x64
	test al, 1
	jz a20wait2
	ret

;-----------------------------------------------------------
; Code in PM
;-----------------------------------------------------------
[BITS 32]
kernel_segments:
	; Setup data segment
	mov ax, DATA_SEGM
	mov ds, ax
	mov ss, ax

	; Setup stack pointer
	mov esp, STACK_ADD

	; Let's jump into Kernel!
	jmp CODE_SEGM:KERNEL_ADD

;-------------------------------------------
; Global Descriptor Table
;-------------------------------------------
gdt:

gdt_null:
	dd 0
	dd 0

;KERNEL_CODE equ $-gdt
gdt_code: ; Code segment
	dw 0x0ffff
	dw 0
	db 0
	db 10011010b
	db 0xcf
	db 0

;KERNEL_DATA equ $-gdt
gdt_data: ; Data segment
	dw 0x0ffff
	dw 0
	db 0
	db 10010010b
	db 11001111b
	db 0

gtd_interrupts:
	dw 0x0ffff
	dw 0x01000
	db 0
	db 10011110b
	db 11001111b
	db 0

gdt_end:

gdt_desc: ; Descriptor
	dw gdt_end - gdt - 1
	dd gdt

times 510-($-$$) db 0
dw 0xAA55