cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

set(PROJECT_NAME meteo-top-test)
project(${PROJECT_NAME} CXX)

Include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1 # or a later release
)
FetchContent_MakeAvailable(Catch2)

# find_package
find_package(Threads REQUIRED)
find_package(CURL REQUIRED)

#  include_directories
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../include")
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../src")
set(SOURCE_TESTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

# libraries
set( LLIBRARIES
    Threads::Threads
    ${CURL_LIBRARIES}
    Catch2::Catch2WithMain
)

set(CATCH2_FILTER "[unit]")

function(build_tests_target)
    
    file(GLOB_RECURSE SRC_FILES ${SOURCE_DIR}/*.cpp)
    list(REMOVE_ITEM SRC_FILES ${SOURCE_DIR}/main.cpp)
    
    file(GLOB_RECURSE SRC_TEST_FILES ${SOURCE_TESTS_DIR}/*.cpp)
    list(APPEND SRC_TEST_FILES ${SRC_FILES})
    
    include_directories(${INCLUDE_DIR}) # include the header files for compilation
    add_executable(${PROJECT_NAME} ${SRC_TEST_FILES})

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
    
    add_custom_target(tests ALL
        COMMAND ${CMAKE_COMMAND} -E env UBSAN_OPTIONS=halt_on_error=1
        $<TARGET_FILE:${PROJECT_NAME}> ${CATCH2_FILTER}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Running ${PROJECT_NAME}..."
        DEPENDS ${PROJECT_NAME}
    )

endfunction()


build_tests_target()




