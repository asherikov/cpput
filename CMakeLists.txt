# General parameters
cmake_minimum_required (VERSION 3.0.0)
project(cpput VERSION 1.2.0)


# --------------
# Options
# --------------
set(CMAKE_VERBOSE_MAKEFILE      ON)
option(CPPUT_BUILD_TESTS        "Build tests" ON)
set(CPPUT_EMBEDDED_COPY_TO_DIR  "" CACHE STRING "Installation destination.")
set(CPPUT_SELECT_HEADERS        "" CACHE STRING "Selection a subset of headers for installation.")
# --------------


# --------------
# Process options
# --------------
if (CPPUT_EMBEDDED_COPY_TO_DIR)
    set(CPPUT_BUILD_TESTS          OFF)
endif()

set(CPPUT_HEADER_DIR "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}")
# --------------


# --------------
# Packaging & installation paths
# --------------
if (NOT CPPUT_EMBEDDED_COPY_TO_DIR)
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

    set(CPPUT_INCLUDE_INSTALL_DESTINATION ${CMAKE_INSTALL_PREFIX}/include/cpput)
endif()
# --------------


# --------------
# Load cmake modules
# --------------
include(CMakeParseArguments)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
# --------------


# --------------
# library
# --------------
if(NOT CPPUT_EMBEDDED_COPY_TO_DIR)
    add_library(${PROJECT_NAME} INTERFACE)

    target_include_directories(${PROJECT_NAME} INTERFACE
        $<BUILD_INTERFACE:${CPPUT_HEADER_DIR}/../>
        $<INSTALL_INTERFACE:include>
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
if (CPPUT_EMBEDDED_COPY_TO_DIR)
    if (NOT CPPUT_SELECT_HEADERS)
        cmakeut_list_filenames("${CPPUT_HEADER_DIR}/" "CPPUT_HEADERS")
        foreach (CPPUT_HEADER ${CPPUT_HEADERS})
            if (NOT ${CPPUT_HEADER} MATCHES ".h.in\$" AND NOT ${CPPUT_HEADER} MATCHES "all.h")
                list(APPEND CPPUT_SELECT_HEADERS "${CPPUT_HEADER}")
            endif()
        endforeach()
    endif()

    if (CPPUT_SELECT_HEADERS)
        foreach (CPPUT_HEADER ${CPPUT_SELECT_HEADERS})
            if (CPPUT_HEADER)
                file(   COPY        "${CPPUT_HEADER_DIR}/${CPPUT_HEADER}"
                        DESTINATION "${PROJECT_BINARY_DIR}/")
                file(   RENAME      "${PROJECT_BINARY_DIR}/${CPPUT_HEADER}"
                                    "${CPPUT_EMBEDDED_COPY_TO_DIR}/${CPPUT_HEADER}")
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
                install (FILES "${CPPUT_HEADER_DIR}/${CPPUT_HEADER}"
                         DESTINATION "${CPPUT_INCLUDE_INSTALL_DESTINATION}/")
            endif()
        endforeach()
    else()
        install (DIRECTORY "${CPPUT_HEADER_DIR}/"
                 DESTINATION "${CPPUT_INCLUDE_INSTALL_DESTINATION}"
                 FILES_MATCHING PATTERN "*.h")
    endif()
endif()
# --------------
