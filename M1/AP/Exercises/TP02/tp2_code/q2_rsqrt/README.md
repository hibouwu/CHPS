## Study of reciprocal square root computation

### I/ Overview of the archive

This archive contains the code to complete for exercise 2 of TP2.
The code is split into 3 files:
- `driver.c` contains the main function of the driver and performs things like argument parsing, ...
- `benchmarks.c` contains the function that call and measure accuracy/performances of the different variants
- `variants.c` contains the inline ASM snippets for the different variants, which you are supposed to complete
=> The only file you need to modify is `variants.c`, but feel free to have a look at the rest of the code.

There are also a couple of other directories:
- `outputs`: is empty for now, but will contain the results file in `.dat` format
-  `gnuplots`: contains the plotting scripts. Those scripts will save plots in this directory, in PDF format.


### II/ Building and running the driver

#### Building
```
❯ make driver
```
To clean the `driver` binary and the object files:
```
❯ make clean
```

#### Running
The `driver` binary accepts a single parameter, which is the variant to run:
```
❯ ./driver [variant]
[variant]
Cycles/iter: 5.948566
Wrote results to outputs/[variant]_results.dat
```
where available variants are `naive`, `newton`, `fast`  and correspond to questions 2.1 to 2.3.
Notice how this prints the cycles per computation/iteration and the location of the result file.

#### Frequency governor for performance measurement
In order to perform reliable performance measurement, you should ensure that your CPU frequency governor is set appropriately.
Available CPU governors can be listed with:
```
❯ cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_available_governors
performance powersave
```

In this example, the governor should be set to `performance` with:
```
❯ sudo cpupower frequency-set --governor performance
Setting cpu: 0
Setting cpu: 1
Setting cpu: 2
Setting cpu: 3
Setting cpu: 4
Setting cpu: 5
Setting cpu: 6
Setting cpu: 7
```

### III/ Plots generation

#### Installing gnuplot

Plot generation is done using [gnuplot](http://www.gnuplot.info/).
Depending on your distribution, it can be installed with:
**Debian / Ubuntu:**
```
❯ sudo apt install gnuplot
```
**Arch:**
```
❯ sudo pacman -S gnuplot
```
Windows binaries are also available on the official website.

#### Calling the scripts

Plotting scripts should be called from the archive root in the following way:
```
❯ gnuplot -c gnuplots/plot_values.plg outputs/[variant]_results.dat   # Plot results
❯ gnuplot -c gnuplots/plot_abs_err.plg outputs/[variant]_results.dat   # Plot absolute error
❯ gnuplot -c gnuplots/plot_rel_err.plg outputs/[variant]_results.dat   # Plot relative error
```

These commands will respectively generate the `outputs/values.pdf`, `outputs/abs_err.pdf` and `outputs/rel_err.pdf` plots.
