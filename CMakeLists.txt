cmake_minimum_required(VERSION 3.14)

find_program(CCACH_PROGRAM ccach)
if(CCACHE_PROGRAM)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

project(Chat C)

add_executable(
	chat
	src/main.c
  src/file_interact.c
)

target_link_libraries(chat PRIVATE m)
