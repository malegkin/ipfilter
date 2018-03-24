#include "stdafx.h"

#define BOOST_TEST_MODULE test_main
#include <boost/test/unit_test.hpp>

#include <fstream>

#include "IpFilter.h"


BOOST_AUTO_TEST_SUITE(test_suite_main)

BOOST_AUTO_TEST_CASE(test_ip_parser)
{

    //positive cases
    Ip ip("1.2.3.4");
    BOOST_CHECK( ip[0] == 1 && ip[1] == 2 && ip[2] == 3 && ip[3] == 4 );
    BOOST_CHECK( ip.toString().compare("1.2.3.4") == 0 );
    BOOST_CHECK( ip.str().compare(ip.toString()) == 0 );


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
