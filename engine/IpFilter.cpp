#include "IpFilter.h"


Ip::Ip(const string& ip_)
        : ip (ip_)
        , octs(ip2octs(ip_))
{};

uint8_t Ip::operator[](int i){
    return octs[i];
}

const string Ip::str(){
    return ip;
}

const string Ip::toString(){
    return accumulate( next(begin(octs)), end(octs), to_string(octs[0]),
                        [](auto a, auto b) {
                            return a + "." + to_string(b);
                    });
}


const octs_t Ip::ip2octs(const string& ip ) {
    static const string s_octet_regex = "([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])";
    static const string s_ip_regex    = (format("^%1%\\.%1%\\.%1%\\.%1%$") % s_octet_regex).str();
    static const regex  ip_regex(s_ip_regex);

    smatch  match;

    if (!regex_search(ip, match, ip_regex)){
        throw std::invalid_argument("The string \""+ip+"\" contained an invalid ip address!");
    }

    octs_t out;
    transform( next(begin(match)), end(match), back_inserter(out), [](auto a) {
        return stoi( static_cast<string>(a) );
    });

    return out;
}




//////////////////////////
const string IpPool::getFirstColumnFromTsvLine(const string& line){

    static const regex  re( "^([0-9\\.]*)\\w" );
    
    smatch match;
    
    if (!regex_search(line, match, re)){
        throw std::invalid_argument("The line \""+line+"\" contained a unsupported string!");
    }

    return static_cast<string>(match[0]);
}
