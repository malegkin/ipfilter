#include "stdafx.h"

#include <cstdlib>
#include <regex>
#include <map>
#include <boost/algorithm/string.hpp>
#include <utility>

#include "foo.h"

ip_t s2ip(const string& in)
{
    ip_t out;    
    
    uint32_t oct     = 0;
    uint32_t iph     = 0;
    uint8_t  p_count = 0;   

    for(size_t i = 0; i <= 16;  i++) {  // max ip lenght == 16   
        switch(in[i]) {
            case '0' ... '9':
                oct = (oct * 10) + static_cast<uint32_t>(in[i] - '0');
                break;
 
           case '.':
                if ( oct > 255 )
                    throw std::invalid_argument("The line \"" + in + "\" contained a unsupported string!");
    
                p_count++;
                iph = (iph << 8) + oct ;
                oct = 0;
                break;

            case '\t':
            case '\n':
            case '\0':
                if ( p_count != 3  ||  oct > 255 )
                    throw std::invalid_argument("The line \"" + in + "\" contained a unsupported string!");

                iph = (iph << 8) + oct;
                return make_pair(iph, in.substr(0, i) ) ;   
                
            default:
                throw std::invalid_argument("The line \"" + in + "\" contained a unsupported string!");
         
        }    
    }

    throw std::invalid_argument("The line \"" + in + "\" contained a unsupported string!");
} 


uint8_t ip2oct(const ip_t& ip, const uint8_t i )
{
    if ( i > 3 )
        throw std::out_of_range("'i' must be a number between 0 and 3");

    return static_cast<uint8_t>( ( get<uint32_t>(ip) << (8 * i)) >> 24 );
}



vector< ip_t > process( istream& in )
{
    multimap<uint32_t, string, greater<uint32_t> > ips;
    vector< ip_t > out;

    transform( getline_iterator( in ), getline_iterator(), inserter( ips, begin(ips) ), [&](string line){
            return s2ip( line );
    } );

    vector< function< bool( const ip_t& ) >> filters;
        //Вывод всех ip
        filters.push_back( []( const ip_t& ) {
            return true;
        });
        //Сразу продолжается список адресов первый байт которых равен 1. 
        filters.push_back( [](const ip_t& ip) {
            return ip2oct(ip, 0) == 1 ;
        });
        //Сразу продолжается список адресов первый байт которых равен 46, а второй 70.    
        filters.push_back( [](const ip_t& ip) {
            return ip2oct(ip, 0) == 46 && ip2oct(ip, 1) == 70 ;
        });
        //Сразу продолжается список адресов любой байт которых равен 46.
        filters.push_back( [](const ip_t& ip) {
            return ip2oct(ip, 0) == 46 || ip2oct(ip, 1) == 46 || ip2oct(ip, 2) == 46 || ip2oct(ip, 3) == 46;
        });
    
    for(auto filter: filters){
        copy_if( begin(ips), end(ips), inserter(out, end(out)), filter);
    }
 
    return out;
}

string to_string(const ip_t& ip){
    return ip.second;
}
