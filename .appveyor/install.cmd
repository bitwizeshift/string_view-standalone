SETLOCAL EnableDelayedExpansion

echo "Downloading conan..."
set PATH=%PATH%;%PYTHON%/Scripts/
pip.exe install conan
conan user
conan --version