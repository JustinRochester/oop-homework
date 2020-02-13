@echo off
title 编译脚本

if exist main.exe (
	echo 程序 main.exe 已存在
	pause>nul
	exit
)
if not exist main.cpp (
	echo 源代码 main.cpp 丢失
	pause>nul
	exit
)
if not exist World.h.gch (
	if not exist World.h (
		echo 源代码 World.h 丢失
		pause>nul
		exit
		)
	if not exist ErrorRepository.h.gch (
		if exist ErrorRepository.h (g++ ErrorRepository.h) else (
			echo 源代码 ErrorRepository.h 丢失
			pause>nul
			exit
		)
	)
	if not exist ValueRepository.h.gch (
		if not exist ValueRepository.h (
			echo 源代码 ValueRepository.h 丢失
			pause>nul
			exit
		)
		if not exist VariableRepository.h.gch (
			if exist VariableRepository.h (g++ VariableRepository.h) else (
				echo 源代码 VariableRepository.h 丢失
				pause>nul
				exit
			)
		)
		if not exist NumberRepository.h.gch (
			if exist NumberRepository.h (g++ NumberRepository.h) else (
				echo 源代码 NumberRepository.h 丢失
				pause>nul
				exit
			)
		)
		g++ ValueRepository.h
	)
	g++ World.h
)
g++ -o main.exe main.cpp
echo 编译完成
pause>nul
