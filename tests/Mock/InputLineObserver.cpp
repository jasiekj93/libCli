#include "InputLineObserver.hpp"
#include <cstring>

using namespace Mock;

InputLineObserver::InputLineObserver(size_t size)
{
    line = new char[size + 1];
}

InputLineObserver::~InputLineObserver()
{
    delete[] line;
}

void InputLineObserver::ReceivedInputLineCallback(const char *text)
{
    std::strcpy(line, text);
}
