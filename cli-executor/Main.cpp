/**
 * @file Main.cpp
 * @author Adrian Szczepanski
 * @date 2025-06-10
 */

#include <iostream>

#include <libcli/Factory.hpp>

#include "Serial.hpp"
#include "Executor.hpp"

using namespace cli;

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        // Print usage information
        std::cerr << "Usage: " << argv[0] << " <serial-port>" << std::endl;
        return 1;
    }

    Serial serial(argv[1]);
    Executor executor; 

    auto terminal = Factory::createNewTerminal(serial, executor, "user");
    executor.setTerminal(terminal);

    while (true)
    {
        auto result = serial.read();
        std::string input(result.begin(), result.end());
        terminal->receivedStringCallback(input.c_str());
    }
    

	return 0;
}
