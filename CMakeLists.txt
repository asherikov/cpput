# General parameters
cmake_minimum_required (VERSION 2.8.12)
project (cpput CXX)

# --------------
include(ExternalProject)
include(CMakeParseArguments)

set (CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include(cpput_add_external_git_project)
# --------------


# --------------
set (CMAKE_VERBOSE_MAKEFILE     ON)
set (CMAKE_CXX_FLAGS            "${CMAKE_CXX_FLAGS} -std=c++11")
# --------------


# --------------
set(REPOS_INSTALL_PREFIX    "${PROJECT_BINARY_DIR}/extra/")
set(REPOS_LIBDIR            "${REPOS_INSTALL_PREFIX}/lib")
set(REPOS_INCLUDE_DIR       "${REPOS_INSTALL_PREFIX}/include")

set(REPOS_ARGS
    --no-warn-unused-cli
    -DCMAKE_INSTALL_PREFIX=${REPOS_INSTALL_PREFIX}
    -DCMAKE_INSTALL_LIBDIR=${REPOS_LIBDIR}
    -DCMAKE_VERBOSE_MAKEFILE=${CMAKE_VERBOSE_MAKEFILE}
    -DCMAKE_BUILD_TYPE=Release)

include_directories (BEFORE SYSTEM  "${REPOS_INCLUDE_DIR}")
# --------------


# --------------
set(GOOGLETEST_DIR  "${CMAKE_CURRENT_LIST_DIR}/googletest")

set(GOOGLETEST_ARGS
    ${REPOS_ARGS}
    -DBUILD_GMOCK=OFF
    -DBUILD_GTEST=ON
    -Dgtest_disable_pthreads=ON
    "-DCMAKE_CXX_FLAGS=-fPIC")

cpput_add_external_git_project(TARGET_NAME "TGT_googletest"
                               PROJECT_DIR "${GOOGLETEST_DIR}"
                               CMAKE_ARGS   ${GOOGLETEST_ARGS})

set(GOOGLETEST_LIBS "${REPOS_LIBDIR}/${CMAKE_SHARED_MODULE_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}")
# --------------


find_package(Eigen3 REQUIRED)
include_directories(SYSTEM ${EIGEN3_INCLUDE_DIR})


include_directories ("${PROJECT_SOURCE_DIR}/include")

enable_testing()
add_subdirectory("${PROJECT_SOURCE_DIR}/test")


install (DIRECTORY "${PROJECT_SOURCE_DIR}/include/cpput"
         DESTINATION "${CMAKE_INSTALL_PREFIX}/include/cpput/")

