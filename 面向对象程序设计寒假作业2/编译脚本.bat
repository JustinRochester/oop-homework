@echo off
title ����ű�

if exist main.exe (
	echo ���� main.exe �Ѵ���
	pause>nul
	exit
)
if not exist main.cpp (
	echo Դ���� main.cpp ��ʧ
	pause>nul
	exit
)
if not exist World.h.gch (
	if not exist World.h (
		echo Դ���� World.h ��ʧ
		pause>nul
		exit
		)
	if not exist VariableRepository.h.gch (
		if exist VariableRepository.h (g++ VariableRepository.h) else (
			echo Դ���� VariableRepository.h ��ʧ
			pause>nul
			exit
		)
	)
	if not exist NumberRepository.h.gch (
		if exist NumberRepository.h (g++ NumberRepository.h) else (
			echo Դ���� NumberRepository.h ��ʧ
			pause>nul
			exit
		)
	)
	g++ World.h
)
g++ -o main.exe main.cpp
echo �������
pause>nul
