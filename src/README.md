# Sources
There are two main directories here:
- `inspector`: a tool to visualize intra and inter prediction in video files.
- `reconstructor`: the tool responsable for reconstructing from the videos

To build each of these you run

``` sh
make TARGET=$(target) MODE=$(mode)
```

Where the target is either the inspector or the reconstructor, and mode is debug
, test, or relese. For practical development purpuses, you can omit the mode
when building for debug (`make TARGET=$(target)`) and testing (`make test TARGET
=$(target)`).

The other direcotries:
- `lib`: contains the test library
- `test_files`: contains the files for testing
