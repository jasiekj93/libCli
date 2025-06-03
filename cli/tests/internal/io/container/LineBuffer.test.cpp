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

static constexpr size_t SIZE = 12;

TEST_GROUP(LineBufferTest)
{

};

TEST(LineBufferTest, Constructor)
{
    LineBuffer buffer(SIZE);

    CHECK_EQUAL(0, buffer.count());
    CHECK_EQUAL(0, buffer.cursor());
}

TEST(LineBufferTest, AddOneChar)
{
    LineBuffer buffer(SIZE);
    char a = 'A';

    CHECK(buffer.put(a));
    
    CHECK_EQUAL(1, buffer.count());
    CHECK_EQUAL(1, buffer.cursor()); 
    CHECK_EQUAL(a, buffer[0]);
    CHECK_EQUAL('\0', buffer[1]);
}

TEST(LineBufferTest, AddString)
{
    LineBuffer buffer(SIZE);
    char string[] = "Hello";

    CHECK(buffer.putString(string));
    
    CHECK_EQUAL(std::strlen(string), buffer.count());
    CHECK_EQUAL(std::strlen(string), buffer.cursor());
    CHECK_EQUAL('\0', buffer[std::strlen(string)]);
}

TEST(LineBufferTest, AddMoreThanSize)
{
    LineBuffer buffer(SIZE);
    char c = 'A';

    for(size_t i = 0; i < SIZE; i++)
        CHECK(buffer.put(c++));
    
    CHECK_FALSE(buffer.put(c));
    c--;
    
    CHECK_EQUAL(SIZE, buffer.count());
    CHECK_EQUAL(SIZE, buffer.cursor());
    CHECK_EQUAL(c, buffer[SIZE - 1]);
    CHECK_EQUAL('\0', buffer[SIZE])
}

TEST(LineBufferTest, Clear)
{
    LineBuffer buffer(SIZE);
    char c = 'A';

    for(size_t i = 0; i < SIZE; i++)
        buffer.put(c++);
    
    CHECK_EQUAL(SIZE, buffer.count());
    CHECK_EQUAL(SIZE, buffer.cursor());

    buffer.clear();

    CHECK_EQUAL(0, buffer.count());
    CHECK_EQUAL(0, buffer.cursor());
}

TEST(LineBufferTest, MoveCursorLeft)
{
    LineBuffer buffer(SIZE);
    char a = 'A';
    char b = 'B';

    buffer.put(a);
    CHECK(buffer.moveCursorLeft());
    buffer.put(b);

    CHECK_EQUAL(1, buffer.count());
    CHECK_EQUAL(1, buffer.cursor());
    CHECK_EQUAL(b, buffer[0]);
    CHECK_EQUAL('\0', buffer[1]);
}

TEST(LineBufferTest, MoveCursorLeft_IsEmpty)
{
    LineBuffer buffer(SIZE);

    CHECK_FALSE(buffer.moveCursorLeft());
}

TEST(LineBufferTest, MoveCursorRight)
{
    LineBuffer buffer(SIZE);
    char a = 'A';
    char b = 'B';
    char c = 'C';

    buffer.put(a);
    buffer.put(b);

    buffer.moveCursorLeft();

    CHECK(buffer.moveCursorRight());

    buffer.put(c);

    CHECK_EQUAL(3, buffer.count());
    CHECK_EQUAL(3, buffer.cursor());
    CHECK_EQUAL(c, buffer[2]);
    CHECK_EQUAL('\0', buffer[3]);
}

TEST(LineBufferTest, MoveCursorRight_IsOnTheEnd)
{
    LineBuffer buffer(SIZE);
    char a = 'A';
    char b = 'B';
    
    buffer.put(a);
    buffer.put(b);

    CHECK_FALSE(buffer.moveCursorRight());
}

TEST(LineBufferTest, remove)
{
    LineBuffer buffer(SIZE);
    char a = 'A';
    char b = 'B';
    
    buffer.put(a);
    buffer.put(b);
    buffer.moveCursorLeft();

    CHECK(buffer.remove());
    CHECK_EQUAL(1, buffer.count());
    CHECK_EQUAL(1, buffer.cursor());
    CHECK_EQUAL(a, buffer[0]);
    CHECK_EQUAL('\0', buffer[1]);
}

TEST(LineBufferTest, remove_InTheMiddle)
{
    LineBuffer buffer(SIZE);
    char a = 'A';
    char b = 'B';
    char c = 'C';
    
    buffer.put(a);
    buffer.put(b);
    buffer.put(c);
    buffer.moveCursorLeft();
    buffer.moveCursorLeft();

    CHECK(buffer.remove());
    CHECK_EQUAL(2, buffer.count());
    CHECK_EQUAL(1, buffer.cursor());
    CHECK_EQUAL(a, buffer[0]);
    CHECK_EQUAL(c, buffer[1]);
    CHECK_EQUAL('\0', buffer[2]);
}

TEST(LineBufferTest, remove_OneChar)
{
    LineBuffer buffer(SIZE);
    char a = 'A';
    
    buffer.put(a);
    buffer.moveCursorLeft();

    CHECK(buffer.remove());
    CHECK_EQUAL(0, buffer.count());
    CHECK_EQUAL(0, buffer.cursor());
    CHECK_EQUAL('\0', buffer[0]);
}

TEST(LineBufferTest, IsEmpty)
{
    LineBuffer buffer(SIZE);
    
    CHECK_FALSE(buffer.remove());
}

TEST(LineBufferTest, remove_OnTheEnd)
{
    LineBuffer buffer(SIZE);
    char a = 'A';
    
    buffer.put(a);
    CHECK_FALSE(buffer.remove());
}

TEST(LineBufferTest, MoveCursorMaxLeft)
{
    const char text[] = "0123456789";
    LineBuffer buffer(SIZE);
    
    buffer.putString(text);
    CHECK_EQUAL(9, buffer.moveCursorMaxLeft());
    CHECK_EQUAL(1, buffer.cursor());
    CHECK_EQUAL(1, buffer.moveCursorMaxLeft());
    CHECK_EQUAL(0, buffer.cursor());
    CHECK_EQUAL(0, buffer.moveCursorMaxLeft());
}

TEST(LineBufferTest, MoveCursorMaxRight)
{
    const char text[] = "0123456789";
    LineBuffer buffer(SIZE);
    
    buffer.putString(text);
    buffer.moveCursorMaxLeft();
    buffer.moveCursorMaxLeft();

    CHECK_EQUAL(9, buffer.moveCursorMaxRight());
    CHECK_EQUAL(9, buffer.cursor());
    CHECK_EQUAL(1, buffer.moveCursorMaxRight());
    CHECK_EQUAL(10, buffer.cursor());
    CHECK_EQUAL(0, buffer.moveCursorMaxRight());
}