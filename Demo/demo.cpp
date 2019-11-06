//@file demo.cpp
//@brief Entry point of the Demo Application
//@author Roman Golovanov
//@date 23 March 2016

#include "DemoEngine.h"

int main(int argc, char* argv[])
{
    DemoEngine engine;
    if (argc > 1)
    {
        engine.Run(argv[1] == std::string("custom") ? DemoEngine::eAskUser : DemoEngine::eAll);
    }
    else
    {
        engine.Run(DemoEngine::eAll);
    }

    return 0;
}
