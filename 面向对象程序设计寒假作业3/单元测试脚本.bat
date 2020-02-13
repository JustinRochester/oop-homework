@echo off
title 单元测试脚本
cd testing\

:start
cls
set line=-------------------------------

::编译

echo 可供测试的单元有：

type _index
echo.
echo %line%
echo.
echo 请选择用以测试的数据点名称：
set /p name=

::核查数据点信息
if not exist testing_data\%name%.in (
	echo 数据点不存在或丢失
	pause>nul
	goto back
)
if not exist testing_data\%name%.ans (
	echo 数据点不存在或丢失
	pause>nul
	goto back
)
if not exist testing_program\%name%.exe (
	echo 程序不存在或丢失
	pause>nul
	goto back
)

::测试模式
echo 输入小写"h"进行手动测试，任意其它按键自动测试
set /p mode=
if %mode% equ h goto hand

::拷贝数据
copy testing_data\%name%.in data.in>nul
copy testing_data\%name%.ans data.ans>nul
copy testing_program\%name%.exe prog.exe>nul

::执行数据
prog.exe<data.in>data.out

::比对结果并判定
echo.
echo %line%
echo.
echo 执行结果:
fc data.out data.ans>nul
if not errorlevel 1 (echo %name% 测试通过) else (
	echo %name% 测试不通过
	fc data.out data.ans
)

::收尾处理
del data.in
del data.out
del data.ans
del prog.exe

::回溯
:back
echo.
echo %line%
echo.
echo 输入小写“b”重新开始，任意其他内容退出
set /p key=
if %key% equ b (goto start) else exit

:hand
testing_program\%name%.exe
goto back