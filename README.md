# meteo-top
A C++ program that makes a periodic get request to the Meteo API.

#  Dependencies

This project was developed in C++ and has the following dependencies:
```
$ sudo apt-get install build-essential cmake
$ sudo apt-get install curl libcurl4-openssl-dev   
```

# Build project

Typically, the project is built into a /build folder as follows:
```
$ mkdir build
$ cd build
```
To build the project, run the following commands in the build folder:
```
$ cmake ..
$ make -j
```

#### Testing
Unit tests can be enabled for debugging by adding the `TESTING` option as follows:
```
cmake -DTESTING=ON ..
make -j
```
