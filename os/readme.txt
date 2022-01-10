booting programs

On mac os 10.12 I'm using a version of qemu that was released about a year after the os was released.
Had to compile it.  Path doesn't seem to work on the binaries.  They need to access bios files that 
are contained within the repo itself.  The program doesn't seem to be able to find them if I use path.
I'm using qemu-system-i386 

qemu 2.9.1
https://github.com/qemu/qemu/tree/359c41abe32638adad503e386969fa428cecff52

build with 
    ./configure
    make 



https://www.youtube.com/watch?v=5FnrtmJXsdM&list=PLT7NbkyNWaqajsw8Xh7SP9KJwjfpP8TNX&index=1


Modified qemu so it doesn't ask for confirmation on exit by replacing the verifyQuit function with this version

- (BOOL)verifyQuit
{
    return YES;
}

