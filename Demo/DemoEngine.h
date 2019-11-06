//@file DemoEngine.cpp
//@brief Contains definition of the DemoEngine
//@author Roman Golovanov
//@date 23 March 2016

#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

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
        std::cout << "Execute " << ReplyName() << "...\n";
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
        eAll, // Show all demos
        eAskUser // Show demo specified by the user
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
        std::cout << "Demo Application contains " << m_demoRegistry.size() << " demos:\n";
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
            std::cout << "Please enter index of the demo to run: ";
            int index = 0;
            std::cin >> index;
            if (0 <= index && index < int(m_demoRegistry.size()))
            {
                m_demoRegistry[index]->Execute();
            }
        }
        else
        {
            std::cout << "Unable to run demo.\n";
        }
    }

private:
    ///@brief Print all demos containing in the registry
    void printRegistry() const
    {
        int index = 0;
        for (const auto& item : m_demoRegistry)
        {
            std::cout << index++ << ") " << item->ReplyName() << "\n";
        }
    }

private:
    std::vector<IDemoCasePtr> m_demoRegistry; // contains demos
};
