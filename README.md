# everything

## SSH Key for github 

    ssh-keygen -t ed25519 -C "your_email@example.com"

    # start the ssh-agent in the background
    eval "$(ssh-agent -s)"

    # Add your SSH private key to the ssh-agent.
    ssh-add ~/.ssh/id_ed25519

Then add the key to github.com in settings > ssh keys

Then clone stuff like this

git clone git@github.com/username:repo




# How to compile on windows using visual studio on the command line

Run vcvarsall.bat, wherever the hell it may be in the future, 
then use the compiler cl ... 


call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

cl /nologo /Zi /MD <input files>


@REM source: https://hero.handmade.network/forums/code-discussion/t/2691-day_001_with_visual_studio_2017

@REM Another example from the imgui repository

mkdir Debug
cl /nologo /Zi /MD /I .. /I ..\.. /I "%WindowsSdkDir%Include\um" /I "%WindowsSdkDir%Include\shared" /I "%DXSDK_DIR%Include" /D UNICODE /D _UNICODE *.cpp ..\imgui_impl_win32.cpp ..\imgui_impl_dx10.cpp ..\..\imgui*.cpp /FeDebug/example_win32_directx10.exe /FoDebug/ /link /LIBPATH:"%DXSDK_DIR%/Lib/x86" d3d10.lib d3dcompiler.lib


