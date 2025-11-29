@echo off
chcp 65001 >nul

REM ========== 경로 설정 ==========
REM jpsxdec.jar 경로
set "JPSXDEC=C:\Users\JO\Desktop\XENO_ARC\Tool\jpsxdec_v2.0\jpsxdec.jar"

REM Xenogears .idx 경로
set "IDX=C:\Users\JO\Desktop\XENO_ARC\Xenogears\XenogearsUSACD1.idx"
REM ===============================

echo ===============================
echo  3. ApplyingMaterial.bat
echo  - 오디오 적용 -> 비디오 적용
echo ===============================
echo.

REM ---------- 1) 오디오 교체 ----------
echo [오디오] 교체할 WAV 파일 이름을 입력하세요.
echo 예) Movie_5_JPN_fixed.wav  또는  Movie_5_JPN.wav
set "WAV="
set /p WAV=WAV 파일 이름 (엔터 = 오디오 교체 건너뛰기): 

if "%WAV%"=="" goto SKIP_AUDIO

if not exist "%WAV%" (
    echo [ERROR] "%WAV%" 파일을 찾을 수 없습니다.
    goto SKIP_AUDIO
)

echo.
echo [오디오] STR 아이템 리스트 번호를 입력하세요. (예: 11)
set "AUD="
set /p AUD=오디오 ID (엔터 = 오디오 교체 건너뛰기): 

if "%AUD%"=="" goto SKIP_AUDIO

echo.
echo 오디오(ID %AUD%)에 "%WAV%" 적용 중...
java -jar "%JPSXDEC%" -x "%IDX%" -i %AUD% -replaceaudio "%WAV%"

:SKIP_AUDIO
echo.
echo -----------------------------------
echo  오디오 단계 완료 (또는 건너뜀)
echo -----------------------------------
echo.

REM ---------- 2) 비디오 교체 ----------
if not exist "replace.xml" (
    echo [WARN] replace.xml 이 현재 폴더에 없습니다.
    echo        비디오 교체는 건너뜁니다.
    goto END
)

echo [비디오] STR 아이템 리스트 번호를 입력하세요. (예: 26)
set "VID="
set /p VID=비디오 ID (엔터 = 비디오 교체 건너뛰기): 

if "%VID%"=="" goto END

echo.
echo 비디오(ID %VID%)에 replace.xml 적용 중...
java -jar "%JPSXDEC%" -x "%IDX%" -i %VID% -replaceframes "replace.xml"

:END
echo.
echo 작업 종료. 콘솔을 확인한 뒤 아무 키나 누르세요...
pause >nul
exit /b
