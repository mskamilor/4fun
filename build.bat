@echo off
echo Rozpoczeto kompilacje
chcp 1252

set args=%*
set defarg="map.pwn" -; -( -r -d0
set pa2th=..
IF [%1]==[] (
	set args=%defarg%
	echo Nie wykryto zadnych argumentow! uzyto domyslnych %args% 
) else (
	echo Kompilacja argumentami %args% 
)
 
set dateformat=%time:~0,2%:%time:~3,2%:%time:~6,2%

echo /*>> "%pa2th%/gamemodes/source/main/version.inc
echo    Plik skompilowany dn. %date% o godz. %dateformat%>> "%pa2th%/gamemodes/source/main/version.inc
echo */ >> "%pa2th%/gamemodes/source/main/version.inc

echo #if defined build>> "%pa2th%/gamemodes/source/main/version.inc
echo	#undef build>> "%pa2th%/gamemodes/source/main/version.inc
echo	#undef buildtime>> "%pa2th%/gamemodes/source/main/version.inc
echo	#undef builddate>> "%pa2th%/gamemodes/source/main/version.inc
echo	#undef buildauthor>> "%pa2th%/gamemodes/source/main/version.inc
echo	#undef buildarg>> "%pa2th%/gamemodes/source/main/version.inc
echo #endif>> "%pa2th%/gamemodes/source/main/version.inc

echo #define build "1332">> "%pa2th%/gamemodes/source/main/version.inc
echo #define buildtime "%dateformat%">> "%pa2th%/gamemodes/source/main/version.inc
echo #define builddate "%date%">> "%pa2th%/gamemodes/source/main/version.inc
echo #define buildarg "%args%">> "%pa2th%/gamemodes/source/main/version.inc
echo #define buildauthor "Msk.">> "%pa2th%/gamemodes/source/main/version.inc

set start=%time%
"%pa2th%/pawno/pawncc.exe" %args%

set end=%time%
set options="tokens=1-4 delims=:."
for /f %options% %%a in ("%start%") do set start_h=%%a&set /a start_m=100%%b %% 100&set /a start_s=100%%c %% 100&set /a start_ms=100%%d %% 100
for /f %options% %%a in ("%end%") do set end_h=%%a&set /a end_m=100%%b %% 100&set /a end_s=100%%c %% 100&set /a end_ms=100%%d %% 100

set /a hours=%end_h%-%start_h%
set /a mins=%end_m%-%start_m%
set /a secs=%end_s%-%start_s%
set /a ms=%end_ms%-%start_ms%
if %hours% lss 0 set /a hours = 24%hours%
if %mins% lss 0 set /a hours = %hours% - 1 & set /a mins = 60%mins%
if %secs% lss 0 set /a mins = %mins% - 1 & set /a secs = 60%secs%
if %ms% lss 0 set /a secs = %secs% - 1 & set /a ms = 100%ms%
if 1%ms% lss 100 set ms=0%ms%

set /a totalsecs = %hours%*3600 + %mins%*60 + %secs% 

echo #if defined builidingtime>> "%pa2th%/gamemodes/source/main/version.inc
echo #undef builidingtime>> "%pa2th%/gamemodes/source/main/version.inc
echo #endif>> "%pa2th%/gamemodes/source/main/version.inc
echo #define builidingtime "%totalsecs%.%ms%s">> "%pa2th%/gamemodes/source/main/version.inc
echo Kompilacja trwala %totalsecs%.%ms%s

runas /user:# "" >nul 2>&1

endlocal


pause
