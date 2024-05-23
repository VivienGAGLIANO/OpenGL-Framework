#include "application.h"


int main()
{
    auto app = std::make_unique<Application>();
    app->start();

    return 0;
}