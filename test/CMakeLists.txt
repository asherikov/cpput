add_executable(inclusion "./inclusion.cpp")
target_link_libraries(inclusion ${GOOGLETEST_LIBS})
add_dependencies(inclusion TGT_googletest)
add_test(NAME inclusion COMMAND inclusion)
