#include "stdafx.h"

#include <cstdlib>
#include <regex>
#include <map>
#include <boost/algorithm/string.hpp>

#include "foo.h"

typedef multimap<uint32_t, string> ips_t;

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

void printIps(const ips_t& ips)
{
    for (auto it = rbegin(ips); it != rend(ips); it++){
        cout << it->second << endl;
    }
}


template< class UnaryPredicate >
void printFilteredIps(const ips_t& ips, UnaryPredicate pred ){
    ips_t filteredIps;
    
    copy_if(begin(ips), end(ips),  inserter(filteredIps, begin(filteredIps)), pred);

    printIps(filteredIps);
}


int main()
{
    ips_t ips;

    std::transform( getline_iterator( cin ), getline_iterator(), inserter( ips, begin(ips) ), [&](string line){
            auto t = s2IpHash( line );
            
            return pair<uint32_t, string>(get<0>(t), get<1>(t));
        } );
   
    printIps(ips);
 
    printFilteredIps( ips, [](auto ip) { 
        return (oct(ip.first, 0) ) == 1 ;
    });

    //Сразу продолжается список адресов первый байт которых равен 46, а второй 70.    
    printFilteredIps( ips, [](auto ip) {
        return oct(ip.first, 0) == 46 && oct(ip.first, 1) == 70 ; 
    });

    //Сразу продолжается список адресов любой байт которых равен 46.
    printFilteredIps( ips, [](auto ip) {
        return oct(ip.first, 0) == 46 || oct(ip.first, 1) == 46 || oct(ip.first, 2) == 46 || oct(ip.first, 3) == 46; 
    });

    return 0;
}
