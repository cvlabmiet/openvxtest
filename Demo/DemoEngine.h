//@file DemoEngine.cpp
//@brief Contains definition of the DemoEngine
//@author Roman Golovanov
//@date 23 March 2016

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <stdio.h>

#include <opencv2/opencv.hpp>

///@class Defines interface of the demo
class IDemoCase
{
public:
   ///@brief dtor
   virtual ~IDemoCase() {};

   ///@brief Returns the name of the demo
   virtual std::string ReplyName() const = 0;

   ///@brief Executes demo
   void Execute()
   {
      printf("Execute %s ...\n", ReplyName().c_str());
      execute();
   }

private:
   ///@brief internal execute
   virtual void execute() = 0;
};

typedef std::unique_ptr<IDemoCase> IDemoCasePtr;

///////////////////////////////////////////////////////////////////////////////
///@brief create Thresholding demo and returns pointer to IDemoCase
IDemoCasePtr CreateThresholdingDemo();

/// TODO: add your demos here

///////////////////////////////////////////////////////////////////////////////

///@class Provide showing demo
class DemoEngine
{
public:
   enum DemoMode
   {
      eAll,		// Show all demos
      eAskUser	// Show demo specified by the user
   };
public:
   ///@brief ctor
   DemoEngine()
   {
      m_demoRegistry.push_back(CreateThresholdingDemo());
      // TODO: add your demos here
   }

   ///@brief Execute demos
   ///@param i_mode, in - demo mode
   void Run(DemoMode i_mode)
   {
      printf("Demo Application contains %d demos:\n", m_demoRegistry.size());
      printRegistry();

      if (i_mode == eAll)
      {
         for (const auto& item : m_demoRegistry)
         {
            item->Execute();
         }
      }
      else if (i_mode == eAskUser)
      {
         printf("Please enter index of the demo to run: ");
         int index = 0;
         scanf_s("%d", &index);
         if (0 <= index && index < int(m_demoRegistry.size()))
         {
            m_demoRegistry[index]->Execute();
         }
      }
      else
      {
         printf("Unable to run demo.\n");
      }
   }

private:
   ///@brief Print all demos containing in the registry
   void printRegistry() const
   {
      int index = 0;
      for (const auto& item : m_demoRegistry)
      {
         printf("%d) %s\n", index++, item->ReplyName().c_str());
      }
   }

private:
   std::vector<IDemoCasePtr> m_demoRegistry; // contains demos
};