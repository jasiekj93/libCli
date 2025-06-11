#include "OutputControllerImpl.hpp"
#include <libcli/internal/io/ControlSequence.hpp>
#include <libcli/internal/io/ControlChar.hpp>

using namespace cli;
using namespace cli::internal;
using namespace cli::internal::io;

OutputControllerImpl::OutputControllerImpl(Output& output)
    : output(output)
{
}

OutputController& OutputControllerImpl::operator<<(char c)
{
    output.write(c);
    return *this;
}

OutputController& OutputControllerImpl::operator<<(etl::string_view string)
{
    output.write(string);
    return *this;
}

OutputController& OutputControllerImpl::operator<<(const formatspec::Base& format)
{
    switch (format.type) 
    {
    case formatspec::Type::NEW_LINE:
        output.write("\r\n");
        break;
    case formatspec::Type::CLEAR_SCREEN:
        output.write('\f');
        break;
    case formatspec::Type::FLUSH:
        output.flush();
        break;
    
    default:
        break;
    }

    return *this;
}