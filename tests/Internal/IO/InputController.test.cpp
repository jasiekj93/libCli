
/**
 * @file InputController.test.cpp
 * @author Adrian Szczepanski
 * @date 23-07-2021
 * @brief 
 * @details
 */

#include <libCli/Internal/IO/InputController.hpp>
#include <tests/Mock/InputLineObserver.hpp>
#include <tests/Mock/OutputController.hpp>
#include <cstring>

#include <CppUTest/CommandLineTestRunner.h>

using namespace Cli::Internal::IO;

static constexpr size_t SIZE = 5;
static constexpr size_t DEPTH = 3;

Mock::InputLineObserver *inputObserver;
Mock::OutputController *output;
Container::LineBufferWithMemory *buffer;

TEST_GROUP(InputControllerTest)
{
    void setup()
    {
        inputObserver = new Mock::InputLineObserver(SIZE);
        output = new Mock::OutputController(SIZE);
        buffer = new Container::LineBufferWithMemory(SIZE, DEPTH);
    }

    void teardown()
    {
        delete inputObserver;
        delete output;
        delete buffer;
    }
};

TEST(InputControllerTest, OneChar)
{   
    char c = 'A';

    InputController controller(*output, *inputObserver, *buffer);

    controller.ReceivedCharCallback(c);

    CHECK_EQUAL(c, (*buffer)[0]);
    CHECK_EQUAL(c, output->line[0]);
}

TEST(InputControllerTest, OneChar_NotPrintable)
{
    char c = '\t';

    InputController controller(*output, *inputObserver, *buffer);

    controller.ReceivedCharCallback(c);

    CHECK_EQUAL(0, buffer->Count());
    CHECK_EQUAL(0, output->line.Count());
}

TEST(InputControllerTest, ArrowLeft)
{
    char a = 'A';
    char b = 'B';

    ControlChar arrowLeft(ControlChar::Type::ArrowLeft);

    InputController controller(*output, *inputObserver, *buffer);

    controller.ReceivedCharCallback(a);
    controller.ReceivedStringCallback(arrowLeft.Data());
    controller.ReceivedCharCallback(b);

    CHECK_EQUAL(b, (*buffer)[0]);
    CHECK_EQUAL(b, output->line[0]);
}

TEST(InputControllerTest, ArrowRight)
{
    char a = 'A';
    char b = 'B';

    ControlChar arrowLeft(ControlChar::Type::ArrowLeft);
    ControlChar arrowRight(ControlChar::Type::ArrowRight);

    InputController controller(*output, *inputObserver, *buffer);

    controller.ReceivedCharCallback(a);
    controller.ReceivedStringCallback(arrowLeft.Data());
    controller.ReceivedStringCallback(arrowRight.Data());
    controller.ReceivedCharCallback(b);

    CHECK_EQUAL(b, (*buffer)[1]);
    CHECK_EQUAL(b, output->line[1]);
}

TEST(InputControllerTest, Home)
{
    const char expected[] = "Aext";
    const char text[] = "Text";
    char c = 'A';

    ControlChar home(ControlChar::Type::Home);

    InputController controller(*output, *inputObserver, *buffer);

    controller.ReceivedStringCallback(text);
    controller.ReceivedStringCallback(home.Data());
    controller.ReceivedCharCallback(c);

    STRCMP_EQUAL(expected, buffer->Data());
    STRCMP_EQUAL(expected, output->line.Data());
}

TEST(InputControllerTest, End)
{
    const char expected[] = "TextA";
    const char text[] = "Text";
    char c = 'A';

    ControlChar home(ControlChar::Type::Home);
    ControlChar end(ControlChar::Type::End);

    InputController controller(*output, *inputObserver, *buffer);

    controller.ReceivedStringCallback(text);
    controller.ReceivedStringCallback(home.Data());
    controller.ReceivedStringCallback(end.Data());
    controller.ReceivedCharCallback(c);

    STRCMP_EQUAL(expected, buffer->Data());
    STRCMP_EQUAL(expected, output->line.Data());
}

TEST(InputControllerTest, Delete)
{
    const char expected[] = "ext";
    const char text[] = "Text";

    ControlChar deleteChar(ControlChar::Type::Delete);
    ControlChar home(ControlChar::Type::Home);

    InputController controller(*output, *inputObserver, *buffer);

    controller.ReceivedStringCallback(text);
    controller.ReceivedStringCallback(home.Data());
    controller.ReceivedStringCallback(deleteChar.Data());

    STRCMP_EQUAL(expected, buffer->Data());
    STRCMP_EQUAL(expected, output->line.Data());
}

TEST(InputControllerTest, Backspace)
{
    const char expected[] = "Tex";
    const char text[] = "Text";

    char backspace = '\b';

    InputController controller(*output, *inputObserver, *buffer);

    controller.ReceivedStringCallback(text);
    controller.ReceivedCharCallback(backspace);

    STRCMP_EQUAL(expected, buffer->Data());
    STRCMP_EQUAL(expected, output->line.Data());
}

TEST(InputControllerTest, Enter)
{
    const char text[] = "Text";
    char enter = '\n';

    InputController controller(*output, *inputObserver, *buffer);

    controller.ReceivedStringCallback(text);
    controller.ReceivedCharCallback(enter);

    CHECK_EQUAL(0, buffer->Count());
    CHECK_EQUAL(0, output->line.Count());
    STRCMP_EQUAL(text, output->previousLine);
}

TEST(InputControllerTest, ArrowUp)
{
    const char text1[] = "Text1";
    const char text2[] = "Text2";
    char enter = '\n';
    ControlChar arrowUp(ControlChar::Type::ArrowUp);

    InputController controller(*output, *inputObserver, *buffer);

    controller.ReceivedStringCallback(text1);
    controller.ReceivedCharCallback(enter);
    controller.ReceivedStringCallback(text2);
    controller.ReceivedStringCallback(arrowUp.Data());

    STRCMP_EQUAL(text1, output->previousLine);
    STRCMP_EQUAL(text1, output->line.Data());
    STRCMP_EQUAL(text1, buffer->Data());
}

TEST(InputControllerTest, ArrowDown)
{
    const char text1[] = "Text1";
    const char text2[] = "Text2";
    char enter = '\n';
    ControlChar arrowUp(ControlChar::Type::ArrowUp);
    ControlChar arrowDown(ControlChar::Type::ArrowDown);

    InputController controller(*output, *inputObserver, *buffer);

    controller.ReceivedStringCallback(text1);
    controller.ReceivedCharCallback(enter);
    controller.ReceivedStringCallback(text2);
    controller.ReceivedStringCallback(arrowUp.Data());
    controller.ReceivedStringCallback(arrowDown.Data());

    STRCMP_EQUAL(text1, output->previousLine);
    STRCMP_EQUAL(text2, output->line.Data());
    STRCMP_EQUAL(text2, buffer->Data());
}