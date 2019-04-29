project(monitor)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -m64 -D_FILE_OFFSET_BITS=64")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -m64 -g -O0 -D_DEBUG")


add_executable(monitor monitor.c)
target_link_libraries(monitor rt)

add_executable(node node.c)
target_link_libraries(node rt) 


