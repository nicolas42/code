// x86 is little endian.  regular numbers are big endian. MSF comes first

0xAA55 big endian

look in first 512 bytes finds magic numbers at the end
if it's there it tries to boot from the first 512 bytes

// #bytes bs
dd if=/dev/zero of=bootsect.bin bs=512 count=1


xxd make hex dump or reverse

hexl-mode
