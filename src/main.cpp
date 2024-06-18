#include <windows.h>

#include "application.h"


// enable optimus!
//extern "C" {
//    _declspec(dllexport) DWORD NvOptimusEnablement = 1;
//}

int main()
{
    auto app = std::make_unique<Application>();
    app->start();

    return 0;
}