# General parameters
cmake_minimum_required (VERSION 3.0.0)
project (cpput CXX)


# --------------
# Options
# --------------
set(CPPUT_ID  "CPPUT" CACHE STRING "Overrides header guards, namespace, installation path (does not apply to 3rdparty headers).")
set(CPPUT_SELECT_HEADERS       "" CACHE STRING "Selection a subset of headers for installation.")
option(CPPUT_BUILD_TESTS       "Build tests" ON)
set(CMAKE_VERBOSE_MAKEFILE     ON)
# --------------


# --------------
# Process options
# --------------
string(TOLOWER "${CPPUT_ID}" CPPUT_ID_LOWER_CASE)
if (NOT ${CPPUT_ID} STREQUAL "CPPUT")
    #    set(CPPUT_BUILD_TESTS          OFF)
endif()
# --------------


# --------------
# Load cmake modules
# --------------
include(CMakeParseArguments)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
# --------------


# --------------
# Configure headers
# --------------
include(cpput_config)
include(cmakeut_list_filenames)


cpput_config(   "${PROJECT_SOURCE_DIR}/include/cpput/cpput_config.h.in"
                "${PROJECT_SOURCE_DIR}/include/cpput/cpput_config.h")
cmakeut_list_filenames("${PROJECT_SOURCE_DIR}/include/cpput/" "CPPUT_HEADERS")
foreach (CPPUT_HEADER ${CPPUT_HEADERS})
    if (${CPPUT_HEADER} MATCHES ".h.in\$"
        AND NOT ${CPPUT_HEADER} MATCHES "cpput_config.h")
        string(REPLACE ".h.in" ".h" CPPUT_HEADER_NO_SUFFIX "${CPPUT_HEADER}")
        message("Configuring header ${CPPUT_HEADER} -> ${CPPUT_HEADER_NO_SUFFIX}")
        configure_file( "${PROJECT_SOURCE_DIR}/include/cpput/${CPPUT_HEADER}"
                        "${PROJECT_SOURCE_DIR}/include/cpput/${CPPUT_HEADER_NO_SUFFIX}")
    endif()
endforeach()

include_directories ("${PROJECT_SOURCE_DIR}/include")
if (NOT ${CPPUT_ID} STREQUAL "CPPUT")
    include_directories ("${PROJECT_SOURCE_DIR}/include/cpput")
endif()
# --------------


# --------------
# tests
# --------------
if(CPPUT_BUILD_TESTS)
    enable_testing()
    add_subdirectory("${PROJECT_SOURCE_DIR}/test")
endif()
# --------------


# --------------
# Install
# --------------
if (CPPUT_SELECT_HEADERS)
    install (DIRECTORY "${PROJECT_SOURCE_DIR}/include/${CPPUT_ID_LOWER_CASE}"
             DESTINATION "${CMAKE_INSTALL_PREFIX}/include/${CPPUT_ID_LOWER_CASE}/"
             FILES_MATCHING PATTERN "*.h")
else()
    foreach (CPPUT_HEADER ${CPPUT_SELECT_HEADERS})
        install (FILES "${PROJECT_SOURCE_DIR}/include/${CPPUT_ID_LOWER_CASE}/${CPPUT_HEADER}"
                 DESTINATION "${CMAKE_INSTALL_PREFIX}/include/${CPPUT_ID_LOWER_CASE}/${CPPUT_HEADER}"
                 FILES_MATCHING PATTERN "*.h")
    endforeach()
endif()
# --------------
