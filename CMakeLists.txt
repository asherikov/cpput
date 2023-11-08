# General parameters
cmake_minimum_required (VERSION 3.0.0)
project(cpput VERSION 1.2.0)


# --------------
# Options
# --------------
set(CMAKE_VERBOSE_MAKEFILE      ON)
option(CPPUT_EMBEDDED           "Embedded in another project" OFF)
option(CPPUT_BUILD_TESTS        "Build tests" ON)
set(CPPUT_EMBEDDED_ID           "" CACHE STRING "Overrides header guards, namespace (does not apply to 3rdparty headers).")
set(CPPUT_EMBEDDED_COPY_TO_DIR  "" CACHE STRING "Installation destination.")
set(CPPUT_SELECT_HEADERS        "" CACHE STRING "Selection a subset of headers for installation.")
# --------------


# --------------
# Process options
# --------------
set(CPPUT_ID "CPPUT")
if (CPPUT_EMBEDDED)
    set(CPPUT_BUILD_TESTS          OFF)
    if(CPPUT_EMBEDDED_ID)
        set(CPPUT_ID "${CPPUT_EMBEDDED_ID}")
    endif()
    if(NOT CPPUT_EMBEDDED_COPY_TO_DIR)
        message(FATAL_ERROR "CPPUT_EMBEDDED_COPY_TO_DIR must be set with CPPUT_EMBEDDED=ON")
    endif()
else()
    if (CPPUT_EMBEDDED_ID OR CPPUT_EMBEDDED_COPY_TO_DIR)
        message(WARNING "CPPUT_EMBEDDED_ID and CPPUT_EMBEDDED_COPY_TO_DIR ignored since CPPUT_EMBEDDED=OFF")
    endif()
endif()

string(TOLOWER "${CPPUT_ID}" CPPUT_ID_LOWER_CASE)

set(CPPUT_HEADER_DIR "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}")
set(CPPUT_OUTPUT_HEADER_DIR "${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}")
# --------------


# --------------
# Packaging & installation paths
# --------------
if (NOT CPPUT_EMBEDDED)
    include(CMakePackageConfigHelpers)
    set(CPPUT_INSTALL_PATH "${CMAKE_INSTALL_PREFIX}/share/cpput/")
    set(CPPUT_INCLUDES "${CMAKE_INSTALL_PREFIX}/include")

    file(
        WRITE
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        "include(\"\${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}Targets.cmake\")"
    )

    write_basic_package_version_file(
        ${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}
        COMPATIBILITY SameMajorVersion)
endif()


if (NOT CPPUT_EMBEDDED)
    set(CPPUT_INCLUDE_INSTALL_DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${CPPUT_ID_LOWER_CASE})
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

execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CPPUT_HEADER_DIR}"
    "${CPPUT_OUTPUT_HEADER_DIR}"
)
cmakeut_list_filenames("${CPPUT_OUTPUT_HEADER_DIR}/" "CPPUT_HEADERS")
foreach (CPPUT_HEADER ${CPPUT_HEADERS})
    if (${CPPUT_HEADER} MATCHES ".h.in\$")
        string(REPLACE ".h.in" ".h" CPPUT_HEADER_NO_SUFFIX "${CPPUT_HEADER}")
        message(STATUS "Configuring header ${CPPUT_OUTPUT_HEADER_DIR}/${CPPUT_HEADER} -> ${CPPUT_OUTPUT_HEADER_DIR}/${CPPUT_HEADER_NO_SUFFIX}")
        configure_file( "${CPPUT_OUTPUT_HEADER_DIR}/${CPPUT_HEADER}"
                        "${CPPUT_OUTPUT_HEADER_DIR}/${CPPUT_HEADER_NO_SUFFIX}")
    endif()
endforeach()
# --------------


# --------------
# library
# --------------
if(NOT CPPUT_EMBEDDED)
    add_library(${PROJECT_NAME} INTERFACE)

    target_include_directories(${PROJECT_NAME} INTERFACE
        $<BUILD_INTERFACE:${CPPUT_OUTPUT_HEADER_DIR}/../>
    )
    set_property(TARGET ${PROJECT_NAME} PROPERTY INTERFACE_${PROJECT_NAME}_MAJOR_VERSION ${PROJECT_VERSION_MAJOR})
    set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY COMPATIBLE_INTERFACE_STRING ${PROJECT_VERSION_MAJOR})
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
if (CPPUT_EMBEDDED)
    if (NOT CPPUT_SELECT_HEADERS)
        cmakeut_list_filenames("${CPPUT_OUTPUT_HEADER_DIR}/" "CPPUT_HEADERS")
        foreach (CPPUT_HEADER ${CPPUT_HEADERS})
            if (NOT ${CPPUT_HEADER} MATCHES ".h.in\$" AND NOT ${CPPUT_HEADER} MATCHES "all.h")
                list(APPEND CPPUT_SELECT_HEADERS "${CPPUT_HEADER}")
            endif()
        endforeach()
    endif()

    if (CPPUT_SELECT_HEADERS)
        foreach (CPPUT_HEADER ${CPPUT_SELECT_HEADERS})
            if (CPPUT_HEADER)
                file(   COPY        "${CPPUT_OUTPUT_HEADER_DIR}/${CPPUT_HEADER}"
                        DESTINATION "${PROJECT_BINARY_DIR}/")
                file(   RENAME      "${PROJECT_BINARY_DIR}/${CPPUT_HEADER}"
                                    "${CPPUT_EMBEDDED_COPY_TO_DIR}/${PROJECT_NAME}_${CPPUT_HEADER}")
            endif()
        endforeach()
    endif()
else()
    install(
        TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}
        INCLUDES DESTINATION include
    )

    export(EXPORT ${PROJECT_NAME}
        FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake"
        NAMESPACE ${PROJECT_NAME}::
    )

    install(EXPORT ${PROJECT_NAME}
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION share/${PROJECT_NAME}/
    )

    install (FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
             DESTINATION "${CPPUT_INSTALL_PATH}/")

    install (FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
             DESTINATION "${CPPUT_INSTALL_PATH}/")

    if (CPPUT_SELECT_HEADERS)
        foreach (CPPUT_HEADER ${CPPUT_SELECT_HEADERS})
            if (CPPUT_HEADER)
                install (FILES "${CPPUT_OUTPUT_HEADER_DIR}/${CPPUT_HEADER}"
                         DESTINATION "${CPPUT_INCLUDE_INSTALL_DESTINATION}/")
            endif()
        endforeach()
    else()
        install (DIRECTORY "${CPPUT_OUTPUT_HEADER_DIR}/"
                 DESTINATION "${CPPUT_INCLUDE_INSTALL_DESTINATION}"
                 FILES_MATCHING PATTERN "*.h")
    endif()
endif()
# --------------
