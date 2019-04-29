project(lect10code)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_FILE_OFFSET_BITS=64")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall --pedantic -g -O0 -D_DEBUG")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_executable(dir dir.c)
add_executable(flock flock.c)
find_package(Threads)
add_executable(flock_2 flock_2.c)
target_link_libraries(flock_2 ${CMAKE_THREAD_LIBS_INIT})
add_executable(flock_3 flock_3.c)
target_link_libraries(flock_3 ${CMAKE_THREAD_LIBS_INIT})
add_executable(fpos fpos.c)
add_executable(fstats fstats.c)
add_executable(ftrunk ftrunk.c)
add_executable(mode_t mode_t.c)




