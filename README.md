# meteo-top
A C++ program that makes a periodic get request to the Meteo API.

#  Dependencies

This project was developed in C++ and has the following dependencies:
```
$ sudo apt-get install build-essential cmake
$ sudo apt-get install curl libcurl4-openssl-dev   
```
##  Other dependencies
The following dependencies are automatically downloaded and linked to the project from CMakeLists.txt
- [yaml-cpp](https://github.com/jbeder/yaml-cpp)
- [Catch2](https://github.com/catchorg/Catch2)

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
 


# Project Structure

    .
    ├── build                                       # Compiled files (local)
    ├── include                                     # Header files 
    │   ├── CURLCommunicationChannel.hpp            # GET request class
    │   ├── PeriodicTask.hpp                        # Periodic task execution class
    │   ├── PeriodicRequest.hpp                     # Periodic GET request execution class
    │   ├── DisplayData.hpp                         # YAML data display class 
    │   └── YamlCPP.hpp                             # include the yaml-cpp library
    ├── src                                         # Source files 
    │   ├── CURLCommunicationChannel.cpp            
    │   ├── PeriodicRequest.cpp                     
    │   ├── PeriodicTask.cpp                        
    │   ├── YamlCPP.cpp                             
    │   └── main.cpp                                # Main menu and deploy of periodic requests 
    ├── test                                        # Automated tests (Catch2)
    │   ├── src-test                                
    │   │   ├── CURLCommunicationChannel_test.cpp   
    │   │   ├── PeriodicRequest_test.cpp            
    │   │   └── main.YamlCPP                        
    │   └── CMakeLists.txt                          
    ├── CMakeLists.txt
    └── README.md

# Help menu

```
$ ./meteo-top -h
usage: meteo-top [-t <periodic_time_us>] [-n <number_of_requests>] 
                 [-i] [-a] [-h]
  options:
    -t <periodic_time_us>   = Time interval between requests in microseconds
    -n <number_of_requests> = Number of requests to perform
    -i                      = Enable makes infinite requests and ignores any
                              input with -n
    -a                      = Display the full response to the GET request
    -h                      = Print help
Note: -t and either -n or -i options are required to run the program
```


# An example of how to run the program

```
$ ./meteo-top -t 1e6 -n 10
```
