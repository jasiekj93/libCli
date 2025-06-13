#include "Command.hpp"
#include <cstring>
#include <cctype>

using namespace cli::model;

Command::Command()
    : name("")
{

}

Command::Command(etl::string_view string)
    : Command()
{
    if( string.empty() or 
        (string.size() > Configuration::MAX_LINE_LENGTH))
        return;

    std::strcpy(buffer.data(), string.data());

    if(findName() == false)
        return;

    if(findArguments() == false)
        arguments.clear();
}

bool Command::findName()
{
    auto namePointer = std::strtok(buffer.data(), " ");    

    if(namePointer == nullptr)
        return false;

    name = namePointer;
    return true;
}

bool Command::findArguments()
{
    char * token = std::strtok(nullptr, " ");
    const char *name = nullptr; 

    while(token != nullptr)
    {
        if(hyphenCount(token) > 1)
            return false;

        if(token[0] == '-')
        {
            if(std::strlen(token) == 1)
                return false;

            if(name != nullptr)
                if(arguments.full())
                    return false;
                else
                    arguments[*name] = Argument(*name, nullptr);

            name = &token[1];

            
            if(std::strlen(token) > 2)
            {
                if(arguments.full())
                    return false;
                else
                {
                    arguments[*name] = Argument(*name, &token[2]);
                    name = nullptr;
                }
            }
        }
        else
        {
            if(name == nullptr)
                return false;
            else
            {
                if(arguments.full())
                    return false;
                else
                {
                    arguments[*name] = Argument(*name, token);
                    name = nullptr;
                }
            }
        }

        token = std::strtok(nullptr, " ");
    }

    if(name != nullptr)
    {
        if(arguments.full())
            return false;
        else
        {
            arguments[*name] = Argument(*name, nullptr);
        }

    }

    return true;
}

unsigned int Command::hyphenCount(const char *token) const
{
    unsigned int result = 0;

    while (*token != '\0')
    {
        if(*token == '-')
            result++;

        token ++;
    }
    
    return result;
}