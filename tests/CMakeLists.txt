project(test)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(test_main_cli test_main.cpp ../src/filter.cpp)

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

#--log_level=all
enable_testing()

add_test(test_version_valid  test_main_cli -t test_suite_main/test_version_valid)

add_test(test_rec_filter     test_main_cli -t test_suite_ip_filter/rec_filter)
add_test(test_empty_data     test_main_cli -t test_suite_ip_filter/empty_data )
add_test(test_valid_data     test_main_cli -t test_suite_ip_filter/valid_data )
add_test(test_invalid_data   test_main_cli -t test_suite_ip_filter/invalid_data )

