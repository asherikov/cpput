set(TEST_LIBS "")

# --------------
# required to pull googletest
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
# required for tests
set(GOOGLETEST_DIR  "${CMAKE_CURRENT_LIST_DIR}/googletest")

set(GOOGLETEST_ARGS
    ${REPOS_ARGS}
    -DBUILD_GMOCK=OFF
    -DBUILD_GTEST=ON
    -Dgtest_disable_pthreads=ON
    "-DCMAKE_CXX_FLAGS=-fPIC")

cmakeut_add_external_git_project(   TARGET_NAME "TGT_googletest"
                                    PROJECT_DIR "${GOOGLETEST_DIR}"
                                    CMAKE_ARGS   ${GOOGLETEST_ARGS})

set(TEST_LIBS "${TEST_LIBS};${REPOS_LIBDIR}/${CMAKE_SHARED_MODULE_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}")
# --------------

# --------------
# required on some non-Linux systems for print_backtrace().
find_package(Backtrace)
if (Backtrace_FOUND)
    include_directories ("${Backtrace_INCLUDE_DIRS}")
    set(TEST_LIBS "${TEST_LIBS};${Backtrace_LIBRARIES}")
endif()
# --------------

add_executable(inclusion "./inclusion.cpp")
target_link_libraries(inclusion "${TEST_LIBS}")
add_dependencies(inclusion TGT_googletest)
add_test(NAME inclusion COMMAND inclusion)
