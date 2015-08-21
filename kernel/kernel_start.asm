[BITS 32]
[global start]
[extern k_main]

start:
	call k_main

	cli
	hlt