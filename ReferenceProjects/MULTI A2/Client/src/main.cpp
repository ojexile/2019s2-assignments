#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <iostream>
#include <exception>
#include "ClientNetwork.h"
#include "application.h"

/**
* Global Namespace
*
* Mainly holds the application
* It can also hold whatever true global variables you need
*/

namespace Global
{
    Application* application;
    HNet::_ClientNetwork NetObj;
};

/**
* Applicatio Entry point
*
* Creates an application object and kicks it off.
*/
int main( int argc, char** argv_ )
{
    try
    {
        Application app;
        Global::application = &app;
        app.Start();
    }
    catch( std::exception &e )
    {
        std::cout << "Application Error: " << e.what() << std::endl;
    }
    catch( ... )
    {
        std::cout << "An unknown exception has occurred" << std::endl;
    }
    return 0;
}