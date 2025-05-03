# 🔐 PassGen++ - Secure Password Generator

**Version**: 1.0.4

**Author**: Joa98

<img src="img/img-01" align="center"/>

PassGen++ is a random password generator application designed for simplicity and security.
The app:

- Generates strong password locally
- Never stores passwprds or user data
- Operates entirely offline for maximum privacy
- Provides secure, self-contained environment

## 🚀 Features

- Adjustable password length (4-16 characters)
- Randoms character generation including:
    - Uppercase (A-Z)
    - Lowercase (a-z)
    - Numbers (0-9)
    - Symbols (!@#$%^&*)

- One-click copy to clipboard
- **Visual feedback**: strength color indicator
- **Lightwight**: No internet connection required

## Requirements

-wxWidgets 3.2+
-C++17 compiler
-Linux/Windows/macOS

### 🐧 Linux (Ubuntu)
```
sudo apt install libwxgtk3.2-dev g++ make
git clone https://github.com/Joa98Dev/passgen-.git
cd PassGen
make
```

### 🐧 Linux (Arch)

```
# 1. Install dependencies (wxGTK3 and build tools)
sudo pacman -S wxgtk3 gcc make git

# 2. Clone repository
git clone https://github.com/Joa98Dev/passgen-.git
cd PassGen

# 3. Build (using make or directly with g++)
make

# OR if you want to direct compile it:
g++ main.cpp ui.cpp -o passgen `wx-config --cxxflags --libs`

# 4. Run
./passgen
```

### 🪟 Windows (MinGW)
```
# 1. Install Chocolatey (Windows package manager)
Set-ExecutionPolicy Bypass -Scope Process -Force
[System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072
iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))

# 2. Install dependencies and build tool
choco install -y mingw make git wxwidgets

# 3. Clone repository
choco install -y mingw make git wxwidgets
cd PassGen

# 4. Build the application
# First create a MinGW-compatible Makefile (save as 'Makefile.win')
echo @echo off > Makefile.win
echo g++ -I"C:\wxWidgets-3.2.0\include" -L"C:\wxWidgets-3.2.0\lib\gcc_dll" src\main.cpp src\ui.cpp -o passgen.exe -lwxmsw32u_core -lwxbase32u >> Makefile.win

# Then build
make -f Makefile.win

# OR direct compiling
g++ -I"C:\wxWidgets-3.2.0\include" -L"C:\wxWidgets-3.2.0\lib\gcc_dll" src\main.cpp src\ui.cpp -o passgen.exe -lwxmsw32u_core -lwxbase32u

# 5. Run the application
.\passgen.exe

```

### ⌨️ How to use it?

1. Open the PassGen++ Application
2. Use the slider to set the length of the password (The app will show you a visual feedback of how strong is the password)
3. Click on the **Generate passoword** button.
4. You can copy the password to your system clipboard using the **Copy** button.

### 📜 License

This project is licensed under **GPL-3.0**

Feel free to fork the code, clone this repository and make changes.

Enjoy your coding time! ☕⌨️
