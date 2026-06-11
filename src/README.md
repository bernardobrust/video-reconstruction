# Source code
There are two main directories here:
- `inspector`: a tool to visualize intra and inter prediction in video files.
- `reconstructor`: the tool responsable for reconstructing from the videos

The other directories:
- `lib`: contains the test library and beter data types
- `test_files`: contains the files for testing

## Building inspector on GNU + Linux (Only X11 for now)
Dependencies:
- Lib X11 for window creation if targeting x11
- Still TODO on wayland

To build each of these you run

``` sh
make TARGET=inspector MODE=$(mode) WINDOWING=$(windowing)
```

Examples:
- For debug for x11: `make TARGET=inspector`
- For release for wayland: `make TARGET=inspector MODE=release WINDOWING=wayland`
- Testing on wayland: `make test TARGET=inspector WINDOWING=wayland`

## Building on Windows (on TODO list)
A `build.bat` script is provided for Windows users. It requires `gcc` (e.g.,
via MinGW-w64) to be in your PATH.

> **Note:** This script is currently **untested** as development is primarily
done on Linux. Additionally, the project does not have a windows layer yet.

To build, run:
``` cmd
build.bat <target> [mode]
```
Example:
``` cmd
build.bat inspector debug
```
