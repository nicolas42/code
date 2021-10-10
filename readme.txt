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



Using visual studio on the command line
-------------------------------------------------------

Visual studio needs a special script to be run before it can be called from a terminal.
It's called vcvarsall.bat and it moves around every time they release a new version of visual studio.
After it's run the visual studio compiler is available as the "cl" command.
Here are the commands from the last time that I used them.

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

cl /nologo /Zi /MD draw_mandelbrot_in_color.c
del *.pdb *.ilk *.obj 

source https://hero.handmade.network/forums/code-discussion/t/2691-day_001_with_visual_studio_2017

Here's a more complicated example of usage from the imgui repository

mkdir Debug
cl /nologo /Zi /MD /I .. /I ..\.. /I "%WindowsSdkDir%Include\um" /I "%WindowsSdkDir%Include\shared" /I "%DXSDK_DIR%Include" /D UNICODE /D _UNICODE *.cpp ..\imgui_impl_win32.cpp ..\imgui_impl_dx10.cpp ..\..\imgui*.cpp /FeDebug/example_win32_directx10.exe /FoDebug/ /link /LIBPATH:"%DXSDK_DIR%/Lib/x86" d3d10.lib d3dcompiler.lib

How to set path in windows
SET PATH=%PATH%;c:\nick\sdl_cross_platform\lib_win64


Awesome Stuff
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



Building and linking
-----------------------------------------------------

./configure; make; make install

After building and installing software, the linker flags can often be found using
pkg-config

e.g.
pkg-config --libs sdl2 opengl


macos
g++ <input.cpp> -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_net -framework SDL2_ttf

Linux
g++ <input.cpp> -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_net -lSDL2_ttf




Linux Packages
--------------------------------------------------

sudo apt install nasm qemu-system-x86 xorriso pkg-config emacs

sudo apt install libsdl2-dev libsdl2-gfx-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-net-dev libsdl2-ttf-dev
sudo apt install libopengl-dev libglew-dev
# sudo apt install libssl-dev
