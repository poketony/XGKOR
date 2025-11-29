@echo off
chcp 65001 >nul
setlocal

echo ===============================
echo  FixAudioLength.bat
echo  - jPSXdec 에러에 맞춰
echo    WAV 길이를 샘플 단위로 보정
echo ===============================
echo.

REM 1) 대상 WAV 파일 이름 입력
set "WAV="
set /p WAV=길이를 보정할 WAV 파일 이름(예: Movie_5_JPN.wav): 

if "%WAV%"=="" (
    echo [ERROR] WAV 파일 이름을 입력해야 합니다.
    goto :END
)

if not exist "%WAV%" (
    echo [ERROR] "%WAV%" 파일을 찾을 수 없습니다.
    goto :END
)

REM 2) jPSXdec 에러 메시지에서 읽은 existing sample length 입력
echo.
echo jPSXdec 에러 로그에서
echo   "existing sample length N"
echo 의 N 값을 그대로 입력하세요.
echo 예: 1,554,336 또는 1554336
echo.

set "EXIST_RAW="
set /p EXIST_RAW=existing sample length 값: 

if "%EXIST_RAW%"=="" (
    echo [ERROR] 값을 입력하지 않았습니다.
    goto :END
)

REM 3) 콤마 제거해서 순수 숫자만 남기기
set "EXIST=%EXIST_RAW:,=%"

REM 4) 베이스 이름 추출
for %%F in ("%WAV%") do set "BASE=%%~nF"

echo.
echo ffmpeg로 샘플 길이 %EXIST% 에 맞춰 WAV 생성 중...
echo ffmpeg -y -i "%WAV%" -ar 37800 -ac 2 -af "apad,atrim=end_sample=%EXIST%" "%BASE%_fixed.wav"
ffmpeg -y -i "%WAV%" -ar 37800 -ac 2 -af "apad,atrim=end_sample=%EXIST%" "%BASE%_fixed.wav"

if exist "%BASE%_fixed.wav" (
    echo.
    echo [OK] 생성 완료: %BASE%_fixed.wav
    echo     ApplyingMaterial.bat을 다시 실행하면
    echo     이 파일이 우선적으로 사용됩니다.
) else (
    echo.
    echo [ERROR] %BASE%_fixed.wav 파일이 생성되지 않았습니다.
    echo ffmpeg 출력 메시지를 확인해 주세요.
)

:END
echo.
echo 종료. 아무 키나 누르세요...
pause >nul
endlocal
