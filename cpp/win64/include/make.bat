@REM call "c:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

cl /Zi /I "win64\include\SDL2" "%1" /link "win64\SDL2.lib" "win64\SDL2main.lib" "win64\SDL2_image.lib" "win64\SDL2_mixer.lib" "win64\SDL2_ttf.lib" "kernel32.lib" "user32.lib" "shell32.lib" /SUBSYSTEM:WINDOWS /OUT:"win64\%1.exe"
del *.manifest *.ilk *.obj *.pdb *.idb *.pdb 
del win64\*.manifest win64\*.ilk win64\*.obj win64\*.pdb win64\*.idb win64\*.pdb
