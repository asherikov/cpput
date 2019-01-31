# General parameters
cmake_minimum_required (VERSION 3.0.0)
project (cpput CXX)

# --------------
include(ExternalProject)
include(CMakeParseArguments)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/3rdparty/cmakeut/cmake")
include(cmakeut_compiler_flags)
include(cpput_config)
# --------------


# --------------
set (CMAKE_VERBOSE_MAKEFILE     ON)

cpput_config(   "${PROJECT_SOURCE_DIR}/include/cpput/config.h.in"
                "${PROJECT_SOURCE_DIR}/include/cpput/config.h")

cmakeut_compiler_flags("c++11")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKEUT_CXX_FLAGS}")
# --------------


include_directories ("${PROJECT_SOURCE_DIR}/include")

enable_testing()
add_subdirectory("${PROJECT_SOURCE_DIR}/test")


install (DIRECTORY "${PROJECT_SOURCE_DIR}/include/cpput"
         DESTINATION "${CMAKE_INSTALL_PREFIX}/include/cpput/"
         FILES_MATCHING PATTERN "*.h")
