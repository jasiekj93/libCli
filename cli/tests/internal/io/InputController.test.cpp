
/**
 * @file InputController.test.cpp
 * @author Adrian Szczepanski
 * @date 23-07-2021
 * @brief 
 * @details
 */

#include <libcli/internal/io/InputController.hpp>
#include <tests/mock/InputLineObserver.hpp>
#include <tests/mock/OutputController.hpp>
#include <cstring>

#include <CppUTest/CommandLineTestRunner.h>

using namespace cli::internal::io;

static constexpr size_t SIZE = 5;
static constexpr size_t DEPTH = 3;

mock::InputLineObserver *inputObserver;
mock::OutputController *output;
container::LineBufferWithMemory *buffer;

TEST_GROUP(InputControllerTest)
{
    void setup()
    {
        inputObserver = new mock::InputLineObserver(SIZE);
        output = new mock::OutputController(SIZE);
        buffer = new container::LineBufferWithMemory(SIZE, DEPTH);
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

    CHECK_EQUAL(0, buffer->count());
    CHECK_EQUAL(0, output->line.count());
}

// TEST(InputControllerTest, ArrowLeft)
// {
//     char a = 'A';
//     char b = 'B';

//     ControlSequence arrowLeft(ControlSequence::Type::ArrowLeft);

//     InputController controller(*output, *inputObserver, *buffer);

//     controller.ReceivedCharCallback(a);
//     controller.ReceivedStringCallback(arrowLeft.Data());
//     controller.ReceivedCharCallback(b);

//     CHECK_EQUAL(b, (*buffer)[0]);
//     CHECK_EQUAL(b, output->line[0]);
// }

// TEST(InputControllerTest, ArrowRight)
// {
//     char a = 'A';
//     char b = 'B';

//     ControlSequence arrowLeft(ControlSequence::Type::ArrowLeft);
//     ControlSequence arrowRight(ControlSequence::Type::ArrowRight);

//     InputController controller(*output, *inputObserver, *buffer);

//     controller.ReceivedCharCallback(a);
//     controller.ReceivedStringCallback(arrowLeft.Data());
//     controller.ReceivedStringCallback(arrowRight.Data());
//     controller.ReceivedCharCallback(b);

//     CHECK_EQUAL(b, (*buffer)[1]);
//     CHECK_EQUAL(b, output->line[1]);
// }

// TEST(InputControllerTest, Home)
// {
//     const char expected[] = "Aext";
//     const char text[] = "Text";
//     char c = 'A';

//     ControlSequence home(ControlSequence::Type::Home);

//     InputController controller(*output, *inputObserver, *buffer);

//     controller.ReceivedStringCallback(text);
//     controller.ReceivedStringCallback(home.Data());
//     controller.ReceivedCharCallback(c);

//     STRCMP_EQUAL(expected, buffer->Data());
//     STRCMP_EQUAL(expected, output->line.Data());
// }

// TEST(InputControllerTest, End)
// {
//     const char expected[] = "TextA";
//     const char text[] = "Text";
//     char c = 'A';

//     ControlSequence home(ControlSequence::Type::Home);
//     ControlSequence end(ControlSequence::Type::End);

//     InputController controller(*output, *inputObserver, *buffer);

//     controller.ReceivedStringCallback(text);
//     controller.ReceivedStringCallback(home.Data());
//     controller.ReceivedStringCallback(end.Data());
//     controller.ReceivedCharCallback(c);

//     STRCMP_EQUAL(expected, buffer->Data());
//     STRCMP_EQUAL(expected, output->line.Data());
// }

// TEST(InputControllerTest, Delete)
// {
//     const char expected[] = "ext";
//     const char text[] = "Text";

//     ControlSequence deleteChar(ControlSequence::Type::Delete);
//     ControlSequence home(ControlSequence::Type::Home);

//     InputController controller(*output, *inputObserver, *buffer);

//     controller.ReceivedStringCallback(text);
//     controller.ReceivedStringCallback(home.Data());
//     controller.ReceivedStringCallback(deleteChar.Data());

//     STRCMP_EQUAL(expected, buffer->Data());
//     STRCMP_EQUAL(expected, output->line.Data());
// }

TEST(InputControllerTest, Backspace)
{
    const char expected[] = "Tex";
    const char text[] = "Text";

    InputController controller(*output, *inputObserver, *buffer);

    controller.ReceivedStringCallback(text);
    controller.ReceivedCharCallback(ControlChar::BACKSPACE);

    STRCMP_EQUAL(expected, buffer->data());
    STRCMP_EQUAL(expected, output->line.data());
}

TEST(InputControllerTest, Enter)
{
    const char text[] = "Text";

    InputController controller(*output, *inputObserver, *buffer);

    controller.ReceivedStringCallback(text);
    controller.ReceivedCharCallback(ControlChar::NEW_LINE);

    CHECK_EQUAL(0, buffer->count());
    CHECK_EQUAL(0, output->line.count());
    STRCMP_EQUAL(text, output->previousLine);
}

TEST(InputControllerTest, ArrowUp)
{
    const char text1[] = "Text1";
    const char text2[] = "Text2";

    ControlSequence arrowUp(ControlSequence::Type::ArrowUp);

    InputController controller(*output, *inputObserver, *buffer);

    controller.ReceivedStringCallback(text1);
    controller.ReceivedCharCallback(ControlChar::NEW_LINE);
    controller.ReceivedStringCallback(text2);
    controller.ReceivedStringCallback(arrowUp.Data());

    STRCMP_EQUAL(text1, output->previousLine);
    STRCMP_EQUAL(text1, output->line.data());
    STRCMP_EQUAL(text1, buffer->data());
}

TEST(InputControllerTest, ArrowDown)
{
    const char text1[] = "Text1";
    const char text2[] = "Text2";

    ControlSequence arrowUp(ControlSequence::Type::ArrowUp);
    ControlSequence arrowDown(ControlSequence::Type::ArrowDown);

    InputController controller(*output, *inputObserver, *buffer);

    controller.ReceivedStringCallback(text1);
    controller.ReceivedCharCallback(ControlChar::NEW_LINE);
    controller.ReceivedStringCallback(text2);
    controller.ReceivedStringCallback(arrowUp.Data());
    controller.ReceivedStringCallback(arrowDown.Data());

    STRCMP_EQUAL(text1, output->previousLine);
    STRCMP_EQUAL(text2, output->line.data());
    STRCMP_EQUAL(text2, buffer->data());
}