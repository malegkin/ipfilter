#define BOOST_TEST_MODULE test_main
#include <boost/test/unit_test.hpp>

#include "version.h"

BOOST_AUTO_TEST_SUITE(test_suite_main)

BOOST_AUTO_TEST_CASE(test_version_valid)
{
	BOOST_CHECK( getProjectBuildNumber() > 0 );
    BOOST_ASSERT( !getProjectVersion().empty() );
}

BOOST_AUTO_TEST_SUITE_END()
