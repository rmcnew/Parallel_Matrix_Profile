cmake_minimum_required(VERSION 3.10)

# get the number of processors for mpirun
include(ProcessorCount)
ProcessorCount(MPI_NUMBER_OF_PROCESSORS)


# set the project name and C++17 standard
project(Group_010 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

# cmake modules go in cmake directory
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# ensure support for C++ 17 filesystem APIs
if(NOT APPLE)
find_package(Filesystem REQUIRED)
endif()

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
add_subdirectory(fftw3)
set(fftw3_SOURCE_DIR "${PROJECT_SOURCE_DIR}/fftw3")
set(fftw3_BINARY_DIR "${CMAKE_BINARY_DIR}/fftw3")
link_directories("${fftw3_BINARY_DIR}")

# CSV Parser from https://github.com/vincentlaucsb/csv-parser
add_subdirectory(csv-parser)
set(CSV_PARSER_SOURCE_DIR "${PROJECT_SOURCE_DIR}/csv-parser")

# get MPI support package
find_package(MPI REQUIRED)


## uncomment to print all defined variables (useful for debugging)
get_cmake_property(_variableNames VARIABLES)
list (SORT _variableNames)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()

#message(STATUS "Run: ${MPIEXEC_EXECUTABLE} ${MPIEXEC_NUMPROC_FLAG} ${MPI_NUMBER_OF_PROCESSORS} EXECUTABLE ARGS")

# turn-on CMake test integration
enable_testing()

########### programs ###########
set(MATRIX_PROFILE_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
file(GLOB matrix_profile_SRC
    "${MATRIX_PROFILE_SOURCE_DIR}/*.h"
    "${MATRIX_PROFILE_SOURCE_DIR}/*.cxx"
)

# add the executable
add_executable(matrix_profile ${matrix_profile_SRC})

# needed include paths
target_include_directories(matrix_profile PUBLIC ${MPI_CXX_INCLUDE_PATH} ${fftw3_SOURCE_DIR}/api ${CSV_PARSER_SOURCE_DIR}/single_include)

# compile options
target_compile_options(matrix_profile PUBLIC ${MPI_CXX_COMPILE_FLAGS})  

# link libraries
if(MINGW)
    set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ ${CMAKE_CXX_STANDARD_LIBRARIES}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
endif()

if(NOT APPLE)
target_link_libraries(matrix_profile PUBLIC fftw3l ${MPI_CXX_LIBRARIES} ${MPI_CXX_LINK_FLAGS} csv std::filesystem)
else()
target_link_libraries(matrix_profile PUBLIC fftw3l ${MPI_CXX_LIBRARIES} ${MPI_CXX_LINK_FLAGS} csv)
endif()

# mpirun target
add_custom_target(run COMMAND ${MPIEXEC_EXECUTABLE} ${MPIEXEC_NUMPROC_FLAG} ${MPI_NUMBER_OF_PROCESSORS} ${CMAKE_CURRENT_BINARY_DIR}/matrix_profile) 


########### tests ###########

### test executables ###
# sanity tests for external dependencies
add_executable(hello_test tests/hello_test.cxx)
target_link_libraries(hello_test gtest_main)

if(WIN32 AND NOT MINGW)
    # copy the FFTW3 dll to the executables directory
    # so the executables and tests can find it
    add_custom_command(TARGET hello_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_BINARY_DIR}/bin/gtest_maind.dll"
        "${CMAKE_BINARY_DIR}")

    add_custom_command(TARGET hello_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_BINARY_DIR}/bin/gtestd.dll"
        "${CMAKE_BINARY_DIR}")
endif()

add_executable(fftw_test tests/fftw_test.cxx)
target_include_directories(fftw_test PUBLIC ${fftw3_SOURCE_DIR}/api)
target_link_libraries(fftw_test fftw3l gtest_main)

if(MINGW)
    # copy the FFTW3 dll to the executables directory
    # so the executables and tests can find it
    add_custom_command(TARGET fftw_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${fftw3_BINARY_DIR}/libfftw3l.dll"
        "${CMAKE_BINARY_DIR}")
endif()
if(WIN32 AND NOT MINGW)
    # copy the FFTW3 dll to the executables directory
    # so the executables and tests can find it
    add_custom_command(TARGET fftw_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${fftw_BINARY_DIR}/fftw3l.dll"
        "${CMAKE_BINARY_DIR}")
endif()


# tests for matrix_profile components
add_executable(timing_test tests/timing_test.cxx src/timing.cxx)
target_include_directories(timing_test PUBLIC ${MATRIX_PROFILE_SOURCE_DIR})
target_link_libraries(timing_test gtest_main)

add_executable(log_test tests/log_test.cxx src/timing.cxx src/log.cxx)
target_include_directories(log_test PUBLIC ${MATRIX_PROFILE_SOURCE_DIR})
if(NOT APPLE)
target_link_libraries(log_test gtest_main std::filesystem)
else()
target_link_libraries(log_test gtest_main)
endif()

add_executable(read_time_series_csv_test tests/read_time_series_csv_test.cxx src/read_time_series_csv.cxx)
target_include_directories(read_time_series_csv_test PUBLIC ${MATRIX_PROFILE_SOURCE_DIR} ${CSV_PARSER_SOURCE_DIR}/single_include)
target_link_libraries(read_time_series_csv_test csv gtest_main)

add_executable(write_matrix_profile_csv_test tests/write_matrix_profile_csv_test.cxx src/write_matrix_profile_csv.cxx)
target_include_directories(write_matrix_profile_csv_test PUBLIC ${MATRIX_PROFILE_SOURCE_DIR})
target_link_libraries(write_matrix_profile_csv_test gtest_main)

add_executable(command_line_args_test tests/command_line_args_test.cxx src/command_line_args.cxx)
target_include_directories(command_line_args_test PUBLIC ${MATRIX_PROFILE_SOURCE_DIR} ${MPI_CXX_INCLUDE_PATH})
target_compile_options(command_line_args_test PUBLIC ${MPI_CXX_COMPILE_FLAGS})  
target_link_libraries(command_line_args_test PUBLIC ${MPI_CXX_LIBRARIES} ${MPI_CXX_LINK_FLAGS} gtest_main)

add_executable(fourier_transform_test tests/fourier_transform_test.cxx src/fourier_transform.cxx)
target_include_directories(fourier_transform_test PUBLIC ${MATRIX_PROFILE_SOURCE_DIR} ${fftw3_SOURCE_DIR}/api)
target_link_libraries(fourier_transform_test fftw3l gtest_main)

add_executable(sliding_dot_product_test tests/sliding_dot_product_test.cxx src/sliding_dot_product.cxx src/fourier_transform.cxx)
target_include_directories(sliding_dot_product_test PUBLIC ${MATRIX_PROFILE_SOURCE_DIR} ${fftw3_SOURCE_DIR}/api)
target_link_libraries(sliding_dot_product_test fftw3l gtest_main)

add_executable(mean_and_standard_deviation_test tests/mean_and_standard_deviation_test.cxx src/mean_and_standard_deviation.cxx)
target_include_directories(mean_and_standard_deviation_test PUBLIC ${MATRIX_PROFILE_SOURCE_DIR})
target_link_libraries(mean_and_standard_deviation_test gtest_main)

add_executable(distance_profile_test tests/distance_profile_test.cxx src/distance_profile.cxx src/mean_and_standard_deviation.cxx src/fourier_transform.cxx src/sliding_dot_product.cxx)
target_include_directories(distance_profile_test PUBLIC ${MATRIX_PROFILE_SOURCE_DIR} ${fftw3_SOURCE_DIR}/api)
target_link_libraries(distance_profile_test fftw3l gtest_main)

add_executable(stamp_test tests/stamp_test.cxx src/stamp.cxx src/distance_profile.cxx src/mean_and_standard_deviation.cxx src/fourier_transform.cxx src/sliding_dot_product.cxx)
target_include_directories(stamp_test PUBLIC ${MATRIX_PROFILE_SOURCE_DIR} ${fftw3_SOURCE_DIR}/api)
target_link_libraries(stamp_test fftw3l gtest_main)


include(GoogleTest)
gtest_discover_tests(hello_test)
gtest_discover_tests(fftw_test)
gtest_discover_tests(timing_test)
gtest_discover_tests(log_test)
gtest_discover_tests(read_time_series_csv_test)              
gtest_discover_tests(write_matrix_profile_csv_test)
gtest_discover_tests(command_line_args_test)
gtest_discover_tests(fourier_transform_test)
gtest_discover_tests(sliding_dot_product_test)
gtest_discover_tests(mean_and_standard_deviation_test)
gtest_discover_tests(distance_profile_test)
gtest_discover_tests(stamp_test)

