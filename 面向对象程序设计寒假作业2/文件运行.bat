@echo off
title 文件运行

:start
cls
set line=-------------------------------
set /p sent=
set prog=%sent:~0,8%
set name=%sent:~9%
echo.
echo %line%
echo.

if %prog% neq main.exe (
	echo 程序不存在
	pause>nul
	exit
)
if not exist main.exe (
	echo.>enter
	call 编译脚本.bat<enter
	del enter
	echo.
	echo %line%
	echo.
)
if not exist %name% (
	echo 文件不存在
	pause>nul
	exit
)
echo 运行结果：
echo.
%prog%<%name%

echo.
echo %line%
echo.

echo 输入小写"b"返回，其它任意字母退出
set /p sent=
if %sent% equ b (goto start) else exit