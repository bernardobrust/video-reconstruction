# Sources
There are two main directories here:
- `inspector`: a tool to visualize intra and inter prediction in video files.
- `reconstructor`: the tool responsable for reconstructing from the videos

To build each of these you run 

``` sh
make TARGET=$(target) MODE=$(mode)
```

Where the target is either the inspector or the reconstructor, and mode is debug (the default), test (to run the tests) or relese (that enables optimizations and strips debug information).

For running the tests you can run `make test TARGET=$(target) MODE=test`.

The other direcotries:
- `lib`: contains the test library
- `test_files`: contains the files for testing

Others may be added in the future for data analysis.
