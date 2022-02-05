cmake_minimum_required(VERSION 3.10)

# set the project name
project(Group_010 LANGUAGES CXX)

find_package(MPI REQUIRED)

## uncomment to print all defined variables
#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

#message(STATUS "Run: ${MPIEXEC_EXECUTABLE} ${MPIEXEC_NUMPROC_FLAG} ${MPIEXEC_MAX_NUMPROCS} ${MPIEXEC_PREFLAGS} EXECUTABLE ${MPIEXEC_POSTFLAGS} ARGS")

# add the executable
add_executable(mpi_hello src/mpi_hello.cxx)

# needed include paths
target_include_directories(mpi_hello PUBLIC ${MPI_CXX_INCLUDE_PATH})

# compile options
target_compile_options(mpi_hello PUBLIC ${MPI_CXX_COMPILE_FLAGS})  

# link libraries
target_link_libraries(mpi_hello PUBLIC ${MPI_CXX_LIBRARIES} ${MPI_CXX_LINK_FLAGS})


add_test(NAME mpi_hello
         COMMAND ${MPIEXEC_EXECUTABLE}
         ${MPIEXEC_NUMPROC_FLAG}
         ${MPIEXEC_MAX_NUMPROCS}
         ${MPIEXEC_PREFLAGS}
         ${CMAKE_CURRENT_BINARY_DIR}/mpi_hello
         ${MPIEXEC_POSTFLAGS}
         ) # <--- any other arguments to the mpi program go here

