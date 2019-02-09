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
    set(CPPUT_EMBEDDED ON)
endif()

if (CPPUT_EMBEDDED)
    set(CPPUT_BUILD_TESTS          OFF)
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
include(cmakeut_list_filenames)
include(cmakeut_detect_func_macro)
cmakeut_detect_func_macro()

cmakeut_list_filenames("${PROJECT_SOURCE_DIR}/include/cpput/" "CPPUT_HEADERS")
foreach (CPPUT_HEADER ${CPPUT_HEADERS})
    if (${CPPUT_HEADER} MATCHES ".h.in\$")
        string(REPLACE ".h.in" ".h" CPPUT_HEADER_NO_SUFFIX "${CPPUT_HEADER}")
        message("Configuring header ${CPPUT_HEADER} -> ${CPPUT_HEADER_NO_SUFFIX}")
        configure_file( "${PROJECT_SOURCE_DIR}/include/cpput/${CPPUT_HEADER}"
                        "${PROJECT_SOURCE_DIR}/include/cpput/${CPPUT_HEADER_NO_SUFFIX}")
    endif()
endforeach()

include_directories ("${PROJECT_SOURCE_DIR}/include")
if (CPPUT_EMBEDDED)
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
# Packaging
# --------------
if (NOT CPPUT_EMBEDDED)
    include(CMakePackageConfigHelpers)
    set(CPPUT_INSTALL_PATH "${CMAKE_INSTALL_PREFIX}/share/cpput/")
    set(CPPUT_INCLUDES "${CMAKE_INSTALL_PREFIX}/include")

    configure_package_config_file(  "cmake/cpputConfig.cmake.in"
                                    "${PROJECT_BINARY_DIR}/cpputConfig.cmake"
                                    INSTALL_DESTINATION "${CMAKE_INSTALL_PREFIX}/share/cpput/"
                                    NO_SET_AND_CHECK_MACRO
                                    NO_CHECK_REQUIRED_COMPONENTS_MACRO)

    write_basic_package_version_file(
        ${PROJECT_BINARY_DIR}/cpputConfigVersion.cmake
        VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}
        COMPATIBILITY SameMajorVersion)


    install (FILES "${PROJECT_BINARY_DIR}/cpputConfig.cmake"
             DESTINATION "${CPPUT_INSTALL_PATH}/")

    install (FILES "${PROJECT_BINARY_DIR}/cpputConfigVersion.cmake"
             DESTINATION "${CPPUT_INSTALL_PATH}/")
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
