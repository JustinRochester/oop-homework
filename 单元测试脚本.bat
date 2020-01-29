@echo off
if not exist baihua-lang.exe (
	g++ baihua-lang.cpp
	ren a.exe baihua-lang.exe
)
copy testing_data\Run.in data.in>nul
copy testing_data\Run.ans data.ans>nul
baihua-lang.exe<data.in>data.out
fc data.out data.ans>nul
if not errorlevel 1 (echo Run 测试通过) else (
	echo Run 测试不通过
	fc data.out data.ans
)
pause>nul
del data.in
del data.out
del data.ans