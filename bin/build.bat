@echo off

:: create target directory if it doesnt exist
IF NOT EXIST W:\build mkdir w:\build
pushd w:\build

:: setup flags for cl.exe
set CompileFlags=/I"W:\deps\include" /O2 /Zi /LD /EHsc /DSDL_EXPORT

set LinkFlags=w:\deps\lib\x86\SDL2.lib w:\deps\lib\x86\SDL2main.lib 

set Files=w:\code\sdl.cpp

cl %CompileFlags% %Files% /link %LinkFlags%

popd