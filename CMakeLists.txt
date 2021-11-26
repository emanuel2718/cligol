cmake_minimum_required(VERSION 3.1)

set(PROJECT_NAME cligol)
project(${PROJECT_NAME} CXX)
set(CMAKE_CXX_STANDARD 17)

set(SRC_DIR src)
set(INCL_DIR include)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Werror -Wall -lncurses -ggdb3")

include_directories(${PROJECT_SOURCE_DIR}/${INCL_DIR})


set(CURSES_USE_NCURSES TRUE)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

set(SOURCE
  ${SRC_DIR}/main.cpp
  ${SRC_DIR}/util.cpp
  ${SRC_DIR}/gameoflife.cpp
  )


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} ncurses)

# add maps folders
set(source "${CMAKE_SOURCE_DIR}/maps")
set(destination "${CMAKE_CURRENT_BINARY_DIR}/maps")
add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination}
  DEPENDS ${destination}
  COMMENT "[OK] Symbolic linked maps folder"
  #COMMENT "symbolic link maps folder from ${source} => ${destination}"
  )
