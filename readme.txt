Screen
--------------------------------------
Make a new screen with screen. exit using exit. reattach to a screen using screen -r <id>. list the screens with screen -ls 

screen
screen -ls
screen -r <screen id>


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



Awesome ...Stuff
-------------------------------

handmade hero
uwimg
stb
darknet
imgui
nanogui-sdl
wyoos
mkernel
ganga.js
three.js
exfat
fasm - good community
https://github.com/phoboslab/pl_mpeg  mpeg 1 player with audio in sdl and opengl
http://dwm.suckless.org/

fabrice bellard - made FFmpeg, QEMU, and the Tiny C Compiler



Building and Linking C/C++ Repositories
-----------------------------------------------------

Typically, backbone repositories use this method to be built in a unix style system.  

./configure; make; make install

Pkg-config is a convenient tool to get the linker flags that are necessary to link your project with other libraries.
Pkg-config can also output the linker flags necessary to statically link libraries which is awesome (I think with --static)
Example:

pkg-config --libs sdl2 opengl


To link libraries in mac os use the -framework flag

g++ <input.cpp> -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_net -framework SDL2_ttf

To link libraries in linux environments use -l<lib name>  where the library name is the filename without the "lib" prefix 
and without the file extension

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


