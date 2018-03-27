#include "stdafx.h"

#include <cstdlib>
#include <regex>
#include <map>
#include <boost/algorithm/string.hpp>

#include "foo.h"


tuple<uint32_t, string> s2IpHash(const string& in)
{
    uint8_t  u       = 0;
    uint32_t iph     = 0;

    for(size_t i = 0; i <= in.size();  i++) {
        
        switch(in[i]) {
            case '.':
                iph = iph << 8;
                iph += u;
                u = 0;
                break;
            
            case '0':
                u *= 10;
                break;
      
            case '1':
                u *= 10;
                u += 1;
                break;

            case '2':
                u *= 10;
                u += 2;
                break;

            case '3':
                u *= 10;
                u += 3;
                break;

            case '4':
                u *= 10;
                u += 4;
                break;

            case '5':
                u *= 10;
                u += 5;
                break;

            case '6':
                u *= 10;
                u += 6;
                break;

            case '7':
                u *= 10;
                u += 7;
                break;

            case '8':
                u *= 10;
                u += 8;
                break;

            case '9':
                u *= 10;
                u += 9;
                break;

            case '\t':
            case '\n':
            case '\0':
                iph = iph << 8;
                iph += u;
                return make_tuple(iph, in.substr(0, i) ) ;
            
            default:
                throw std::invalid_argument("The line \"" + in + "\" contained a unsupported string!");
         
        }    
    
    
    }

       throw std::invalid_argument("The line \"" + in + "\" contained a unsupported string!");
} 




uint8_t oct(uint32_t iph, const uint8_t i )
{
    if( i > 3 )
        throw std::out_of_range("'i' must be a number between 0 and 3");

    return static_cast<uint8_t>( (iph << (8 * i)) >> 24 );
}


string h2str(uint32_t iph)
{
    return (format( "%1%.%2%.%3%.%4%" )  % static_cast<uint32_t>(oct(iph, 0)) 
                                    % static_cast<uint32_t>(oct(iph, 1))
                                    % static_cast<uint32_t>(oct(iph, 2))
                                    % static_cast<uint32_t>(oct(iph, 3))).str() ;
}
