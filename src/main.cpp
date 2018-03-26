#include "stdafx.h"

#include <cstdlib>
#include <regex>
#include <map>
#include <boost/algorithm/string.hpp>

#include "foo.h"

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


void printIps(const vector<uint32_t>& ips, const map<uint32_t, string>& ips_map ){
    for (auto it = rbegin(ips); it != rend(ips); it++){
        cout << ips_map.at(*it) << endl;
    }
}

template< class UnaryPredicate >
void printFilteredIps(const vector<uint32_t>& ips, const map<uint32_t, string>& ips_map, UnaryPredicate pred ){
    vector<uint32_t> filteredIps;

    copy_if(begin(ips), end(ips),  back_insert_iterator<vector<uint32_t>>(filteredIps), pred);

    printIps(filteredIps, ips_map);
}

int main()
{
    vector< uint32_t > ips;
    map< uint32_t, string > ips_map;

    std::transform( getline_iterator( cin ), getline_iterator(), inserter( ips, begin(ips) ), [&](string line){
            auto t = s2IpHash( line );
            
            uint32_t iph = get<0>(t);
            ips_map[ iph ] = get<1>(t); 
            
            return iph;
        } );

    sort(begin(ips), end(ips));
   
    printIps(ips, ips_map);
 
    printFilteredIps( ips, ips_map, [](auto iph) { 
        return (oct(iph, 0) ) == 1 ;
    });

    //Сразу продолжается список адресов первый байт которых равен 46, а второй 70.    
    printFilteredIps( ips, ips_map, [](auto iph) {
        return oct(iph, 0) == 46 && oct(iph, 1) == 70 ; 
    });

    //Сразу продолжается список адресов любой байт которых равен 46.
    printFilteredIps( ips, ips_map, [](auto iph) {
        return oct(iph, 0) == 46 || oct(iph, 1) == 46 || oct(iph, 2) == 46 || oct(iph, 3) == 46; 
    });
    return 0;
}
