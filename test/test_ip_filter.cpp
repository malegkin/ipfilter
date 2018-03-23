#include "stdafx.h"

#define BOOST_TEST_MODULE test_main
#include <boost/test/unit_test.hpp>

#include "IpFilter.h"

BOOST_AUTO_TEST_SUITE(test_suite_main)

BOOST_AUTO_TEST_CASE(test_ip_parser)
{
    //positive cases
    Ip ip("1.2.3.4");
    BOOST_CHECK(ip[1] == 1 && ip[2] == 2 && ip[3] == 3 && ip[4] == 4 );
    BOOST_CHECK(ip.str().compare(ip.toString()) );

    //negative cases
    BOOST_REQUIRE_THROW( Ip(""), std::invalid_argument );
    BOOST_REQUIRE_THROW( Ip("AAA"), std::invalid_argument );
    BOOST_REQUIRE_THROW( Ip("AAA.BBB.CCC.DDD"), std::invalid_argument );
    BOOST_REQUIRE_THROW( Ip("256.2.3.4"), std::invalid_argument );
    BOOST_REQUIRE_THROW( Ip("1.256.3.4"), std::invalid_argument );
    BOOST_REQUIRE_THROW( Ip("1.2.256.4"), std::invalid_argument );
    BOOST_REQUIRE_THROW( Ip("1.2.3.256"), std::invalid_argument );
    BOOST_REQUIRE_THROW( Ip("-1.2.3.4"), std::invalid_argument );
    BOOST_REQUIRE_THROW( Ip("1.2.3.4.5"), std::invalid_argument );

}

BOOST_AUTO_TEST_SUITE_END()
