cmake_minimum_required(VERSION 3.10)

# get the number of processors for mpirun
include(ProcessorCount)
ProcessorCount(MPI_NUMBER_OF_PROCESSORS)


# set the project name and C++17 standard
project(Group_010 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

# get GoogleTest from GitHub
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)

# Windows: prevent override of parent project compiler / linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# FFTW3
FetchContent_Declare(
    fftw3
    URL https://www.fftw.org/fftw-3.3.10.tar.gz
    URL_HASH MD5=8ccbf6a5ea78a16dbc3e1306e234cc5c
    CMAKE_CACHE_ARGS -DCMAKE_C_FLAGS:STRING=$<$<BOOL:WIN32>:-DFFTW_ENABLE_ALLOCA=0 -DWITH_OUR_MALLOC=1 -DHAVE_SSE2=1 -DHAVE_AVX=1 -DHAVE_AVX2=1 -Wl,-Bdynamic>
)
FetchContent_MakeAvailable(fftw3)

# get MPI support package
find_package(MPI REQUIRED)


## uncomment to print all defined variables (useful for debugging)
#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

#message(STATUS "Run: ${MPIEXEC_EXECUTABLE} ${MPIEXEC_NUMPROC_FLAG} ${MPI_NUMBER_OF_PROCESSORS} EXECUTABLE ARGS")

# turn-on CMake test integration
enable_testing()

########### programs ###########

# add the executable
add_executable(matrix_profile src/matrix_profile.cxx)

# needed include paths
target_include_directories(matrix_profile PUBLIC ${MPI_CXX_INCLUDE_PATH})

# compile options
target_compile_options(matrix_profile PUBLIC ${MPI_CXX_COMPILE_FLAGS})  

# link libraries
target_link_libraries(matrix_profile PUBLIC ${MPI_CXX_LIBRARIES} ${MPI_CXX_LINK_FLAGS})

# mpirun target
add_custom_target(run COMMAND ${MPIEXEC_EXECUTABLE} ${MPIEXEC_NUMPROC_FLAG} ${MPI_NUMBER_OF_PROCESSORS} ${CMAKE_CURRENT_BINARY_DIR}/matrix_profile) 


########### tests ###########

# add test executables
add_executable(hello_test tests/hello_test.cxx)
target_link_libraries(hello_test gtest_main)

add_executable(fftw_test tests/fftw_test.cxx)
target_include_directories(fftw_test PUBLIC ${fftw3_SOURCE_DIR}/api)
target_link_libraries(fftw_test gtest_main fftw3)

include(GoogleTest)
gtest_discover_tests(hello_test)
gtest_discover_tests(fftw_test)



                


