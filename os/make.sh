files=$(echo "1_boot.asm 2_print_a_character.asm 3_print_a_string.asm")
for file in $files; do fasm $file; done

qemu(){
    /Users/nick/qemu-2.9.1/i386-softmmu/qemu-system-i386 -drive format=raw,file=$1,if=ide,index=0,media=disk
}
