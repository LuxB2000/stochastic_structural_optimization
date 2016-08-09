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

## Run EASEA optimization
- cd easea/v0.1
- easea optimizer.ez
- make
- ./optimizer

