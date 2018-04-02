#include "lib.h"
#include "filter.h"
#include <sstream>

#define BOOST_TEST_MODULE test_main

#include <boost/test/unit_test.hpp>
#include <boost/test/execution_monitor.hpp> 
#include <boost/test/output_test_stream.hpp>

using boost::test_tools::output_test_stream;


void test_ip_filter(std::string in_data, std::string out_data)
{
    std::stringstream iss;
    std::stringstream oss;

    iss << in_data;
    process_data(oss, get_data(iss));

    BOOST_CHECK( oss.str() == out_data );

}

BOOST_AUTO_TEST_SUITE(test_suite_main)

BOOST_AUTO_TEST_CASE(test_version_valid)
{
    BOOST_CHECK( (major_version() >= 0) &&  (minor_version() >= 0) && (patch_version() >= 0) );
    BOOST_CHECK( (major_version() >  0) ||  (minor_version() >  0) || (patch_version() >  0) );
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(test_suite_ip_filter)

BOOST_AUTO_TEST_CASE(rec_filter)
{
    rec_t r = { {11,  22,   33,   44} };

    BOOST_CHECK(  ( f_and<rec_t, 0,11>(r)) );
    BOOST_CHECK(  ( f_and<rec_t, 0,11,3,44>(r)) );
    BOOST_CHECK( !( f_and<rec_t, 0,11,2,44>(r)) );
    BOOST_CHECK(  ( f_any<rec_t, 33>(r)) );
    BOOST_CHECK( !( f_any<rec_t, 55>(r)) );   
}

BOOST_AUTO_TEST_CASE(empty_data)
{
    test_ip_filter("", "");
    test_ip_filter("         ", "");
    
}

BOOST_AUTO_TEST_CASE(valid_data)
{
     
    test_ip_filter( 
    "79.180.73.190\t2\t1\n"
    "46.70.145.4\t22\t0\n"
    "67.46.81.208\t1\t 0\n"
    "85.254.10.197\t0\t7\n"
    "23.240.215.189\t6\t0\n"
    "1.29.168.152\t17\t\n",

            "85.254.10.197\n"
            "79.180.73.190\n"
            "67.46.81.208\n"
            "46.70.145.4\n"
            "23.240.215.189\n"
            "1.29.168.152\n"
            "1.29.168.152\n"
            "46.70.145.4\n"
            "67.46.81.208\n"
            "46.70.145.4\n");
}

BOOST_AUTO_TEST_CASE(invalid_data)
{
    test_ip_filter(
    "qweqweqw",                // invalid
            "");

    test_ip_filter(
    "79.180.73.190.34\t2\t1\n" // invalid  *.*.*.*.* 
    "31.29.168.152\t17\t\n",   // valid

            "31.29.168.152\n");

    test_ip_filter(
    "79.180.73.190.34\t2\t1\n" // invalid *.*.*.*.*
    "31.29.168.852\t17\t\n",   // invalid *.*.*.852 > 255 !!!

            "31.29.168.852\n");     

    test_ip_filter(
    "1.2.3.4 fasfasf\t2\t1\n",

            "1.2.3.4\n"
            "1.2.3.4\n");

    BOOST_CHECK_THROW(test_ip_filter("fasfasf 1.2.3.4 \t2\t1\n", ""), std::invalid_argument);
    BOOST_CHECK_THROW(test_ip_filter("1.2.3.43423423423423423432423234234 \t2\t1\n", ""), std::out_of_range);

    test_ip_filter("1.2.3,4.8.8 \t2\t1\n", "");
}

BOOST_AUTO_TEST_SUITE_END()
