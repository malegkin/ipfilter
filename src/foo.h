#pragma once

#include "stdafx.h"

typedef pair<uint32_t, string> ip_t;

uint8_t         ip2oct( const ip_t&   ip,   uint8_t index );
ip_t            s2ip(   const string& in );



string to_string( const ip_t& ip );


using filter_predicat_t = function< bool( const ip_t& ) >;

//все один к одному
auto FILTER_PREDICAT_0 = []( const ip_t& ) { return true; };

//Сразу продолжается список адресов первый байт которых равен 1. 
auto FILTER_PREDICAT_1 = [](const ip_t& ip) { return ip2oct(ip, 0) == 1 ; };

//Сразу продолжается список адресов первый байт которых равен 46, а второй 70.    
auto FILTER_PREDICAT_2 = [](const ip_t& ip) { return ip2oct(ip, 0) == 46 && ip2oct(ip, 1) == 70 ; };

//Сразу продолжается список адресов любой байт которых равен 46.
auto FILTER_PREDICAT_3 = [](const ip_t& ip) { return ip2oct(ip, 0) == 46 || ip2oct(ip, 1) == 46 || ip2oct(ip, 2) == 46 || ip2oct(ip, 3) == 46; };


vector< ip_t >  process( istream& stream );
vector< ip_t >  process( istream& in , const vector< filter_predicat_t >& filters );


class getline_iterator: public std::iterator<std::input_iterator_tag, std::string>
{
        std::istream* is;
        std::string line;

        void fetchline() {
            if (is && !std::getline(*is, line))
                is = 0;
        }

    public:
        getline_iterator(std::istream& is) : is(&is) {
            fetchline();
        }

        getline_iterator() : is(0)
        { }

        string operator*() {
            return line;
        }

        getline_iterator& operator++() {
            fetchline();
            return *this;
        }

        bool operator==(const getline_iterator& rhs) const {
            return (!rhs.is) == (!is);
        }

        bool operator!=(const getline_iterator& rhs) const {
            return !(rhs == *this);
        }
};

