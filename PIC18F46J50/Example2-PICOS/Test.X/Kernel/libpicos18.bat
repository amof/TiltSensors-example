echo
REM  ______________________________________________________________________
REM >                                                                      <
REM >                         PICos18 release 3.00                         <
REM >                                                                      <
REM >             PICos18 - Real-time kernel for PIC18 family              <
REM >                                                                      <
REM >                                                                      <
REM > www.picos18.org                                    www.pragmatec.net <
REM >______________________________________________________________________<

//@echo off 
cls 

REM -- point to the source of the kernel 
set PATHTOKERNEL=E:\Julien\Downloads\PICos18_v3_00

REM -- the automatic variant 
REM cd .. 
REM set PATHTOKERNEL=%cd% 
REM cd Kernel 

REM -- what pic18 chip are you using 
set CHIP=18F46J50

if not exist %PATHTOKERNEL% goto _invalid_path 

REM ------------------------------------------------------------- 
REM ------------------------------------------------------------- 
REM -------------------------------------------------------------  

set MCC18=E:\mplabc18\v3.47
set CFLAGS=-O- -ls

REM -- do not edit this

echo Trying to build the PICos18 kernel library 
echo ... 

IF EXIST %PATHTOKERNEL%\Kernel\picos18.lib del %PATHTOKERNEL%\Kernel\picos18.lib 
%MCC18%\bin\mplib.exe /c %PATHTOKERNEL%\Kernel\picos18.lib 

echo 1...

for %%f in (%PATHTOKERNEL%\Kernel\*.o) do del %%f 
for %%f in (%PATHTOKERNEL%\Kernel\*.err) do del %%f 
for %%f in (%PATHTOKERNEL%\Kernel\*.lst) do del %%f 
for %%f in (%PATHTOKERNEL%\Kernel\*.i) do del %%f 
for %%i in (%PATHTOKERNEL%\Kernel\*.asm) do %MCC18%\mpasm\mpasmwin.exe /rDEC /l- /o /q /d__LARGE__  /p%CHIP% %%i 
for %%i in (%PATHTOKERNEL%\Kernel\*.c) do %MCC18%\bin\mcc18.exe %CFLAGS%  /i"%MCC18%\h" /i"%PATHTOKERNEL%\Include" -p%CHIP% %%i 

echo 2...

del PICos18.o 
del PICos18i.o 
del PICos18iz.o 
for %%i in (%PATHTOKERNEL%\Kernel\*.o) do %MCC18%\bin\mplib.exe /r %PATHTOKERNEL%\Kernel\picos18.lib %%i 
REM %MCC18%\bin\mplib.exe /r %PATHTOKERNEL%\Kernel\picos18.lib kernel.O 

echo 3...

%MCC18%\bin\mcc18.exe %CFLAGS% /i"%MCC18%\h" /i"%PATHTOKERNEL%\Include" -p%CHIP% %PATHTOKERNEL%\Kernel\PICos18.c 
%MCC18%\bin\mcc18.exe %CFLAGS% /i"%MCC18%\h" /i"%PATHTOKERNEL%\Include" -p%CHIP% %PATHTOKERNEL%\Kernel\PICos18i.c 
%MCC18%\bin\mcc18.exe %CFLAGS% /i"%MCC18%\h" /i"%PATHTOKERNEL%\Include" -p%CHIP% %PATHTOKERNEL%\Kernel\PICos18iz.c 


echo ================================================== 
echo           PICos18 Library has been rebuilt    
echo ================================================== 
dir %PATHTOKERNEL%\Kernel\*.lib 

goto _end 

:_invalid_path 

echo ERROR: Path PATHTOKERNEL does not exists: %PATHTOKERNEL%. 
goto _end 

:_no_chip_set 

echo ERROR: Variable CHIP has not been set. 
goto _end 

:_end 
pause
