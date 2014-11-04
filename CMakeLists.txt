cmake_minimum_required(VERSION 2.8.4)

### App name
project(Raytracer)
set (APP_NAME Raytracer)

### Standart
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

### Sources directory
set (SRC_DIR ${PROJECT_SOURCE_DIR}/src)

### Build directory
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/builds )

### Warning level
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

### Source code. Recursively includes all files in SRC_DIR exclude .glsl files.
file(GLOB_RECURSE SRC ${SRC_DIR} ${SRC_DIR}/*)
FOREACH(_FILE ${SRC})
  get_filename_component(_EXT ${_FILE} EXT)
  IF (NOT ${_EXT} STREQUAL ".glsl")
    list(APPEND SRC ${_FILE})
  ENDIF()
ENDFOREACH()
add_executable ( ${APP_NAME} ${SRC} )

### Libs dirs
#link_directories ( /path/to/lib_1 )
#link_directories ( ${PROJECT_SOURCE_DIR}/libs/FreeImage/FreeImage )

### Libs names
#target_link_libraries( ${APP_NAME} name_1 )
#target_link_libraries( ${APP_NAME} FreeImage )


######### External packeges #########

### OpenMP
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()