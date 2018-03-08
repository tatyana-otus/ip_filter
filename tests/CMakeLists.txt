project(test)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(test_main_cli test_main.cpp ../src/ip_rec.cpp)

target_include_directories(test_main_cli PRIVATE ../include)
target_include_directories(test_main_cli PRIVATE ${Boost_INCLUDE_DIR})

set_target_properties(test_main_cli PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
#  INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(test_main_cli
  ${Boost_LIBRARIES}
  helloworld
)

enable_testing()
add_test(test_version_valid test_main_cli -t test_suite_main/test_version_valid)
add_test(test_rec_compare   test_main_cli -t */test_rec_compare)
add_test(test_rec_filter    test_main_cli -t */test_rec_filter)

