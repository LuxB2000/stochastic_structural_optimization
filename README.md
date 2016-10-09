# Stochastic Structural Optimization
proof of concept illustrating the evolutionnary algorithm applied to structural optimization

## Dependencies
- Armadillo: http://arma.sourceforge.net/ - version 5.2 or higher,
- CMake
- easylogging++: the library is located in folder 'libs/easyloggingpp', see \url{https://github.com/easylogging/easyloggingpp}

## Build
> mkdir build

> cd build

> cmake ..

## Run Unit tests
Run the unit tests with:
> ./UnitTester

Some tests require to have access to matrix that have to be generted using Matlab. To create these data, you have to run the script 'createAllUnitTestData.m' in tests/matlab. The matrix files will be written in a new folder tests/data.

## Run EASEA optimization
- cd easea/v0.1
- easea optimizer.ez
- make
- ./optimizer

