:: backup current directory
pushd %CD%

:: set batch file directory as current
cd /d %~dp0%

:: remove generated folders
@RD /S /Q SharpmakeProjects\generated\
@RD /S /Q .build\

Tools\Sharpmake\Sharpmake.Application.exe "/sources('SharpmakeProjects/Main.sharpmake.cs') /verbose"

:: restore current directory
popd

pause
