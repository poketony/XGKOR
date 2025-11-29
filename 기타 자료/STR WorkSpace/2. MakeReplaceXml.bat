@echo off
chcp 65001 >nul
setlocal enabledelayedexpansion

echo ===============================
echo  [2] MakeReplaceXml.bat
echo  - Frames 폴더의 PNG로
echo  - replace.xml 생성
echo ===============================
echo.

REM 1) Frames 폴더 존재 확인
if not exist "Frames" (
    echo [ERROR] Frames 폴더가 없습니다.
    echo 먼저 MaterialAdjusting.bat으로 프레임을 추출하세요.
    goto :END
)

REM 2) Frames 안에 PNG가 있는지 확인
set "HASPNG="

for %%F in (Frames\*.png) do (
    set "HASPNG=1"
    goto :HAVEPNG
)

:HAVEPNG
if not defined HASPNG (
    echo [ERROR] Frames 폴더 안에 .png 프레임이 없습니다.
    goto :END
)

REM 3) replace.xml 새로 만들기 (기존 파일은 덮어씀)
echo replace.xml 생성 중...

> "replace.xml" echo ^<?xml version="1.0"?^>
>>"replace.xml" echo ^<str-replace version="0.3"^>

set /a IDX=0

for %%F in (Frames\*.png) do (
    REM 예: <replace frame="0">Frames/frame_00001.png</replace>
    >>"replace.xml" echo ^    ^<replace frame="!IDX!"^>Frames/%%~nxF^</replace^>
    set /a IDX+=1
)

>>"replace.xml" echo ^</str-replace^>

echo 완료: replace.xml
echo.

:END
echo 작업 종료. 계속하려면 아무 키나 누르세요...
pause >nul
endlocal
