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
add_executable(mpi_hello src/mpi_hello.cxx)

# needed include paths
target_include_directories(mpi_hello PUBLIC ${MPI_CXX_INCLUDE_PATH})

# compile options
target_compile_options(mpi_hello PUBLIC ${MPI_CXX_COMPILE_FLAGS})  

# link libraries
target_link_libraries(mpi_hello PUBLIC ${MPI_CXX_LIBRARIES} ${MPI_CXX_LINK_FLAGS})

# mpirun target
add_custom_target(run COMMAND ${MPIEXEC_EXECUTABLE} ${MPIEXEC_NUMPROC_FLAG} ${MPI_NUMBER_OF_PROCESSORS} ${CMAKE_CURRENT_BINARY_DIR}/mpi_hello) 


########### tests ###########

# add test executables
add_executable(hello_test tests/hello_test.cxx)
target_link_libraries(hello_test gtest_main)
include(GoogleTest)
gtest_discover_tests(hello_test)



                


