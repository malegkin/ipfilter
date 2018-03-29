#pragma once

#include "stdafx.h"

typedef pair<uint32_t, string> ip_t;

uint8_t         ip2oct( const ip_t&   ip,   uint8_t index );
ip_t            s2ip(   const string& in );

vector< ip_t >  process( istream& stream );

string to_string(const ip_t& ip);

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

