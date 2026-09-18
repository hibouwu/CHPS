# Lab 3: Exercise 2 - Matrix Product

In this exercise, we will use Kokkos for representing matrices and for expressing shared-memory parallelism
(equivalent to OpenMP on CPU). For more information, check the full Kokkos documentation [here](https://kokkos.org/kokkos-core-wiki/index.html).

### Compilation

To compile the code, the following are the minimal CMake commands:
```sh
cmake -B <BUILD_DIRECTORY> \
      -DCMAKE_BUILD_TYPE=Release \ # Compile in release mode, i.e. w/ `-O3`
      -DKokkos_ENABLE_OPENMP=ON    # Activate the OpenMP backend for Kokkos
cmake --build <BUILD_DIRECTORY>
```

See all the CMake keywords supported by Kokkos [here](https://kokkos.org/kokkos-core-wiki/get-started/configuration-guide.html).

### Running

You can then run the code normally. If benchmarking on a laptop, we advise to use the following OpenMP environment variables:
```sh
# Number of threads should be the number of *physical* cores
export OMP_NUM_THREADS=$(lscpu -p | egrep -v '^#' | sort -u -t, -k 2,4 | wc -l)
export OMP_PROC_BIND=true
export OMP_PLACES=cores
./build/src/top.matrix_product <M> <N> <K>
```
