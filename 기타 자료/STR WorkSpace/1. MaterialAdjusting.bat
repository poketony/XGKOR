@echo off
chcp 65001 >nul
setlocal enabledelayedexpansion

echo ===============================
echo  [1] MaterialAdjusting.bat
echo  - AVI 프레임 추출
echo  - WAV 길이 조정(선택)
echo ===============================
echo.

REM 1) AVI 파일 찾기 (이 폴더에 1개 있다고 가정)
set "AVI="
for %%F in ("*.avi") do (
    set "AVI=%%~nxF"
    goto :FOUND_AVI
)

echo [ERROR] 이 폴더에서 .avi 파일을 찾을 수 없습니다.
goto :END

:FOUND_AVI
echo 사용 AVI 파일: %AVI%

REM 2) WAV 파일 찾기 (이 폴더에 1개 있다고 가정)
set "WAV="
set "WAVBASE="
for %%F in ("*.wav") do (
    set "WAV=%%~nxF"
    set "WAVBASE=%%~nF"
    goto :FOUND_WAV
)

echo [ERROR] 이 폴더에서 .wav 파일을 찾을 수 없습니다.
goto :END

:FOUND_WAV
echo 사용 WAV 파일: %WAV%

echo.
echo [단계 1] AVI -> PNG 프레임 추출

REM Frames 폴더 생성
if not exist "Frames" (
    mkdir "Frames"
)

echo ffmpeg -y -i "%AVI%" -pix_fmt rgb24 "Frames\frame_%%05d.png"
ffmpeg -y -i "%AVI%" -pix_fmt rgb24 "Frames\frame_%%05d.png"

echo.
echo [단계 2] WAV 길이 조정 (선택)

echo 현재 WAV: %WAV%
echo WAV의 목표 길이(초)를 입력하세요. (예: 298.56)
echo 모르면 그냥 Enter 눌러서 생략해도 됩니다.
set "DUR="
set /p DUR=길이(초): 

if "%DUR%"=="" (
    echo 길이 조정 없이 원본 WAV를 그대로 사용합니다.
) else (
    echo.
    echo ffmpeg -y -i "%WAV%" -ar 37800 -ac 2 -af "apad,atrim=end=%DUR%" "%WAVBASE%_fixed.wav"
    ffmpeg -y -i "%WAV%" -ar 37800 -ac 2 -af "apad,atrim=end=%DUR%" "%WAVBASE%_fixed.wav"

    if exist "%WAVBASE%_fixed.wav" (
        echo 길이 조정된 WAV 생성 완료: %WAVBASE%_fixed.wav
    ) else (
        echo [WARN] 길이 조정 WAV 생성에 실패했습니다. 원본 WAV를 그대로 사용하게 될 수 있습니다.
    )
)

:END
echo.
echo 작업 종료. 계속하려면 아무 키나 누르세요...
pause >nul
endlocal
