#include "lib.h"
#include "filter.h"

#define BOOST_TEST_MODULE test_main

#include <boost/test/unit_test.hpp>
#include <boost/test/execution_monitor.hpp> 

BOOST_AUTO_TEST_SUITE(test_suite_main)

BOOST_AUTO_TEST_CASE(test_version_valid)
{
    BOOST_CHECK( (major_version() >= 0) &&  (minor_version() >= 0) && (patch_version() >= 0) );
    BOOST_CHECK( (major_version() >  0) ||  (minor_version() >  0) || (patch_version() >  0) );


}

BOOST_AUTO_TEST_CASE(test_rec_filter)
{
    rec_t r = { {11,  22,   33,   44} };

    BOOST_CHECK(  ( filter<0, 11>(r)) );
    BOOST_CHECK(  ( filter<2, 33>(r)) );
    BOOST_CHECK( !( filter<3, 33>(r)) );

    BOOST_CHECK(  ( filter_any< 33>(r)) );
    BOOST_CHECK( !( filter_any< 55>(r)) );
}

BOOST_AUTO_TEST_SUITE_END()


