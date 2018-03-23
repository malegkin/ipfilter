#include "stdafx.h"

#include <tclap/CmdLine.h>

#include "IpFilter.h"
#include "version.h"

int main(int argc, char* argv[])
{
    Ip ip1("1.2.3.60");

    cout << ip1.toString();
    
    try {

        TCLAP::CmdLine cmd("Simple Hello World", ' ', getProjectVersion());
        cmd.parse( argc, argv );

    } catch (TCLAP::ArgException &e) { 

        cerr << "error: " << e.error() << " for arg " << e.argId() << endl; 

    }


    cout << "Hello, World!" << endl;
    return 0;
}
