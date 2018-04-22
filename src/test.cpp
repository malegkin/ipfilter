#include "stdafx.h"

#define BOOST_TEST_MODULE test_foo
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include "foo.h"
#include <iostream>
#include <fstream>
#include "openssl/md5.h"

#define LOG_LEVEL all

BOOST_AUTO_TEST_SUITE(test_suite_main)

    boost::filesystem::path get_work_dir()
    {
        int argc        = boost::unit_test::framework::master_test_suite().argc;
        char** argv     = boost::unit_test::framework::master_test_suite().argv;

        BOOST_REQUIRE( argc == 2);

        return boost::filesystem::path( argv[1] );
    }

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


vector< ip_t > process_file(string file_name, uint32_t repeats = 1 )
{
    ifstream ifs ( file_name );
    BOOST_REQUIRE( ifs.is_open() );

    stringstream buffer;

    for (uint32_t u = 0; u < repeats; u++) {
        buffer << ifs.rdbuf();
        ifs.seekg (0, ifs.beg);
    }

    ifs.close();

    return process(buffer);
}

    vector< ip_t > process_file(string file_name, filter_predicat_t filter, uint32_t repeats = 1 )
    {
        ifstream ifs ( file_name );
        BOOST_REQUIRE( ifs.is_open() );

        stringstream buffer;

        for (uint32_t u = 0; u < repeats; u++) {
            buffer << ifs.rdbuf();
            ifs.seekg (0, ifs.beg);
        }

        ifs.close();

        return process(buffer, vector<filter_predicat_t>({filter}));
    }



void test_filter( string ips_fn, string sorted_ips_fn, filter_predicat_t filter )
{
    auto ips = process_file( ips_fn, filter );
   
    ifstream ifs( sorted_ips_fn );
    BOOST_REQUIRE( ifs.is_open() );

    auto ips_it = begin(ips);
    for (string line; getline(ifs, line); ips_it++){
        BOOST_REQUIRE( line == to_string(*ips_it));
    }

    ifs.close();
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
    BOOST_REQUIRE_THROW( s2ip("abrakadabra"), std::invalid_argument );

}


    BOOST_AUTO_TEST_CASE( test_filter_0 )
    {
        boost::filesystem::path in_fn       = get_work_dir()  / "ips.tsv" ;
        boost::filesystem::path sorted_fn   = get_work_dir()  / "sorted_ips_0.tsv" ;

        test_filter(in_fn.string(), sorted_fn.string(), FILTER_PREDICAT_0);
    }

    BOOST_AUTO_TEST_CASE( test_filter_1 )
    {
        boost::filesystem::path in_fn       = get_work_dir()  / "ips.tsv" ;
        boost::filesystem::path sorted_fn   = get_work_dir()  / "sorted_ips_1.tsv" ;

        test_filter(in_fn.string(), sorted_fn.string(), FILTER_PREDICAT_1);
    }

    BOOST_AUTO_TEST_CASE( test_filter_2 )
    {
        boost::filesystem::path in_fn       = get_work_dir()  / "ips.tsv" ;
        boost::filesystem::path sorted_fn   = get_work_dir()  / "sorted_ips_2.tsv" ;

        test_filter(in_fn.string(), sorted_fn.string(), FILTER_PREDICAT_2);
    }

    BOOST_AUTO_TEST_CASE( test_filter_3 )
    {
        boost::filesystem::path in_fn       = get_work_dir()  / "ips.tsv" ;
        boost::filesystem::path sorted_fn   = get_work_dir()  / "sorted_ips_3.tsv" ;

        test_filter(in_fn.string(), sorted_fn.string(), FILTER_PREDICAT_3);
    }


    BOOST_AUTO_TEST_CASE( test_process )
{
    boost::filesystem::path in_fn       = get_work_dir()  / "ips.tsv" ;
    boost::filesystem::path sorted_fn   = get_work_dir()  / "sorted_ips.tsv" ;

    auto ips = process_file( in_fn.string() );

    BOOST_REQUIRE ( ips.size() > 1000 );
    
    ifstream ifs( sorted_fn.string() );
    BOOST_REQUIRE( ifs.is_open() );

    auto ips_it = begin(ips);
    for (string line; getline(ifs, line); ips_it++){
        BOOST_REQUIRE( line == to_string(*ips_it));
    }

    ifs.close();
}

BOOST_AUTO_TEST_CASE( test_process_on_empty_in )
{
    stringstream ss;
        
    auto ips = process( ss );

    BOOST_REQUIRE( ips.size() == 0 );

}

BOOST_AUTO_TEST_CASE( test_ip_parser_big_line )
{  
    uint32_t bs_size = 8*1024*1024;
    stringstream ss;
    unique_ptr<char[]> big_cstring(new char[ bs_size ]);
    memset(big_cstring.get(), '.', bs_size);
    big_cstring[ bs_size -1] = '\0'; 
    ss << "1.2.3.4\t5\t2" << big_cstring.get() << endl;
 
    ip_t ip = s2ip( ss.str() );

    BOOST_REQUIRE( to_string( ip ) == "1.2.3.4" );
}

BOOST_AUTO_TEST_CASE( test_ip_filter_otus )
{
    boost::filesystem::path test_fn  = get_work_dir()  / "ip_filter.tsv" ;

    BOOST_REQUIRE( md5(process_file( test_fn.string() )) == "24e7a7b227daee89c64d3ca5fb3da1a");

}


BOOST_AUTO_TEST_CASE(testip_filter_1M)
{
    boost::filesystem::path test_fn  = get_work_dir()  / "ips.tsv" ;
    
    BOOST_REQUIRE ( process_file( test_fn.string(), 100).size() > 1000 * 1000 );
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
