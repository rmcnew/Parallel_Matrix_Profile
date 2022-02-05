cmake_minimum_required(VERSION 3.10)
include(ProcessorCount)
ProcessorCount(MPI_NUMBER_OF_PROCESSORS)

ENABLE_TESTING()

# set the project name
project(Group_010 LANGUAGES CXX)

find_package(MPI REQUIRED)

## uncomment to print all defined variables (useful for debugging)
#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

#message(STATUS "Run: ${MPIEXEC_EXECUTABLE} ${MPIEXEC_NUMPROC_FLAG} ${MPI_NUMBER_OF_PROCESSORS} EXECUTABLE ARGS")

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
                

# testing stub: runs tests
add_test(NAME mpi_hello
         COMMAND ${MPIEXEC_EXECUTABLE} ${MPIEXEC_NUMPROC_FLAG} ${MPI_NUMBER_OF_PROCESSORS} ${CMAKE_CURRENT_BINARY_DIR}/mpi_hello) 

