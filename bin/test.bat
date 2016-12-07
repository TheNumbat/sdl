@echo off

:: create target directory if it doesnt exist
IF NOT EXIST W:\build mkdir w:\build
pushd w:\build

:: setup flags for cl.exe
set CompileFlags=/O2 /Zi /EHsc

set LinkFlags=/SUBSYSTEM:windows /ENTRY:mainCRTStartup w:\build\sdl.lib

set Files=w:\code\test.cpp

cl %CompileFlags% %Files% /link %LinkFlags%

popd