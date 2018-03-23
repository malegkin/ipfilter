#pragma once
#include "stdafx.h"

#include <regex>
#include <numeric>

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


private:
//    typedef vector<uint8_t>  octs_t;

    string ip;
    octs_t octs;


    Ip();

    static const octs_t ip2octs(const string& ip );
};



