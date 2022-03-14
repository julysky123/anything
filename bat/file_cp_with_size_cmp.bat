@echo off

:::::::::::::::::::::::::::SET VARIABLE:::::::::::::::::::::::::

set target_path=C:\target_path
set target_files=(file1.txt file2.txt file3.log)
set copy_path=E:\copy_path

set size_pos=4
set no_file=1000000000

:::::::::::::::::::::::::::WORKING PART::::::::::::::::::::::::::

if not exist %copy_path% ( md %copy_path% )
for %%a in %target_files% do set target_file=%%a & call :Loop
exit

:::::::::::::::::::::::::::SUBROUTINE::::::::::::::::::::::::::::

:Loop
if not exist %target_path%\%target_file% ( goto :eof )

set s2=%no_file%

REM size comparison
for /f "tokens=%size_pos% delims= " %%a IN ('dir /-C %%target_path%% ^| findstr %%target_file%%') do set s1=%%a
for /f "tokens=%size_pos% delims= " %%b IN ('dir /-C %%copy_path%% ^| findstr %%target_file%%') do set s2=%%b

if %s1% LSS %s2% ( del %copy_path%\%target_file% )

copy /Y %target_path%\%target_file% %copy_path%\%target_file%
goto :eof

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
