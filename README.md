# Eigen-Gurobi

Eigen-Gurobi allows to use the Gurobi QP solver with the Eigen library.

## Dependencies

Eigen-Gurobi has two required dependancies:

* [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) >= 3.2
* [Gurobi](http://www.gurobi.com/index) >= 4.0

Optionally, unit-tests can be built using Catch2. Catch2 will be downloaded
automatically through CMake.

## Building

```sh
mkdir build
cd build
cmake [options] ..
make
```

Where the main options are:

 * `-DCMAKE_BUIlD_TYPE=Release`: Build in Release mode
 * `-DEIGEN_GUROBI_WITH_TESTS=ON`: Build unit tests
