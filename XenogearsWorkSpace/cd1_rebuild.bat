@echo off

REM 현재 위치 저장
set ORIG_DIR=%cd%

REM 파일 이동
move "%ORIG_DIR%\0022.rootexecd1" "%ORIG_DIR%\STRIPCD1(KOR)\"

REM ===== 여기서 작업 수행 =====
REM 예: 프로그램 실행
xenoiso cd1list.txt -d

REM ============================

REM 작업 끝나면 파일 다시 원위치로
move "%ORIG_DIR%\STRIPCD1(KOR)\0022.rootexecd1" "%ORIG_DIR%\"

REM 원래 위치로 복귀
cd /d "%ORIG_DIR%"

echo DISC 1 builded
pause
