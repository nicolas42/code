call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

cl /nologo /Zi /MD draw_mandelbrot_in_color.c

del *.pdb *.ilk *.obj 

