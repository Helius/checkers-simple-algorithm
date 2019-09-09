cmake_minimum_required(VERSION 2.8.9)
project (checkers)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
#add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/../googletest
#                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
#                 EXCLUDE_FROM_ALL)
add_subdirectory("googletest")

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("googletest/googletest/include")
endif()

# Now simply link against gtest or gtest_main as needed. Eg

add_executable(checkers checkers.cpp)
add_executable(checkersAI checkersAI.cpp)

################################
# Unit Tests
################################
# Add test cpp file
add_executable( checkers_test checkers_test.cpp )
# Link test executable against gtest & gtest_main
target_link_libraries(checkers_test gtest gtest_main)
add_test( checkers_test checkers_test )
