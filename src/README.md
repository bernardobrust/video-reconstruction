# Source code
There are two main directories here:
- `inspector`: a tool to visualize intra and inter prediction in video files.
- `reconstructor`: the tool responsable for reconstructing from the videos

The other directories:
- `lib`: contains the test library
- `test_files`: contains the files for testing

## Building on GNU + Linux
Dependencies:
- Lib X11 for window creation

To build each of these you run

``` sh
make TARGET=$(target) MODE=$(mode)
```

Where the target is either the inspector or the reconstructor, and mode is
debug, test, or relese. For practical development purpuses, you can omit the
mode when building for debug (`make TARGET=$(target)`) and testing (`make test
TARGET=$(target)`).

## Building on Windows
A `build.bat` script is provided for Windows users. It requires `gcc` (e.g.,
via MinGW-w64) to be in your PATH.

**Note:** This script is currently **untested** as development is primarily
done on Linux. Additionally, the project does not have a windows layer yet.

To build, run:
``` cmd
build.bat <target> [mode]
```
Example:
``` cmd
build.bat inspector debug
```
