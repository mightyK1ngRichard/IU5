@echo off 

if (%1)==() goto menu 
if NOT (%1)==() goto ter 



:menu 
REM Choose the point of menu. 
echo 1. Rename Information. 
echo 2. Rename all .doc files to .txt. 
echo 3. Rename all .txt files to .doc. 
echo 4. Rename file with the way.   
echo 5. Student Information.  
echo 6. CLS.
echo 7. Exit. 

REM Выбираем пункт меню.
choice /C 1234567
Set met=p%ERRORLEVEL% 
goto %met%

:p1
echo Print information about rename 
rename /? 
pause
goto menu

:p2 
REM Меняем все расширения файлов.
rename *.doc *.txt
pause
goto menu 

:p3
REM Меняем все расширения файлов.
echo %cd%\*.txt
rename *.txt *.doc
pause 
goto menu 

:p4
REM Меняем имя файла по определённому пути.
set /p name=[Input the way with the file's name: ]
set /p nameNew=[Input the new name: ]
rename %name% %nameNew%
pause 
goto menu

:p5 
REM Информация о гение. 
call INFO.bat
goto menu 

:p6 
REM Очищаем консоль.
cls
goto menu

:p7 
REM Quit the command field. 
echo Exit 
exit

:ter 
if exist %1.bat ( 
call %1.bat 
) else ( 
echo The file "%1.bat" doesn't exsist! 
) 
if (%2)==(y) cls
goto menu