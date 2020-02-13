@echo off
title ����ű�

if exist baihua-lang.exe (
	echo ���� baihua-lang.exe �Ѵ���
	pause>nul
	exit
)
if not exist baihua-lang.cpp (
	echo Դ���� baihua-lang.cpp ��ʧ
	pause>nul
	exit
)
if not exist World.h.gch (
	if not exist World.h (
		echo Դ���� World.h ��ʧ
		pause>nul
		exit
		)
	if not exist ErrorRepository.h.gch (
		if exist ErrorRepository.h (g++ ErrorRepository.h) else (
			echo Դ���� ErrorRepository.h ��ʧ
			pause>nul
			exit
		)
	)
	if not exist ValueRepository.h.gch (
		if not exist ValueRepository.h (
			echo Դ���� ValueRepository.h ��ʧ
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
		g++ ValueRepository.h
	)
	g++ World.h
)
g++ -o baihua-lang.exe baihua-lang.cpp
echo �������
pause>nul
