#include "InputLineObserver.hpp"
#include <cstring>

using namespace mock;

InputLineObserver::InputLineObserver(size_t size)
{
    line = new char[size + 1];
}

InputLineObserver::~InputLineObserver()
{
    delete[] line;
}

void InputLineObserver::receivedInputLineCallback(const char *text)
{
    std::strcpy(line, text);
}
