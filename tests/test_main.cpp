#include "lib.h"
#include "ip_rec.h"

#define BOOST_TEST_MODULE test_main

#include <boost/test/unit_test.hpp>
#include <boost/test/execution_monitor.hpp> 

BOOST_AUTO_TEST_SUITE(test_suite_main)

BOOST_AUTO_TEST_CASE(test_version_valid)
{
	BOOST_CHECK( (major_version() >= 0) &&  (minor_version() >= 0) && (patch_version() >= 0) );
	BOOST_CHECK( (major_version() >  0) ||  (minor_version() >  0) || (patch_version() >  0) );


}

BOOST_AUTO_TEST_CASE(test_rec_compare)
{	

	BOOST_CHECK(   rec({"23",  "0",   "0",   "10"  }) <  rec({"111",  "0",  "0",   "10" })  );	
	BOOST_CHECK(   rec({"100", "0",   "0",   "8"   }) <  rec({"100",  "0",  "0",   "10" })  );
	BOOST_CHECK( !(rec({"127", "0",   "0",   "10"  }) <  rec({"127",  "0",  "0",    "5" })) );
	BOOST_CHECK( !(rec({"255", "255", "255", "255" }) <  rec({"255", "255", "255", "255"})) );	
}

BOOST_AUTO_TEST_CASE(test_rec_filter)
{	
	BOOST_CHECK(  ( filter<0,11>(rec({"11",  "22",   "33",   "44" })) ) );
	BOOST_CHECK(  ( filter<1,22>(rec({"11",  "22",   "33",   "44" })) ) );
	BOOST_CHECK(  ( filter<2,33>(rec({"11",  "22",   "33",   "44" })) ) );
	BOOST_CHECK(  ( filter<3,44>(rec({"11",  "22",   "33",   "44" })) ) );

	BOOST_CHECK( !( filter<0,22>(rec({"11",  "22",   "33",   "44" })) ) );
	BOOST_CHECK( !( filter<1,11>(rec({"11",  "22",   "33",   "44" })) ) );
	BOOST_CHECK( !( filter<2,44>(rec({"11",  "22",   "33",   "44" })) ) );
	BOOST_CHECK( !( filter<3,33>(rec({"11",  "22",   "33",   "44" })) ) );

}

BOOST_AUTO_TEST_SUITE_END()


