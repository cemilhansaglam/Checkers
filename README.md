# Project Directory Structure

```
project_directory/
├── Makefile
├── *.dll                  # Place necessary DLL files here (openal32.dll, sfml-audio-2.dll, sfml-audio-d-2.dll, sfml-graphics-2.dll, sfml-graphics-d-2.dll, sfml-network-2.dll, sfml-network-d-2.dll, sfml-system-2.dll, sfml-system-d-2.dll, sfml-window-2.dll, sfml-window-d-2.dll)
├── source code (.cpp and .hpp files)
├── Resources (audio, fonts, res)
└── src/
    ├── include/
    │   └── [header files]
    └── lib/
        └── [library files]
```

# How to Build and Run the Project

1. Open a terminal in the `project_directory`.
2. Build the project by running the following command:

   ```
   mingw32-make
   ```

3. After building, run the application by typing:

   ```
   main.exe
   ```

# Clean the Project

To clean the project, use the following command:

```bash
mingw32-make clean
```

