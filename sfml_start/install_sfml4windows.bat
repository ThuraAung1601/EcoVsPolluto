@echo off
set SFML_VERSION=2.6.1
set SFML_INSTALL_PATH=C:\SFML

echo Installing SFML...

:: Download SFML
curl -o sfml.zip -L https://www.sfml-dev.org/files/SFML-%SFML_VERSION%-windows-gcc-10.3-mingw-64-bit.zip

:: Extract SFML
7z x sfml.zip -o"%SFML_INSTALL_PATH%"

:: Clean up
del sfml.zip

echo SFML installation completed.

echo Setting up environment variables...

:: Set SFML_PATH environment variable
setx SFML_PATH "%SFML_INSTALL_PATH%\SFML-%SFML_VERSION%-windows-gcc-10.3-mingw-64-bit"

:: Update PATH environment variable
setx PATH "%PATH%;%SFML_INSTALL_PATH%\SFML-%SFML_VERSION%-windows-gcc-10.3-mingw-64-bit\bin"

echo Environment variables configured.

echo Installation completed. You may need to restart your command prompt or IDE for changes to take effect.