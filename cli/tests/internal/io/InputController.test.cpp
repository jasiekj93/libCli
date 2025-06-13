
/**
 * @file InputController.test.cpp
 * @author Adrian Szczepanski
 * @date 23-07-2021
 * @brief 
 * @details
 */

#include <cstring>
#include <memory>

#include <libcli/internal/io/InputController.hpp>

#include <tests/mock/InputLineObserver.hpp>
#include <tests/mock/OutputStreamLarge.hpp>

#include <CppUTest/CommandLineTestRunner.h>

using namespace cli::internal::io;

TEST_GROUP(InputControllerTest)
{
    std::shared_ptr<mock::InputLineObserver> inputObserver;
    std::shared_ptr<mock::OutputStreamLarge> output;
    std::shared_ptr<OutputStreamExtended> outputExtended;
    std::shared_ptr<container::LineBufferWithMemory> buffer;

    void setup()
    {
        inputObserver = std::make_shared<mock::InputLineObserver>();
        output = std::make_shared<mock::OutputStreamLarge>();
        outputExtended = std::make_shared<OutputStreamExtended>(*output);
        buffer = std::make_shared<container::LineBufferWithMemory>();
    }

    void teardown()
    {
    }
};

TEST(InputControllerTest, OneChar)
{   
    char c = 'A';

    InputController controller(*outputExtended, *inputObserver, *buffer);

    controller.receivedCharCallback(c);

    CHECK_EQUAL(c, (*buffer)[0]);
    CHECK_EQUAL(c, output->line[0]);
}

TEST(InputControllerTest, OneChar_NotPrintable)
{
    char c = '\t';

    InputController controller(*outputExtended, *inputObserver, *buffer);

    controller.receivedCharCallback(c);

    CHECK_EQUAL(0, buffer->getCount());
    CHECK_EQUAL(0, output->line.size());
}

// TEST(InputControllerTest, ArrowLeft)
// {
//     char a = 'A';
//     char b = 'B';

//     ControlSequence arrowLeft(ControlSequence::Type::ARROW_LEFT);

//     InputController controller(*output, *inputObserver, *buffer);

//     controller.receivedCharCallback(a);
//     controller.receivedStringCallback(arrowLeft.getData());
//     controller.receivedCharCallback(b);

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

//     ControlSequence deleteChar(ControlSequence::Type::DELETE);
//     ControlSequence home(ControlSequence::Type::HOME);

//     InputController controller(*output, *inputObserver, *buffer);

//     controller.receivedStringCallback(text);
//     controller.receivedStringCallback(home.getData());
//     controller.receivedStringCallback(deleteChar.getData());

//     STRCMP_EQUAL(expected, buffer->getData().c_str());
//     STRCMP_EQUAL(expected, output->line.getData().c_str());
// }

TEST(InputControllerTest, Backspace)
{
    const char expectedOutput[] = { 'T', 'e', 'x', 't', ControlChar::BACKSPACE, '\0' }; 
    auto expectedBuffer = "Tex";
    auto text = "Text";

    InputController controller(*outputExtended, *inputObserver, *buffer);

    controller.receivedStringCallback(text);
    controller.receivedCharCallback(ControlChar::BACKSPACE);

    STRCMP_EQUAL(expectedBuffer, buffer->getData().c_str());
    STRCMP_EQUAL(expectedOutput, output->line.c_str());
}

TEST(InputControllerTest, Enter)
{
    const char expectedOutput[] = "Text\r\n";
    const char text[] = "Text";

    InputController controller(*outputExtended, *inputObserver, *buffer);

    controller.receivedStringCallback(text);
    controller.receivedCharCallback(ControlChar::NEW_LINE);

    CHECK_EQUAL(0, buffer->getCount());
    STRCMP_EQUAL(expectedOutput, output->line.c_str());
}

TEST(InputControllerTest, ArrowUp)
{
    const char text1[] = "Text1";
    const char text2[] = "Text2";
    const char expectedOutput[] = { 'T', 'e', 'x', 't', '1', '\r', '\n', 'T', 'e', 'x', 't', '2',  
        ControlChar::BACKSPACE, ControlChar::BACKSPACE, ControlChar::BACKSPACE, ControlChar::BACKSPACE, ControlChar::BACKSPACE,
        'T', 'e', 'x', 't', '1', '\0' };

    ControlSequence arrowUp(ControlSequence::Type::ARROW_UP);

    InputController controller(*outputExtended, *inputObserver, *buffer);

    controller.receivedStringCallback(text1);
    controller.receivedCharCallback(ControlChar::NEW_LINE);
    controller.receivedStringCallback(text2);
    controller.receivedStringCallback(arrowUp.getData());

    STRCMP_EQUAL(expectedOutput, output->line.c_str());
    STRCMP_EQUAL(text1, buffer->getData().c_str());
}

TEST(InputControllerTest, ArrowDown)
{
    const char text1[] = "Text1";
    const char text2[] = "Text2";
    const char expectedOutput[] = { 'T', 'e', 'x', 't', '1', '\r', '\n', 'T', 'e', 'x', 't', '2',  
        ControlChar::BACKSPACE, ControlChar::BACKSPACE, ControlChar::BACKSPACE, ControlChar::BACKSPACE, ControlChar::BACKSPACE,
        'T', 'e', 'x', 't', '1', 
        ControlChar::BACKSPACE, ControlChar::BACKSPACE, ControlChar::BACKSPACE, ControlChar::BACKSPACE, ControlChar::BACKSPACE,
        'T', 'e', 'x', 't', '2', '\0' };

    ControlSequence arrowUp(ControlSequence::Type::ARROW_UP);
    ControlSequence arrowDown(ControlSequence::Type::ARROW_DOWN);

    InputController controller(*outputExtended, *inputObserver, *buffer);

    controller.receivedStringCallback(text1);
    controller.receivedCharCallback(ControlChar::NEW_LINE);
    controller.receivedStringCallback(text2);
    controller.receivedStringCallback(arrowUp.getData());
    controller.receivedStringCallback(arrowDown.getData());

    STRCMP_EQUAL(expectedOutput, output->line.c_str());
    STRCMP_EQUAL(text2, buffer->getData().c_str());
}