@echo off
title �ļ�����

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
	echo ���򲻴���
	pause>nul
	exit
)
if not exist main.exe (
	echo.>enter
	call ����ű�.bat<enter
	del enter
	echo.
	echo %line%
	echo.
)
if not exist %name% (
	echo �ļ�������
	pause>nul
	exit
)
echo ���н����
echo.
%prog%<%name%

echo.
echo %line%
echo.

echo ����Сд"b"���أ�����������ĸ�˳�
set /p sent=
if %sent% equ b (goto start) else exit