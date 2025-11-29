@echo off
chcp 65001 >nul
setlocal

echo ================================
echo   Frames 폴더 PNG 삭제 도구
echo ================================
echo.

if not exist "Frames" (
    echo [ERROR] Frames 폴더가 존재하지 않습니다.
    echo.
    pause
    exit /b
)

echo Frames 폴더 : %CD%\Frames
echo 안의 PNG 파일을 모두 삭제합니다.
echo.

set /p CONFIRM=정말 삭제할까요? (Y/N): 

if /I "%CONFIRM%"=="Y" (
    del /q "Frames\*.png"
    echo.
    echo 삭제 완료!
) else (
    echo.
    echo 삭제 취소됨.
)

echo.
pause
