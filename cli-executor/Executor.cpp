#include "Executor.hpp"
#include <cstdio>  // For popen and fgets
#include <memory>  // For std::shared_ptr
#include <string>  // For std::string

static std::string replaceNewlineWithCarriageReturn(std::string input);

Executor::Executor()
    : terminal(nullptr)
{
    templates["pwd"] = cli::templates::Command("pwd", "Print working directory");
    templates["whoami"] = cli::templates::Command("whoami", "Print current user name");
    templates["clear"] = cli::templates::Command("clear", "Clear the terminal screen");
    templates["ls"] = cli::templates::Command("ls", "List directory contents", {
         { 'l', { cli::model::Argument::Type::EMPTY, false } },
         { 'a', { cli::model::Argument::Type::EMPTY, false } }
    });
    templates["ps"] = cli::templates::Command("ps", "Report a snapshot of current processes", {
         { 'a', { cli::model::Argument::Type::EMPTY, false } },
         { 'u', { cli::model::Argument::Type::EMPTY, false } },
         { 'x', { cli::model::Argument::Type::EMPTY, false } }
    });
}

void Executor::receivedCommandCallback(const cli::model::Command& command)
{
    std::string cmd = command.getName().data();
    cmd += ' ';

    for(auto arg : command.getArguments())
    {
        cmd += "-";
        cmd += arg.first;
        cmd += ' ';
    }

    executeCommand(cmd);
}

void Executor::setTerminal(const std::shared_ptr<cli::Terminal>& term)
{
    terminal = term;
    terminal->templates() = templates;  // Set the command templates in the terminal
}

void Executor::executeCommand(std::string_view command)
{
    FILE* pipe = popen(command.data(), "r");

    if (not pipe)
    {
        terminal->putString("Failed to execute command\r\n");
        return;
    }

    char buffer[2048];
    std::string result;
    int counter = 0;

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
    {
        result += buffer;
        counter++;
    }

    pclose(pipe);

    result = replaceNewlineWithCarriageReturn(result);
    terminal->putString(result.data());
}

static std::string replaceNewlineWithCarriageReturn(std::string input)
{
    size_t pos = 0;
    const std::string from = "\n";
    const std::string to = "\r\n";

    while ((pos = input.find(from, pos)) != std::string::npos)
    {
        input.replace(pos, from.length(), to);
        pos += to.length(); // Move past the replacement
    }

    return input;
}
