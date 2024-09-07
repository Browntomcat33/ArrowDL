@echo off
:: Copyright 2019-present Sébastien Vavassori. All rights reserved.
:: Use of this source code is governed by a LGPL license that can be
:: found in the LICENSE file.

SET PATH=C:\Windows\System32;%PATH%

:: Remove the final backslash with the ":n,m" substring syntax, here ":~0,-1"
SET currentPath=%~dp0
SET INSTALL_PATH=%currentPath:~0,-1%

:: For some reasons, the '-quiet' parsing must be done after the 'Set INSTALL_DIR', otherwise it's not set correctly.
SET QUIET=0
:loop
IF NOT "%1"=="" (
    IF "%1"=="-quiet" (
        SET QUIET=1
        SHIFT
    )
    SHIFT
    GOTO :loop
)

ECHO *************************************************
ECHO                      ArrowDL
ECHO *************************************************
ECHO.
ECHO Install to: %INSTALL_PATH%
ECHO.

ECHO.
ECHO Writting to Chrome Registry...
ECHO ---------------------------------
ECHO Key: HKCU\Software\Google\Chrome\NativeMessagingHosts\com.arrowdl.extension
REG ADD "HKCU\Software\Google\Chrome\NativeMessagingHosts\com.arrowdl.extension" /ve /t REG_SZ /d "%INSTALL_PATH%\launcher-manifest-chrome.json" /f

ECHO. 
ECHO Writting to Firefox Registry...
ECHO ---------------------------------
ECHO Key: HKCU\SOFTWARE\Mozilla\NativeMessagingHosts\com.arrowdl.extension
REG ADD "HKCU\SOFTWARE\Mozilla\NativeMessagingHosts\com.arrowdl.extension" /ve /t REG_SZ /d "%INSTALL_PATH%\launcher-manifest-firefox.json" /f

ECHO. 
ECHO Writting to Edge Registry...
ECHO ---------------------------------
ECHO Key: HKCU\Software\Microsoft\Edge\NativeMessagingHosts\com.arrowdl.extension
REG ADD "HKCU\Software\Microsoft\Edge\NativeMessagingHosts\com.arrowdl.extension" /ve /t REG_SZ /d "%INSTALL_PATH%\launcher-manifest-edge.json" /f

ECHO.
ECHO Writting to Waterfox Registry...
ECHO ---------------------------------
ECHO Key: HKCU\SOFTWARE\Mozilla\NativeMessagingHosts\com.arrowdl.extension
REG ADD "HKCU\SOFTWARE\Waterfox\NativeMessagingHosts\com.arrowdl.extension" /ve /t REG_SZ /d "%INSTALL_PATH%\launcher-manifest-firefox.json" /f

ECHO.
ECHO Writting to Thunderbird Registry...
ECHO ---------------------------------
ECHO Key: HKCU\SOFTWARE\Mozilla\NativeMessagingHosts\com.arrowdl.extension
REG ADD "HKCU\SOFTWARE\Thunderbird\NativeMessagingHosts\com.arrowdl.extension" /ve /t REG_SZ /d "%INSTALL_PATH%\launcher-manifest-firefox.json" /f

ECHO.
ECHO ^>^>^> Done! ^<^<^<
ECHO.

IF NOT "%QUIET%"=="1" (
    TIMEOUT /T 10
)
