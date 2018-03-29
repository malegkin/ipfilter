#include "stdafx.h"

#define BOOST_TEST_MODULE test_foo
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include "foo.h"
#include <iostream>
#include <fstream>
#include "openssl/md5.h"

BOOST_AUTO_TEST_SUITE(test_suite_main)

string md5(const vector<ip_t>& ips){
    uint8_t digest[16];

    MD5_CTX ctx;
    MD5_Init(&ctx);
    for( auto ip: ips ){
        string ip_string = to_string(ip) + "\n";
        MD5_Update(&ctx, ip_string.c_str(), ip_string.size());
    }
    MD5_Final(digest, &ctx);

    stringstream md5stream;
    for (auto d: digest){
        md5stream << std::hex << static_cast<uint32_t>(d);
    }
    
    return md5stream.str();
} 

vector<ip_t> process_file(string file_name)
{
    ifstream ifs ( file_name );
    BOOST_REQUIRE( ifs.is_open() );

    vector<ip_t> ips = process( ifs );

    ifs.close();
    
    return ips;
}

boost::filesystem::path get_work_dir()
{
    int argc        = boost::unit_test::framework::master_test_suite().argc;
    char** argv     = boost::unit_test::framework::master_test_suite().argv;

    cout << argc << endl;
    BOOST_REQUIRE( argc == 2);

    return boost::filesystem::path( argv[1] );
}

BOOST_AUTO_TEST_CASE(test_ip_parser)
{
    //positive cases
    ip_t ip      = s2ip("1.2.3.4\t111\t5");
    uint32_t iph = get<0>(ip);
    string   ips = get<1>(ip);
    
    BOOST_REQUIRE( iph == 16909060 );
    BOOST_REQUIRE( ips == "1.2.3.4" );

    BOOST_REQUIRE( ip2oct(ip, 0) == 1 );
    BOOST_REQUIRE( ip2oct(ip, 1) == 2 );
    BOOST_REQUIRE( ip2oct(ip, 2) == 3 );
    BOOST_REQUIRE( ip2oct(ip, 3) == 4 );
 
   //negative cases
    BOOST_REQUIRE_THROW( s2ip(""),      std::invalid_argument );
    BOOST_REQUIRE_THROW( s2ip("AAA"),   std::invalid_argument );
    BOOST_REQUIRE_THROW( s2ip("AAA.BBB.CCC.DDD"), std::invalid_argument );
    BOOST_REQUIRE_THROW( s2ip("256.2.3.4"), std::invalid_argument );
    BOOST_REQUIRE_THROW( s2ip("1.256.3.4"), std::invalid_argument );
    BOOST_REQUIRE_THROW( s2ip("1.2.256.4"), std::invalid_argument );
    BOOST_REQUIRE_THROW( s2ip("1.2.3.256"), std::invalid_argument );
    BOOST_REQUIRE_THROW( s2ip("-1.2.3.4"),  std::invalid_argument );
    BOOST_REQUIRE_THROW( s2ip("1.2.3.4.5"), std::invalid_argument );

}

BOOST_AUTO_TEST_CASE( test_ip_filter )
{
    boost::filesystem::path in_fn       = get_work_dir()  / "ips.tsv" ;
    boost::filesystem::path sorted_fn   = get_work_dir()  / "sorted_ips.tsv" ;

    auto ips = process_file( in_fn.string() );
    
    ifstream ifs( sorted_fn.string() );
    BOOST_REQUIRE( ifs.is_open() );

    BOOST_REQUIRE( equal( begin(ips), end(ips), getline_iterator( ifs ), [](const auto& ip, const string& str) {
                                                                               return to_string(ip) == str;})); 
    ifs.close();
}

BOOST_AUTO_TEST_CASE( test_ip_filter_empty )
{
    stringstream ss;
        
    auto ips = process( ss );

    BOOST_REQUIRE( ips.size() == 0 );

}

BOOST_AUTO_TEST_CASE( test_ip_filter_buffer_overflow )
{   
    stringstream ss;
    string big_string;
    big_string.reserve( 1024*1024*1024 );
    ss << "1.2.3.4\t5\t2" << big_string;
    
    auto ips = process(ss);

    BOOST_REQUIRE( to_string( ips[0] ) == "1.2.3.4" );
}

BOOST_AUTO_TEST_CASE( test_ip_filter_otus )
{
    boost::filesystem::path test_fn  = get_work_dir()  / "ip_filter.tsv" ;

    BOOST_REQUIRE( md5(process_file( test_fn.string() )) == "24e7a7b227daee89c64d3ca5fb3da1a");

}

BOOST_AUTO_TEST_CASE(testip_filter_1M)
{
    boost::filesystem::path test_fn  = get_work_dir()  / "1M.tsv" ;
    process_file( test_fn.string() );

#ifdef BOOST_SIGACTION_BASED_SIGNAL_HANDLING
  BOOST_TEST(false);
#else
  BOOST_TEST(true);
#endif
}

//negative scenarious
BOOST_AUTO_TEST_CASE( test_ip_filter_ne_big_octet )
{
    stringstream ss;
    ss << "256.1.1.2\t5\t2\n";
        
    BOOST_REQUIRE_THROW( process (ss), std::invalid_argument );
}

BOOST_AUTO_TEST_CASE( test_ip_filter_ne_alpabet_octet )
{   
    stringstream ss;
    ss << "AAA.1.1.2\t5\t2\n";
        
    BOOST_REQUIRE_THROW( process (ss), std::invalid_argument );
}

BOOST_AUTO_TEST_CASE( test_ip_filter_ne_excess_octet )
{
    stringstream ss;
    ss << "1.2.3.4.5\t5\t2\n";
        
    BOOST_REQUIRE_THROW( process (ss), std::invalid_argument );
}

BOOST_AUTO_TEST_CASE( test_ip_filter_ne_lost_octet )
{
    stringstream ss;
    ss << "1.2.3\t5\t2\n";
        
    BOOST_REQUIRE_THROW( process (ss), std::invalid_argument );
}


BOOST_AUTO_TEST_SUITE_END()
