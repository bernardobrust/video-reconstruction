@echo off
setlocal enabledelayedexpansion

:: Usage: build.bat <target> [mode]
:: target: inspector | reconstructor
:: mode:   debug | test | release (default: debug)

:: Note on building: This is just a recreation of the Makefile as a .bat file
:: It's untested and there is no platform layer for windows yet

set TARGET=%~1
set MODE=%~2

if "%TARGET%"=="" (
    echo Error: TARGET must be specified. Valid targets: inspector, reconstructor
    echo Usage: build.bat ^<target^> [mode]
    exit /b 1
)

if "%MODE%"=="" set MODE=debug

set VALID=0
if "%TARGET%"=="inspector" set VALID=1
if "%TARGET%"=="reconstructor" set VALID=1
if %VALID%==0 (
    echo Error: TARGET must be one of: inspector, reconstructor
    exit /b 1
)

set BUILD_DIR=build\%MODE%
set LIB_DIR=lib
set BIN=%BUILD_DIR%\%TARGET%\%TARGET%.exe

if not exist "%BUILD_DIR%\%TARGET%" mkdir "%BUILD_DIR%\%TARGET%"

set CFLAGS=--std=c11 -I%TARGET% -I%LIB_DIR%
set LDFLAGS=
set EXTERNAL_LIBS=-lX11

if "%MODE%"=="debug" (
    set CFLAGS=%CFLAGS% -Wall -Wextra -Werror -ggdb -O0 -fsanitize=address
    set LDFLAGS=%LDFLAGS% -fsanitize=address
) else if "%MODE%"=="test" (
    set CFLAGS=%CFLAGS% -Wall -Wextra -Werror -ggdb -O0 -fsanitize=address
    set LDFLAGS=%LDFLAGS% -fsanitize=address
) else (
    set CFLAGS=%CFLAGS% -Ofast -flto -march=native -DNDEBUG
)

:: Find source files
set SRCS=
if "%MODE%"=="test" (
    for /r %TARGET% %%f in (*.c) do (
        set FILENAME=%%~nf
        if not "!FILENAME!"=="main" (
            set SRCS=!SRCS! "%%f"
        )
    )
) else (
    for /r %TARGET% %%f in (*.c) do (
        set FILENAME=%%~nf
        :: Check if it's NOT a .test.c file
        echo !FILENAME! | findstr /i ".test" >nul
        if errorlevel 1 (
            set SRCS=!SRCS! "%%f"
        )
    )
)

echo Building %TARGET% in %MODE% mode...
echo gcc %CFLAGS% [sources] -o %BIN% %LDFLAGS% %EXTERNAL_LIBS%
gcc %CFLAGS% %SRCS% -o %BIN% %LDFLAGS% %EXTERNAL_LIBS%

if %errorlevel% equ 0 (
    echo Build successful: %BIN%
) else (
    echo Build failed.
    exit /b %errorlevel%
)
