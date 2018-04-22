#include "stdafx.h"
#include "foo.h"

int main()
{
    for (auto ip: process( cin )){
        cout << to_string(ip) << endl;       
    }

    return 0;
}
