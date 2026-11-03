# Static C++ Web App (Wt) – Portfolio Landing Page
Author: Pratiksha Bhende (github.com/pratiksha0604)

## Structure
```
wt-portfolio-static/
├── CMakeLists.txt
├── vcpkg.json
├── src/main.cpp          <- Wt server + "/" route
└── static/               <- docroot (Day 22 landing page)
    ├── index.html
    ├── css/style.css
    └── js/main.js
```

## Windows (VS Code + vcpkg + CMake)
1. Install: Visual Studio Build Tools (C++), CMake, Git, VS Code extensions "C/C++" and "CMake Tools".
2. Install vcpkg:
   ```
   git clone https://github.com/microsoft/vcpkg C:\vcpkg
   C:\vcpkg\bootstrap-vcpkg.bat
   ```
3. Configure and build (first build of Wt takes a while):
   ```
   cd wt-portfolio-static
   cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
   cmake --build build --config Release
   ```
4. Run from the PROJECT ROOT (so `static/` is found):
   ```
   build\Release\portfolio_server.exe
   ```
   or explicitly:
   ```
   build\Release\portfolio_server.exe --docroot static --http-address 0.0.0.0 --http-port 8080
   ```
5. Open http://localhost:8080 in the browser.

## Linux / WSL alternative
```
sudo apt install build-essential cmake witty-dev
cmake -B build -S . && cmake --build build
./build/portfolio_server
```

## How it works
- Step 2: `--docroot static` makes Wt serve `/css/style.css`, `/js/main.js`, etc. directly from `static/`.
- Step 4: `IndexResource` is registered at `/` and returns `static/index.html`.
