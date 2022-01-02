HTML Forms 
------------------
https://www.w3schools.com/tags/att_form_method.asp


HTML forms make GET and POST requests and send the data in the form as name/value pairs.
The html tags must have name="something"
A server can be made that responds to this information appropriately.
POST requests have no limitations on data length https://www.w3schools.com/tags/ref_httpmethods.asp.



Net Cat (nc)
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




Alert from macos terminal 
--------------------------
(Put this after a long set of commands)

osascript -e 'tell app "System Events" to display dialog "Hello World"'

source: https://stackoverflow.com/questions/5588064/how-do-i-make-a-mac-terminal-pop-up-alert-applescript



Awesome
-------------------------------

How 3D video games do graphics - Jonathan Blow https://youtu.be/bGe-d09Nc_M?t=3600

Mr P Solver https://www.youtube.com/c/MrPSolver/videos
Tired Amateur https://www.youtube.com/channel/UCeT6NdimLKHXlkQgrbcg6XQ
handmade hero
imgui
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
https://github.com/phoboslab/pl_mpeg
http://dwm.suckless.org/
fabrice bellard - made FFmpeg, QEMU, and the Tiny C Compiler
https://github.com/kokke/tiny-AES-c
https://github.com/guzlewski/netcat
http://beej.us/guide/bgnet/html/



jdh - made bootable tetris https://www.youtube.com/channel/UCUzQJ3JBuQ9w-po4TXRJHiA





Resize and center an image
-----------------------------

An image must be scaled by the minimum ratio of the max_width / image_width or the max_height / image_height
to be scaled while maintaining its aspect to fit inside a box

var scaler = Math.min(canvas.width / img.naturalWidth, canvas.height / img.naturalHeight);
img_size = { width: img.naturalWidth*scaler, height: img.naturalHeight*scaler };
offset_y = (canvas.height - img_size.height)/2;
offset_x = (canvas.width - img_size.width)/2;


Javascript Calculator
---------------------------
(function () { Object.getOwnPropertyNames(Math).forEach(function (a) { eval(a + "=" + "Math." + a + "\t") }); })();

This will import the javascript math object into the global namespace


Screen
--------------------------------------
Make a new screen with screen. detatch using ctrl+a d. list the screens with screen -ls. reattach with screen -r <id>. exit using exit.

screen
screen -ls
screen -r <screen id>

Nohup
--------------------------------------
Run background processes in linux with nohup <command> & 
Kill the background process by deleting nohup.out 



Python datetime filenames
------------------------------------

datetime.datetime.now().strftime("%Y%m%d_%H%M%S")


Github SSH Keys
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

git clone git@github.com/username:repo



Compiling Stuff on Windows Using Visual Studio on the command line
-------------------------------------------------------

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



Building and Linking C/C++ Repositories
-----------------------------------------------------

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




Some Linux Packages that I'm using at the moment (Debian)
--------------------------------------------------

sudo apt install nasm qemu-system-x86 xorriso pkg-config emacs

sudo apt install libsdl2-dev libsdl2-gfx-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-net-dev libsdl2-ttf-dev
sudo apt install libopengl-dev libglew-dev
# sudo apt install libssl-dev





------------------------------------------------------------------------------
IDEAS FOR PROJECTS
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
just creates pure html sites from the browser, and saves them in a persistent way.
start from go wiki example 
could use version control like nit version control system that I made 

20100820_<fixed_length_hash>_description


SDL based GUI.  
-------------------------------

buttons
basic text editor
archie quasimode and leap interface :)


Make networked chat program
------------------------------


Basic file sharing program
------------------------------
like https://wormhole.app/


