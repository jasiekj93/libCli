/**
 * @file LineBuffer.test.cpp
 * @author Adrian Szczepanski
 * @date 23-07-2021
 * @brief 
 * @details
 */

#include <libcli/internal/io/container/LineBuffer.hpp>
#include <cstring>

#include <CppUTest/CommandLineTestRunner.h>

using namespace cli::internal::io::container;

TEST_GROUP(LineBufferTest)
{

};

TEST(LineBufferTest, Constructor)
{
    LineBuffer buffer;

    CHECK_EQUAL(0, buffer.getCount());
    CHECK_EQUAL(0, buffer.getCursor());
}

TEST(LineBufferTest, AddOneChar)
{
    LineBuffer buffer;
    char a = 'A';

    CHECK(buffer.push(a));
    
    CHECK_EQUAL(1, buffer.getCount());
    CHECK_EQUAL(1, buffer.getCursor()); 
    CHECK_EQUAL(a, buffer[0]);
    CHECK_EQUAL('\0', buffer[1]);
}

TEST(LineBufferTest, AddString)
{
    LineBuffer buffer;
    char string[] = "Hello";

    CHECK(buffer.push(string));
    
    CHECK_EQUAL(std::strlen(string), buffer.getCount());
    CHECK_EQUAL(std::strlen(string), buffer.getCursor());
    CHECK_EQUAL('\0', buffer[std::strlen(string)]);
}

TEST(LineBufferTest, AddMoreThanSize)
{
    LineBuffer buffer;
    char c = 'A';

    for(size_t i = 0; i < LineBuffer::SIZE; i++)
        CHECK(buffer.push(c++));
    
    CHECK_FALSE(buffer.push(c));
    c--;
    
    CHECK_EQUAL(LineBuffer::SIZE, buffer.getCount());
    CHECK_EQUAL(LineBuffer::SIZE, buffer.getCursor());
    CHECK_EQUAL(c, buffer[LineBuffer::SIZE - 1]);
    CHECK_EQUAL('\0', buffer[LineBuffer::SIZE])
}

TEST(LineBufferTest, Clear)
{
    LineBuffer buffer;
    char c = 'A';

    for(size_t i = 0; i < LineBuffer::SIZE; i++)
        buffer.push(c++);
    
    CHECK_EQUAL(LineBuffer::SIZE, buffer.getCount());
    CHECK_EQUAL(LineBuffer::SIZE, buffer.getCursor());

    buffer.clear();

    CHECK_EQUAL(0, buffer.getCount());
    CHECK_EQUAL(0, buffer.getCursor());
}

TEST(LineBufferTest, MoveCursorLeft)
{
    LineBuffer buffer;
    char a = 'A';
    char b = 'B';

    buffer.push(a);
    CHECK(buffer.moveCursorLeft());
    buffer.push(b);

    CHECK_EQUAL(2, buffer.getCount());
    CHECK_EQUAL(1, buffer.getCursor());
    CHECK_EQUAL(b, buffer[0]);
    CHECK_EQUAL(a, buffer[1]);
}

TEST(LineBufferTest, MoveCursorLeft_IsEmpty)
{
    LineBuffer buffer;

    CHECK_FALSE(buffer.moveCursorLeft());
}

TEST(LineBufferTest, MoveCursorRight)
{
    LineBuffer buffer;
    char a = 'A';
    char b = 'B';
    char c = 'C';

    buffer.push(a);
    buffer.push(b);

    buffer.moveCursorLeft();

    CHECK(buffer.moveCursorRight());

    buffer.push(c);

    CHECK_EQUAL(3, buffer.getCount());
    CHECK_EQUAL(3, buffer.getCursor());
    CHECK_EQUAL(c, buffer[2]);
    CHECK_EQUAL('\0', buffer[3]);
}

TEST(LineBufferTest, MoveCursorRight_IsOnTheEnd)
{
    LineBuffer buffer;
    char a = 'A';
    char b = 'B';
    
    buffer.push(a);
    buffer.push(b);

    CHECK_FALSE(buffer.moveCursorRight());
}

TEST(LineBufferTest, remove)
{
    LineBuffer buffer;
    char a = 'A';
    char b = 'B';
    
    buffer.push(a);
    buffer.push(b);
    buffer.moveCursorLeft();

    CHECK(buffer.remove());
    CHECK_EQUAL(1, buffer.getCount());
    CHECK_EQUAL(1, buffer.getCursor());
    CHECK_EQUAL(a, buffer[0]);
    CHECK_EQUAL('\0', buffer[1]);
}

TEST(LineBufferTest, remove_InTheMiddle)
{
    LineBuffer buffer;
    char a = 'A';
    char b = 'B';
    char c = 'C';
    
    buffer.push(a);
    buffer.push(b);
    buffer.push(c);
    buffer.moveCursorLeft();
    buffer.moveCursorLeft();

    CHECK(buffer.remove());
    CHECK_EQUAL(2, buffer.getCount());
    CHECK_EQUAL(1, buffer.getCursor());
    CHECK_EQUAL(a, buffer[0]);
    CHECK_EQUAL(c, buffer[1]);
    CHECK_EQUAL('\0', buffer[2]);
}

TEST(LineBufferTest, remove_OneChar)
{
    LineBuffer buffer;
    char a = 'A';
    
    buffer.push(a);
    buffer.moveCursorLeft();

    CHECK(buffer.remove());
    CHECK_EQUAL(0, buffer.getCount());
    CHECK_EQUAL(0, buffer.getCursor());
    CHECK_EQUAL('\0', buffer[0]);
}

TEST(LineBufferTest, IsEmpty)
{
    LineBuffer buffer;
    
    CHECK_FALSE(buffer.remove());
}

TEST(LineBufferTest, remove_OnTheEnd)
{
    LineBuffer buffer;
    char a = 'A';
    
    buffer.push(a);
    CHECK_FALSE(buffer.remove());
}

TEST(LineBufferTest, MoveCursorHome)
{
    const char text[] = "0123456789";
    LineBuffer buffer;
    
    buffer.push(text);
    CHECK_EQUAL(10, buffer.moveCursorHome());
    CHECK_EQUAL(0, buffer.getCursor());
    CHECK_EQUAL(0, buffer.moveCursorHome());
}

TEST(LineBufferTest, MoveCursorEnd)
{
    const char text[] = "0123456789";
    LineBuffer buffer;
    
    buffer.push(text);
    buffer.moveCursorHome();

    CHECK_EQUAL(10, buffer.moveCursorEnd());
    CHECK_EQUAL(10, buffer.getCursor());
    CHECK_EQUAL(0, buffer.moveCursorEnd());
}