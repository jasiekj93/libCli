#include "InputLineObserver.hpp"
#include <cstring>

using namespace mock;

void InputLineObserver::receivedInputLineCallback(etl::string_view text)
{
    line = text;
}
