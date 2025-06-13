
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

TEST(InputControllerTest, ArrowLeft)
{
    char a = 'A';
    char b = 'B';
    const char expectedOutput[] = { 'A', 
        ControlChar::ESCAPE_CHAR, '[', '1', 'D', // Move cursor left
        'B', 'A', 
        ControlChar::ESCAPE_CHAR, '[', '1', 'D', // Move cursor left again
        '\0' };

    ControlSequence arrowLeft(ControlSequence::Type::ARROW_LEFT);

    InputController controller(*outputExtended, *inputObserver, *buffer);

    controller.receivedCharCallback(a);
    controller.receivedStringCallback(arrowLeft.getData());
    controller.receivedCharCallback(b);

    STRCMP_EQUAL(expectedOutput, output->line.c_str());
}

TEST(InputControllerTest, ArrowRight)
{
    char a = 'A';
    char b = 'B';
    const char expectedOutput[] = { 'A', 
        ControlChar::ESCAPE_CHAR, '[', '1', 'D', // Move cursor left
        ControlChar::ESCAPE_CHAR, '[', '1', 'C', // Move cursor right
        'B', '\0' };

    ControlSequence arrowLeft(ControlSequence::Type::ARROW_LEFT);
    ControlSequence arrowRight(ControlSequence::Type::ARROW_RIGHT);

    InputController controller(*outputExtended, *inputObserver, *buffer);

    controller.receivedCharCallback(a);
    controller.receivedStringCallback(arrowLeft.getData());
    controller.receivedStringCallback(arrowRight.getData());
    controller.receivedCharCallback(b);

    STRCMP_EQUAL(expectedOutput, output->line.c_str());
}

TEST(InputControllerTest, Home)
{
    const char text[] = "Text";
    char c = 'A';
    const char expectedOutput[] = { 'T', 'e', 'x', 't',
        ControlChar::ESCAPE_CHAR, '[', '4', 'D', // Move cursor to the beginning
        'A', 'T', 'e', 'x', 't',
        ControlChar::ESCAPE_CHAR, '[', '4', 'D', // Move cursor to the beginning again
        '\0' };

    ControlSequence home(ControlSequence::Type::HOME);

    InputController controller(*outputExtended, *inputObserver, *buffer);

    controller.receivedStringCallback(text);
    controller.receivedStringCallback(home.getData());
    controller.receivedCharCallback(c);

    STRCMP_EQUAL(expectedOutput, output->line.c_str());
}

TEST(InputControllerTest, End)
{
    const char text[] = "Text";
    char c = 'A';
    const char expectedOutput[] = { 'T', 'e', 'x', 't',
        ControlChar::ESCAPE_CHAR, '[', '4', 'D',  // Move cursor to the beginning
        ControlChar::ESCAPE_CHAR, '[', '4', 'C', // Move cursor to the end
        'A', '\0' };

    ControlSequence home(ControlSequence::Type::HOME);
    ControlSequence end(ControlSequence::Type::END);

    InputController controller(*outputExtended, *inputObserver, *buffer);

    controller.receivedStringCallback(text);
    controller.receivedStringCallback(home.getData());
    controller.receivedStringCallback(end.getData());
    controller.receivedCharCallback(c);

    STRCMP_EQUAL(expectedOutput, output->line.c_str());
}

TEST(InputControllerTest, Delete)
{
    const char text[] = "Text";
    const char expectedOutput[] = { 'T', 'e', 'x', 't',
        ControlChar::ESCAPE_CHAR, '[', '4', 'D', // Move cursor to the beginning
        ControlChar::ESCAPE_CHAR, '[', '3', '~', // Delete the first character
        'e', 'x', 't', ' ', 
        ControlChar::ESCAPE_CHAR, '[', '4', 'D', // Move cursor to the beginning again
        '\0' };

    ControlSequence deleteChar(ControlSequence::Type::DELETE);
    ControlSequence home(ControlSequence::Type::HOME);

    InputController controller(*outputExtended, *inputObserver, *buffer);

    controller.receivedStringCallback(text);
    controller.receivedStringCallback(home.getData());
    controller.receivedStringCallback(deleteChar.getData());

    STRCMP_EQUAL(expectedOutput, output->line.c_str());
}

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