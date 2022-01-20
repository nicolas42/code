# the os currently uses floppy emulation
# when using cylinder drive sector boot as a floppy i.e. if=floppy
# reading disk using the ata requires if=ide



all:
	fasm my_second_boot_loader.asm
	qemu-system-i386 -drive format=raw,file=my_second_boot_loader.bin,if=ide,index=0,media=disk


clean:
	rm *.bin




# all: linux

# macos:
# 	fasm os.asm
# 	/Users/nick/qemu-2.9.1/i386-softmmu/qemu-system-i386 -drive format=raw,file=os.bin,if=ide,index=0,media=disk

# linux:
# 	fasm os.asm
# 	qemu-system-i386 -drive format=raw,file=os.bin,if=ide,index=0,media=disk







# ---------------------------------------------------------------------------------
# QEMU Notes
# -----------------------------------------------------------------------------------
# for more information see
# https://www.qemu.org/docs/master/system/invocation.html

# -drive option[,option[,option[,...]]]
# Define a new drive. This includes creating a block driver node (the backend) as well as a guest device, and is mostly a shortcut for defining the corresponding -blockdev and -device options.

# -drive accepts all options that are accepted by -blockdev. In addition, it knows the following options:

# file=file
# This option defines which disk image (see the Disk Images chapter in the System Emulation Users Guide) to use with this drive. If the filename contains comma, you must double it (for instance, “file=my,,file” to use file “my,file”).

# if=interface
# This option defines on which type on interface the drive is connected. Available types are: ide, scsi, sd, mtd, floppy, pflash, virtio, none.
# bus=bus,unit=unit
# These options define where is connected the drive by defining the bus number and the unit id.
# index=index
# This option defines where is connected the drive by using an index in the list of available connectors of a given interface type.
# media=media
# This option defines the type of the media: disk or cdrom.


# -boot [order=drives][,once=drives][,menu=on|off][,splash=sp_name][,splash-time=sp_time][,reboot-timeout=rb_timeout][,strict=on|off]
# Specify boot order drives as a string of drive letters. Valid drive letters depend on the target architecture. The x86 PC uses: a, b (floppy 1 and 2), c (first hard disk), d (first CD-ROM), n-p (Etherboot from network adapter 1-4), hard disk boot is the default. To apply a particular boot order only on the first startup, specify it via once. Note that the order or once parameter should not be used together with the bootindex property of devices, since the firmware implementations normally do not support both at the same time.

# Interactive boot menus/prompts can be enabled via menu=on as far as firmware/BIOS supports them. The default is non-interactive boot.


# -fda floppy disk a -hda hard disk a  can be b,c,d...
# -boot a,b,c  (disk drive letter)



