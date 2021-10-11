all:
	fasm a.asm
	qemu-system-i386 -drive format=raw,file=a.bin,if=ide,index=0,media=disk
