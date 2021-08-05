To change capslock to enter modify /usr/share/X11/xkb/symbols/pc.  God knows why it's called pc but it contains the information for modifier keys mappings.  As you might imagine you change a line that has capslock in it.

    //    key <CAPS> {      [ Caps_Lock             ]       };
        key <CAPS> {        [ Return                ]       };

After this reload the keyboard map with 

    setxkbmap us

There's a premade pc file in this repo if you don't want to do it yourself.


There are many sections in these files.  The top one appears to bethe default so just modify that one I suppose.

To change other keys modify /usr/share/X11/xkb/symbols/us
then again reload it with setxkbmap us


sudo nano /usr/share/X11/xkb/symbols/pc
check settings
setxkbmap -query
set keyboard map to us
setxkbmap us


# mount a device in linux
sudo mount -t ntfs-3g -o ro /dev/nvme0n1p3 /media/windows/



fix linux and windows using different clocks

timedatectl set-local-rtc 1 --adjust-system-clock

Linux will no longer apply timezone adjustments to the clock on your motherboard. As a result, the clocks on your dual boot Windows 10 and Linux set up will be in perfect sync. Before you reboot though you should probably make sure it has worked. Just Enter the command below in the Terminal.

timedatectl

https://mashtips.com/fix-linux-windows-dual-boot-clock-different-time/#:~:text=Method%202%3A%20Make%20Windows%20use%20UTC%20Time&text=For%20this%2C%20go%20to%20Settings,toggle%20under%20Set%20time%20automatically.




# Example of how to compile on windows using visual studio on the command line

Run vcvarsall.bat, wherever the hell it may be in the future, 
then use the compiler cl ... 


call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

cl /nologo /Zi /MD <input files>


@REM source: https://hero.handmade.network/forums/code-discussion/t/2691-day_001_with_visual_studio_2017

@REM Another example from the imgui repository

mkdir Debug
cl /nologo /Zi /MD /I .. /I ..\.. /I "%WindowsSdkDir%Include\um" /I "%WindowsSdkDir%Include\shared" /I "%DXSDK_DIR%Include" /D UNICODE /D _UNICODE *.cpp ..\imgui_impl_win32.cpp ..\imgui_impl_dx10.cpp ..\..\imgui*.cpp /FeDebug/example_win32_directx10.exe /FoDebug/ /link /LIBPATH:"%DXSDK_DIR%/Lib/x86" d3d10.lib d3dcompiler.lib


