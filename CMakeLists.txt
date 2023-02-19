cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

set(PROJECT_NAME meteo-top)
project(${PROJECT_NAME} CXX)

# find_package
find_package(Threads REQUIRED)
find_package(CURL REQUIRED)

#  include_directories
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
list(APPEND ${CURL_INCLUDE_DIR})

# libraries
set( LLIBRARIES
    Threads::Threads
    ${CURL_LIBRARIES}
)

function(build_main_target)
    file(GLOB_RECURSE SRC_FILES ${SOURCE_DIR}/*.cpp)
    include_directories(${INCLUDE_DIR}) # include the header files for compilation

    add_executable(${PROJECT_NAME} ${SRC_FILES})

    target_compile_features(${PROJECT_NAME} PUBLIC
        cxx_std_17
        cxx_auto_type
        cxx_lambdas
        cxx_nullptr
        cxx_override
        cxx_range_for
    )

    target_link_libraries(${PROJECT_NAME}
        PRIVATE
        ${LLIBRARIES}
    )
    
endfunction()


build_main_target()



