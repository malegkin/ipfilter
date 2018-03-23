#include <iostream>
#include "stdafx.h"

#include "version.h"

int getProjectBuildNumber()
{
	return PROJECT_BUILD_NUMBER;
}

std::string getProjectVersion()
{
    return PROJECT_VERSION;
}
