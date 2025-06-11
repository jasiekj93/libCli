#pragma once

/**
 * @file Executor.hpp
 * @author Adrian Szczepanski
 * @date 10-06-2025
 */

#include <libcli/CommandObserver.hpp>
#include <libcli/Terminal.hpp>

class Executor : public cli::CommandObserver
{
public:
    explicit Executor();

    void receivedCommandCallback(const cli::model::Command&, cli::InputStream&, cli::OutputStream&) override;

    void setTerminal(const std::shared_ptr<cli::Terminal>&);

protected:
    void executeCommand(std::string_view command);

private:
    std::shared_ptr<cli::Terminal> terminal;

    cli::Terminal::TemplatesBuffer templates;
};