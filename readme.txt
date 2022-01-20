omg an unecessary change

#Emacs
--------------------
in file explorer
   g refreshes page
   d selects files for deletion, 
   x deletes files
   undo deletion marks with the regular undo
   ~ selects ~ files for deletion
   # selects # files for deletion
   
m-x (un)comment-region




What is a "block device"
------------------------------
It appears the main distinction is between a "character device" where a single character can be read
versus a "block device" where only a block of information can be read, comprising multiple bytes,
like a 512 byte sector.
https://unix.stackexchange.com/questions/259193/what-is-a-block-device



------------------------------------------------------------------------------------------------
Beej's Guide to C Programming 
------------------------------------------------------------------------------------------------

from https://beej.us/guide/bgc/html/


7.4 String Initializers
---------------------------------

Importantly, in c, initializing a string as a pointer is interpreted 
as a pointer directly to the string literal.  And string literals apparently are immutable.  
However if the string is declared as an array, char s[] = 'string', then the program includes 
a pointer to a COPY of the string literal which is mutable.  
So basically 

char *s = "immutable"; !!!!!!!!
char s[] = "mutable";

Attempting to change an immutable string will result in the program crashing, which I have done many times.



16.1.1.1 const and Pointers
---------------------------------

Both of these examples result in the content itself being unmodifiable.

    const int *p;  // Can't modify what p points to
    int const *p;  // Can't modify what p points to, just like the previous line

A constant pointer is made like this.

    int *const p;   // We can't modify "p" with pointer arithmetic
    p++;  // Compiler error!

Both 

    const int *const p;  // Can't modify p or *p!

Multiple levels of indirection

    char *const *const p;
    p++;     // Error!
    (*p)++;  // Error!




To Do List  #todo
---------------------------

extend the OS so that it can use more memory.  Perhaps make a kind of malloc.

stripe
implement payment processing system using stripe
https://github.com/stripe-samples/accept-a-payment/tree/main/prebuilt-checkout-page


look at busybox implementations
networking, files, encryption, string operations
try to use their c code

learn about how to use file descriptors
Input-output system calls in C | Create, Open, Close, Read, Write
https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/
https://en.wikipedia.org/wiki/File_descriptor






---------------------------------------------------------------------------------------
System calls and standard libraries
---------------------------------------------------------------------------------------

I think finaly, the key here is just to define the interfaces to the operating system so they can be redefined later

musl libc can't install on macos it only works on linux distros. 
tcc appeared to have a standard library, that worked some of the time?
maybe it was just using the standard one though.

I'm basically just looking for the most basic file IO that can be built upon.


https://suckless.org/
Unix Specification https://pubs.opengroup.org/onlinepubs/7908799/






Plan 9
-------------------------------------------
from https://aiju.de/plan_9/plan9-syscalls
plan 9 was what unix wanted to be.  
it takes the metaphor of devices as being represented as a heirarchical system of files 
to its extreme 
networking is done through a file like interface
proceedures have their own filespace
some of these ideas have been picked up by other systems, like the proc directory 
for proceedure information 
It also had a low number of system calls.


Input-output system calls in C | Create, Open, Close, Read, Write
https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/

https://en.wikipedia.org/wiki/C_POSIX_library
fcnt

https://en.wikipedia.org/wiki/File_descriptor

https://en.wikipedia.org/wiki/Unistd.h
In the C and C++ programming languages, unistd.h is the name of the header file that provides access to the POSIX operating system API. It is defined by the POSIX.1 standard, the base of the Single Unix Specification, and should therefore be available in any POSIX-compliant operating system and compiler. For instance, this includes Unix and Unix-like operating systems, such as GNU variants, distributions of Linux and BSD, and macOS, and compilers such as GCC and LLVM.

On Unix-like systems, the interface defined by unistd.h is typically made up largely of system call wrapper functions such as fork, pipe and I/O primitives (read, write, close, etc.).


Jonathan Blow on how an operating system should work
https://www.youtube.com/watch?v=k0uE_chSnV8
programs are sandboxed by default 
can't look at hte file system 
basic communication mechanism between processes 
processes communicat by direct memory mapping 
map a mutual buffer 
memcpy data into 


standard library in macos?

there's also a libc.a under a gcc subdirectory.
/usr/include/c++/4.2.1/cstdio









Nuklear GUI single header file library
-----------------------------------------------------

Nuklear is a single header library GUI toolkit written in C89 with no dependencies.
https://github.com/Immediate-Mode-UI/Nuklear

The demo section works well but the large example requires glew which I couldn't install.




C Operator Precedence
----------------------------------------------------------------------------------
How am I supposed to remember this?  It's better just to use parentheses.
from https://en.cppreference.com/w/c/language/operator_precedence




Endianness
----------------------------------------------

Pointers point to the first byte. A "type" occupies that byte and the bytes to the right of it.
A byte in little-endian will have the same value whether the type is 8,16,32,or 64 bits long.
A big endian system needs to know the type to write the right value.  

Little endian is the more popular system, except in networking.

https://uynguyen.github.io/2018/04/30/Big-Endian-vs-Little-Endian/
https://stackoverflow.com/questions/57154009/how-do-pointers-reference-multi-byte-variables





# Python
----------------------------------------------

make an executable

    pyinstaller --onefile --hidden-import=configparser script.py

--one-file seems to be slower than not, but it is more convenient

datetime filenames in format 20200101_240000

    datetime.datetime.now().strftime("%Y%m%d_%H%M%S")




GCC parameters 
--------------------------

-Wfatal-errors   stop after the first fatal error
-fsanitize=address -g 
-Wall -Wpedantic 
-fPIC  position independent code 


ar rcs lib.a *.o    combine object files.
usage: gcc main.c lib.a 

Show/hide hidden files in macos #macos
In Finder, open up your Macintosh HD folder. Press Command+Shift+Dot. Your hidden files will become visible. Repeat step 2 to hide them again




Flexbox #web
-----------------------------------------------------------
Flexbox actually lays out elements reasonably on the web.

The flex-grow attribute can be used on child elements
to make them take up the remaining space in a box.

parent { display: flex; flex-direction: column; } 
parent > child { flex-grow: 1; /* default 0 */ }

For all my playing with box-sizing: border-box and the like, I haven't found 
a way to layout html elements in a sane way using CSS.  The only thing that appears 
to work properly is flexbox.  



#CSS link tag  #web
----------------------
I always forget this

<LINK rel="stylesheet" href="../css/reset.css">



HTML element ids automatically become global variables in javascript. !!!!!!!!!!
https://stackoverflow.com/questions/3434278/do-dom-tree-elements-with-ids-become-global-variables




Cryptography  #crypto
-----------------------

RSA (Rivest–Shamir–Adleman) is a public-key cryptosystem that is widely used for secure data transmission. 

Diffie Helman: 
RSA DH is an asymmetric algorithm used to establish a shared secret for a symmetric key algorithm.




Network Socket Programming #sockets
--------------------------------------------

SERVER          CLIENT
socket()        socket()
bind()          
listen()        
accept()   <-   connect()
recv()     <-   send()
send()     ->   recv()
close()    <-   close()

Can both parties be made symmetrical?
Could they both start as clients and then 
if they can't connect to the other then start as a server 
and wait for an incoming connection.




Netcat (nc)  #bash
---------------------
Net cat is a handy utility for tcp and udp stuff.
The examples below were tested on macos 10.12
-l listen -v verbose -u udp

To Do: Make a version of netcat that doesn't care whether it's a client or a server.
The program should start of as a client then if it fails to connect then it becomes a server
and waits for someone else to connect.

1. Chat program

nc -l 127.0.0.1 8888
nc 127.0.0.1 8888


2. port scanner

nc -v <your public IP address> 1-1000


3. HTTP

nc google.com 80
GET / HTTP/1.1

nc www.rssweather.com 80
GET /wx/in/kanpur/wx.php HTTP/1.0
Host: www.rssweather.com



Making a macos .app application
-------------------------------
Create a folder named "YourApplication.app". 
Put your script file directly in this folder.  Its name must be the same name as the application folder 
but without extension. In the case described here the script file must be named "YourApplication".
https://apple.stackexchange.com/questions/224394/how-to-make-a-mac-os-x-app-with-a-shell-script

My script didn't run when it attempted to access terminal input like argc or argv.




#Awesome
-------------------------------

https://github.com/mirror/busybox/

http://underscorejs.org/  seems like a good javascript library

* https://www.lemoda.net/  lots of C and other code

How 3D video games do graphics - Jonathan Blow https://youtu.be/bGe-d09Nc_M?t=3600

Mr P Solver https://www.youtube.com/c/MrPSolver/videos

Tired Amateur https://www.youtube.com/channel/UCeT6NdimLKHXlkQgrbcg6XQ

handmade hero
imgui   Imgui is a small c++ GUI library
stb
darknet
uwimg
nanogui-sdl
wyoos
mkernel
ganga.js
three.js
exfat
fasm - good community

pl_mpeg mpeg1 player in SDL and opengl https://github.com/phoboslab/pl_mpeg

suckless http://dwm.suckless.org/

fabrice bellard - made FFmpeg, QEMU, and the Tiny C Compiler

aes https://github.com/kokke/tiny-AES-c

netcat https://github.com/guzlewski/netcat

beej's guide to network sockets http://beej.us/guide/bgnet/html/

jdh - made bootable tetris https://www.youtube.com/channel/UCUzQJ3JBuQ9w-po4TXRJHiA

single file libraries in C/C++  https://github.com/nothings/single_file_libs




#SQLite 
----------------
omg sqlite https://sqlite.org/ is encapsulated in a single c file.  I love them so much.



#Lorem Ipsum 
----------------------
This is a passage that is commonly used in design so the text itself doesn't distract the user.

"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."

source https://www.lipsum.com/



#Git tricks
-------------------

remove all files from staging area 

    git reset

clone a repo with ssh 

    git clone git@github.com:username/repo




Regular Expressions #regex
----------------------------
abc…	Letters
123…	Digits
\d	Any Digit
\D	Any Non-digit character
.	Any Character
\.	Period
[abc]	Only a, b, or c
[^abc]	Not a, b, nor c
[a-z]	Characters a to z
[0-9]	Numbers 0 to 9
\w	Any Alphanumeric character
\W	Any Non-alphanumeric character
{m}	m Repetitions
{m,n}	m to n Repetitions
*	Zero or more repetitions
+	One or more repetitions
?	Optional character
\s	Any Whitespace
\S	Any Non-whitespace character
^…$	Starts and ends
(…)	Capture Group
(a(bc))	Capture Sub-group
(.*)	Capture all
(abc|def)	Matches abc or def

refer to a match \1 \2...

reference: https://regexone.com/

Greediness: 
Putting ? after a quantifier makes it non-greedy (or lazy?).  This means that 
the subsequent rule takes precedence. For instance

".*?\d*"

The digits (\d*) will take precedence over the lazy wildcard characters (.*?).




HTML Forms  #web
------------------
https://www.w3schools.com/tags/att_form_method.asp


HTML forms make GET and POST requests.  A server can be made to respond appropriately to this information.
The information itself is encoded as name=value pairs that come from the form.

The html tags in the form must have name attribute and value attributes.

The action is just a string.  The server determines how to use it along with the name=value information. 

<form action="/action_page.php" method="get">
  <label for="fname">First name:</label>
  <input type="text" id="fname" name="fname"><br><br>
  <label for="lname">Last name:</label>
  <input type="text" id="lname" name="lname"><br><br>
  <input type="submit" value="Submit">
</form>


POST requests have no limitations on data length https://www.w3schools.com/tags/ref_httpmethods.asp.




Alert from macos terminal 
--------------------------

Put this after a long command to be alerted when it's done.

osascript -e 'tell app "System Events" to display dialog "Hello World"'

source: https://stackoverflow.com/questions/5588064/how-do-i-make-a-mac-terminal-pop-up-alert-applescript



Resize and center an image
-----------------------------

To fit an image box inside another box while maintaining its aspect ratio it can be scaled (multiplied)
by the minimum ratio of the max_width / image_width or the max_height / image_height.

var scaler = Math.min(canvas.width / img.naturalWidth, canvas.height / img.naturalHeight);
img_size = { width: img.naturalWidth*scaler, height: img.naturalHeight*scaler };

offset_y = (canvas.height - img_size.height)/2;
offset_x = (canvas.width - img_size.width)/2;



Javascript Calculator
---------------------------
Used eval.  Time for seppuku.

(function () { Object.getOwnPropertyNames(Math).forEach(function (a) { eval(a + "=" + "Math." + a + "\t") }); })();

This will import the javascript math object into the global namespace


Time a process #bash
-------------------------------
time a process

time ./a.out


Screen  #bash
--------------------------------------
Make a new screen with the command "screen". detatch using ctrl+a d. exit using exit.
list the screens (with their ids) with "screen -ls". reattach with "screen -r <id>". 
a partial id can be used in place of the full id.

screen
screen -ls
screen -r <screen id>


Nohup   #bash
--------------------------------------
Run background processes in linux with nohup <command> & 
Kill the background process by deleting nohup.out 



Make an #SSH key 
--------------------------------------------

To make an SSH Key for github do the following commands.  You can use git bash in windows.

1) create an ssh key
2) start the ssh-agent
3) Add your SSH private key to the ssh-agent.

ssh-keygen -t ed25519
eval "$(ssh-agent -s)"
ssh-add ~/.ssh/id_ed25519

The public key must be given to github.com.  Find the corresponding id_ed25519.pub file
and copy the text into an ssh key in github's settings > ssh keys section.

Repos have to be cloned in this fashion.

git clone git@github.com:username/repo



Compiling Stuff on Windows Using Visual Studio on the command line   #visualstudio 
----------------------------------------------------------------------------------------

Visual studio needs a special script to be run before it can be called from a terminal.
It's called vcvarsall.bat and it moves around every time they release a new version of visual studio.
After it is run the visual studio compiler is available as the "cl" command.
Here are the commands from the last time that I used them.

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

cl /nologo /Zi /MD draw_mandelbrot_in_color.c
del *.pdb *.ilk *.obj 

source https://hero.handmade.network/forums/code-discussion/t/2691-day_001_with_visual_studio_2017

Here's a more complicated example of usage from the imgui repository

mkdir Debug
cl /nologo /Zi /MD /I .. /I ..\.. /I "%WindowsSdkDir%Include\um" /I "%WindowsSdkDir%Include\shared" /I "%DXSDK_DIR%Include" /D UNICODE /D _UNICODE *.cpp ..\imgui_impl_win32.cpp ..\imgui_impl_dx10.cpp ..\..\imgui*.cpp /FeDebug/example_win32_directx10.exe /FoDebug/ /link /LIBPATH:"%DXSDK_DIR%/Lib/x86" d3d10.lib d3dcompiler.lib


How to set PATH variable in windows
-------------------------------------------------------
SET PATH=%PATH%;c:\nick\sdl_cross_platform\lib_win64



Building and Linking C/C++ Repositories   #pkg-config #linking
---------------------------------------------------------------------

Typical unix build

./configure; make; make install

Linking with pkg-config e.g.

pkg-config --libs sdl2 opengl

To link in macos use the -framework flag, e.g.

g++ <input.cpp> -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_net -framework SDL2_ttf

To link libraries in unix use -l<lib name>.  The library name is the filename without its "lib" prefix 
and without the file extension.  

g++ <input.cpp> -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_net -lSDL2_ttf

.a libraries can be produced using the ar tool (archive?).  For some reason its flags don't need a dash.

ar r lib.a 'ls *.o'

Packaging .o files like this lets linking be done by just adding the .a file to the list which simplifies linking.

g++ main.c lib.a

This works with code that I write but for libraries that are designed to be dynamically linked it appears to be more complicated.
I still don't really understand how shared object .so files work.  Maybe they are just used by the operating system to find the different libraries
it needs to link together the program. Dunno.




Linux Packages I was using (Debian)   #linux
---------------------------------------------------------------------------------

sudo apt install nasm qemu-system-x86 xorriso pkg-config emacs

sudo apt install libsdl2-dev libsdl2-gfx-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-net-dev libsdl2-ttf-dev
sudo apt install libopengl-dev libglew-dev
# sudo apt install libssl-dev






------------------------------------------------------------------------------
#IDEAS FOR PROJECTS
------------------------------------------------------------------------------


file system
-----------------------------------------
* use a single file 1gb
* use fseek    int fseek(FILE *stream, long int offset, int whence)
* flat file system 
* search function

u64 file_offset u64 file_length u64 filename_length filename

offsets and lengths are all in bytes


html wiki  
--------------------------------
[x]     just creates pure html sites from the browser, and saves them in a persistent way.  
        start from go wiki example 

[ ]     could use version control like nit version control system that I made 
        20100820_<fixed_length_hash>_description


SDL based GUI.  
-------------------------------

buttons
basic text editor
archie quasimode and leap interface :)


Make networked chat program
------------------------------

[x]     The netcat program that I found basically does this.  
        But I haven't tested this over the internet.


Basic file sharing program
------------------------------
like https://wormhole.app/


