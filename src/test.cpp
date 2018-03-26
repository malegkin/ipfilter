#include "stdafx.h"

#define BOOST_TEST_MODULE test_main
#include <boost/test/unit_test.hpp>

#include "foo.h"


BOOST_AUTO_TEST_SUITE(test_suite_main)

BOOST_AUTO_TEST_CASE(test_ip_parser)
{

    //positive cases
    auto t = s2IpHash("1.2.3.4\t111\t5");
    uint32_t iph = get<0>(t);
    BOOST_CHECK( iph == 16909060 );
    BOOST_CHECK( get<1>(t) == "1.2.3.4" );

    BOOST_CHECK( oct(iph, 2) == 3);
    BOOST_CHECK( h2str(iph) == "1.2.3.4");
    //negative cases
/*
    BOOST_REQUIRE_THROW( s2IpHash(""), std::invalid_argument );
    BOOST_REQUIRE_THROW( s2IpHash("AAA"), std::invalid_argument );
    BOOST_REQUIRE_THROW( s2IpHash("AAA.BBB.CCC.DDD"), std::invalid_argument );
    BOOST_REQUIRE_THROW( s2IpHash("256.2.3.4"), std::invalid_argument );
    BOOST_REQUIRE_THROW( s2IpHash("1.256.3.4"), std::invalid_argument );
    BOOST_REQUIRE_THROW( s2IpHash("1.2.256.4"), std::invalid_argument );
    BOOST_REQUIRE_THROW( s2IpHash("1.2.3.256"), std::invalid_argument );
    BOOST_REQUIRE_THROW( s2IpHash("-1.2.3.4"), std::invalid_argument );
    BOOST_REQUIRE_THROW( s2IpHash("1.2.3.4.5"), std::invalid_argument );
*/
}


BOOST_AUTO_TEST_CASE(test_ip_filter)
{
/*
    ifstream file ("ip_filter.tsv", ios::in);
    string line;
    getline(file, line);
    BOOST_CHECK(line.compare("www") == 0);
*/
//    IpPool ipp(ifstream);

  ///  for (auto ip: ipp.getInverseSortedIps()){
     //   BOOST_TEST_MESSAGE(ip.toString());
    //}
    

}


BOOST_AUTO_TEST_SUITE_END()
