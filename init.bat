@echo off
echo Compiling the application...c
@REM gcc src/app.c src/service/command.c src/service/sh.c src/client/manage.c -o app

if %errorlevel% neq 0 (
    echo Compilation failed!
    exit /b %errorlevel%
)

echo Compilation successful. Starting the application...
start app
