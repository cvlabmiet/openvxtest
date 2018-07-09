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
      engine.Run(_strcmpi(argv[1], "custom") == 0 ? DemoEngine::eAskUser : DemoEngine::eAll);
   }
   else
   {
      engine.Run(DemoEngine::eAll);
   }
   cv::destroyAllWindows();
   return 0;
}
