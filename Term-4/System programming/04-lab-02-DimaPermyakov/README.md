# Laboratory work №2.

```bat
@echo off 

if (%1)==() goto menu 
if NOT (%1)==() goto ter 



:menu 
REM Choose the point of menu. 
echo 1. Additional task from Aksenova.
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
REM Additional task
dir
if (%old_name%)==() set old_name="file.txt"
echo %old_name%
rename %old_name% %3
set old_name=%3
shift /3
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
```

## Additional task:
Request example: ```lab02.bat INFO y name1.txt name2.doc name3.siu siuuuuu.docx```
```bat
...
:p8
REM Additional task
dir
if (%old_name%)==() set old_name="file.txt"
echo %old_name%
rename %old_name% %3
set old_name=%3
shift /3
goto menu
```