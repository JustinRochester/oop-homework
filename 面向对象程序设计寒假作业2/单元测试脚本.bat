@echo off
title ��Ԫ���Խű�
cd testing\

:start
cls
set line=-------------------------------

::����

echo �ɹ����Եĵ�Ԫ�У�

type _index
echo.
echo %line%
echo.
echo ��ѡ�����Բ��Ե����ݵ����ƣ�
set /p name=

::�˲����ݵ���Ϣ
if not exist testing_data\%name%.in (
	echo ���ݵ㲻���ڻ�ʧ
	pause>nul
	goto back
)
if not exist testing_data\%name%.ans (
	echo ���ݵ㲻���ڻ�ʧ
	pause>nul
	goto back
)
if not exist testing_program\%name%.exe (
	echo ���򲻴��ڻ�ʧ
	pause>nul
	goto back
)

::����ģʽ
echo ����Сд"h"�����ֶ����ԣ��������������Զ�����
set /p mode=
if %mode% equ h goto hand

::��������
copy testing_data\%name%.in data.in>nul
copy testing_data\%name%.ans data.ans>nul
copy testing_program\%name%.exe prog.exe>nul

::ִ������
prog.exe<data.in>data.out

::�ȶԽ�����ж�
echo.
echo %line%
echo.
echo ִ�н��:
fc data.out data.ans>nul
if not errorlevel 1 (echo %name% ����ͨ��) else (
	echo %name% ���Բ�ͨ��
	fc data.out data.ans
)

::��β����
del data.in
del data.out
del data.ans
del prog.exe

::����
:back
echo.
echo %line%
echo.
echo ����Сд��b�����¿�ʼ���������������˳�
set /p key=
if %key% equ b (goto start) else exit

:hand
testing_program\%name%.exe
goto back