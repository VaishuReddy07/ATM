# AGENTS.md

## Project Overview
- **Language:** C++20
- **Build System:** CMake (configured for Ninja)
- **IDE:** JetBrains CLion (auto-generates build/debug configuration)
- **Main Executable:** `untitled`

## Key Files & Structure
- `main.cpp`: Entry point and only source file. All logic currently resides here.
- `CMakeLists.txt`: Minimal CMake configuration. Sets C++ standard and defines the executable target.
- `cmake-build-debug/`: CLion-managed build output directory. Contains Ninja build files, CMake cache, and the compiled executable (`untitled.exe`).

## Build & Run Workflow
- **Build:**
  - Run from CLion IDE (preferred): Use the IDE's build/run buttons.
  - Or from terminal (in project root):
    ```powershell
    cmake -S . -B cmake-build-debug -G Ninja
    cmake --build cmake-build-debug
    ```
- **Run:**
  - From CLion: Use the Run/Debug buttons.
  - From terminal:
    ```powershell
    .\cmake-build-debug\untitled.exe
    ```

## Debugging
- Use CLion's built-in debugger. Breakpoints and step-through are supported out of the box.
- No custom debug scripts or launch configurations are present.

## Testing
- No automated tests or test frameworks are configured.
- `Testing/Temporary/LastTest.log` is present but empty; likely a placeholder from CMake/CLion.

## Patterns & Conventions
- No custom project conventions or patterns are established yet.
- All code is in a single file; refactor as the project grows.
- CMake is set to require C++20 (`set(CMAKE_CXX_STANDARD 20)`).

## External Dependencies
- No external libraries or dependencies are used.
- Toolchain: MinGW (as configured by CLion), Ninja for builds.

## Recommendations for AI Agents
- When adding new features, create new `.cpp`/`.h` files and update `CMakeLists.txt` accordingly.
- Follow standard C++ and CMake practices; no project-specific overrides.
- If introducing tests, add a test framework (e.g., GoogleTest) and update CMake.
- Document any new conventions or workflows in this file as the project evolves.

