#include "stdafx.h"

#include <cstdlib>

#include "IpFilter.h"
#include "version.h"


void printVector(const vector<Ip>& in){
    cout << accumulate(begin(in), end(in), string(), [](string s, Ip ip) {
        return s + "\n" +  ip.toString();
   });
}


int main(int argc, char* argv[])
{

    IpPool ips(cin);

    printVector( ips.getInverseSortedIps() );    

    //Сразу продолжается список адресов первый байт которых равен 1.
    printVector( ips.getFilteredInvereseSortedIps( [](Ip ip) { 
        return (static_cast<uint32_t>(ip[0]) ) == 1 ;} 
    ));

    //Сразу продолжается список адресов первый байт которых равен 46, а второй 70.    
    printVector( ips.getFilteredInvereseSortedIps( [](Ip ip) {
        return ip[0] == 46 && ip[1] == 70 ;} 
    ));

    //Сразу продолжается список адресов любой байт которых равен 46.
    printVector( ips.getFilteredInvereseSortedIps( [](Ip ip) { 
        return ip[0] == 46 || ip[1] == 46 || ip[2] == 46 || ip[3] == 46;} 
    ));

    return 0;
}
