@REM @echo off

@REM usage example: 
@REM make.bat lazyfoo_examples.cpp
@REM output goes in win64 directory

IF "%vcvarsall_has_been_run%"=="" (
    SET vcvarsall_has_been_run=1
    call "c:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
)

@REM FOR %%F IN ("show_mandelbrot.cpp") DO %%F 

cl /Zi /I "win64\include\SDL2" show_mandelbrot.cpp /link "win64\SDL2.lib" "win64\SDL2main.lib" "win64\SDL2_image.lib" "win64\SDL2_mixer.lib" "win64\SDL2_ttf.lib" "kernel32.lib" "user32.lib" "shell32.lib" /SUBSYSTEM:WINDOWS /OUT:"win64\show_mandelbrot.cpp.exe"

del *.manifest *.ilk *.obj *.pdf *.idb *.pdb 
del win64\*.manifest win64\*.ilk win64\*.obj win64\*.pdf win64\*.idb win64\*.pdb



