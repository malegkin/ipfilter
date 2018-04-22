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


vector< ip_t > process( istream& in , const vector< filter_predicat_t >& filters )
{
    multimap< uint32_t, string, greater<uint32_t> > ips;
    vector< ip_t > out;

    for (string line; getline(in, line);){
        ips.insert(s2ip(line));
    }

    for(auto filter: filters){
        copy_if( begin(ips), end(ips), inserter(out, end(out)), filter);
    }

    return out;
}

vector< ip_t > process( istream& in)
{
    vector< filter_predicat_t > filters;
        filters.push_back( FILTER_PREDICAT_0 );
        filters.push_back( FILTER_PREDICAT_1 );
        filters.push_back( FILTER_PREDICAT_2 );
        filters.push_back( FILTER_PREDICAT_3 );

    return process( in, filters);
} 



string to_string(const ip_t& ip){
    return ip.second;
}
