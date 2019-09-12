#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "application.h"
#include "ClientNetwork.h"

namespace Global
{
    extern Application* application;
    extern HNet::_ClientNetwork NetObj;
};

#endif