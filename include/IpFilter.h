#pragma once
#include "stdafx.h"

#include <regex>
#include <numeric>
#include <iostream>
#include <sstream>

typedef vector<uint8_t> octs_t;

struct  Ip {

    //in: string with ip address
    Ip(const string& ip_);

    //in: index of octet [0-3]
    //return: octet of ip address by index
    uint8_t operator[](int i);

    //return: a transmitted to constructor ip address ad string
    const string str();

    //return: a ip address as string  CONSTRUCTED of parsed octets
    const string toString();

    uint32_t getHashCode() const {
        return hashCode;
    }


    bool operator< (const Ip& right) const {
        return getHashCode() < right.getHashCode();
    }    

    bool operator> (const Ip& right) const {
        return getHashCode() > right.getHashCode();
    }    
    

private:

    string ip;
    uint32_t hashCode;
    octs_t octs;

    Ip();

    static const octs_t ip2octs(const string& ip );
};


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


struct IpPool {
    
    IpPool(istream & ins)
    {
        std::transform(getline_iterator(ins), getline_iterator(), inserter(ips, begin(ips)), [](auto line){
            return getFirstColumnFromTsvLine(line);
        } );
        
        sort(begin(ips), end(ips));
        copy(begin(ips), end(ips), back_insert_iterator<vector<Ip>>(sorted_ips));
    }
    
    const vector<Ip>& getInverseSortedIps(){
        return sorted_ips;
    }

    template< class UnaryPredicate >
    vector<Ip> getFilteredInvereseSortedIps(UnaryPredicate pred){
        vector<Ip> out;
        copy_if( begin(sorted_ips), end(sorted_ips),  back_insert_iterator<vector<Ip>>(out), pred);
        return out;
    }

private:

    vector<Ip> ips;
//    set<Ip, std::greater<Ip>> ips;
    vector<Ip> sorted_ips;  

    static const string getFirstColumnFromTsvLine(const string &);       
};
