/**
 * @file LineBuffer.test.cpp
 * @author Adrian Szczepanski
 * @date 23-07-2021
 * @brief 
 * @details
 */

#include <libCli/Utils/LineBuffer.hpp>

#include <CppUTest/CommandLineTestRunner.h>

using namespace Cli::Utils;

static constexpr size_t SIZE = 5;

TEST_GROUP(LineBufferTest)
{

};

TEST(LineBufferTest, Constructor)
{
    LineBuffer<SIZE> buffer;

    CHECK_EQUAL(0, buffer.Count());
    CHECK_EQUAL(0, buffer.Cursor());
}

TEST(LineBufferTest, AddOneChar)
{
    LineBuffer<SIZE> buffer;
    char a = 'A';

    CHECK(buffer.Put(a));
    
    CHECK_EQUAL(1, buffer.Count());
    CHECK_EQUAL(1, buffer.Cursor()); 
    CHECK_EQUAL(a, buffer[0]);
    CHECK_EQUAL('\0', buffer[1]);
}

TEST(LineBufferTest, AddString)
{
    LineBuffer<SIZE> buffer;
    char string[] = "Hello";

    CHECK(buffer.PutString(string));
    
    CHECK_EQUAL(std::strlen(string), buffer.Count());
    CHECK_EQUAL(std::strlen(string), buffer.Cursor());
    CHECK_EQUAL('\0', buffer[std::strlen(string)]);
}

TEST(LineBufferTest, AddMoreThanSize)
{
    LineBuffer<SIZE> buffer;
    char c = 'A';

    for(size_t i = 0; i < SIZE; i++)
        CHECK(buffer.Put(c++));
    
    CHECK_FALSE(buffer.Put(c));
    c--;
    
    CHECK_EQUAL(SIZE, buffer.Count());
    CHECK_EQUAL(SIZE, buffer.Cursor());
    CHECK_EQUAL(c, buffer[SIZE - 1]);
    CHECK_EQUAL('\0', buffer[SIZE])
}

TEST(LineBufferTest, Clear)
{
    LineBuffer<SIZE> buffer;
    char c = 'A';

    for(size_t i = 0; i < SIZE; i++)
        buffer.Put(c++);
    
    CHECK_EQUAL(SIZE, buffer.Count());
    CHECK_EQUAL(SIZE, buffer.Cursor());

    buffer.Clear();

    CHECK_EQUAL(0, buffer.Count());
    CHECK_EQUAL(0, buffer.Cursor());
}

TEST(LineBufferTest, MoveCursorLeft)
{
    LineBuffer<SIZE> buffer;
    char a = 'A';
    char b = 'B';

    buffer.Put(a);
    CHECK(buffer.MoveCursorLeft());
    buffer.Put(b);

    CHECK_EQUAL(1, buffer.Count());
    CHECK_EQUAL(1, buffer.Cursor());
    CHECK_EQUAL(b, buffer[0]);
    CHECK_EQUAL('\0', buffer[1]);
}

TEST(LineBufferTest, MoveCursorLeft_IsEmpty)
{
    LineBuffer<SIZE> buffer;

    CHECK_FALSE(buffer.MoveCursorLeft());
}

TEST(LineBufferTest, MoveCursorRight)
{
    LineBuffer<SIZE> buffer;
    char a = 'A';
    char b = 'B';
    char c = 'C';

    buffer.Put(a);
    buffer.Put(b);

    buffer.MoveCursorLeft();

    CHECK(buffer.MoveCursorRight());

    buffer.Put(c);

    CHECK_EQUAL(3, buffer.Count());
    CHECK_EQUAL(3, buffer.Cursor());
    CHECK_EQUAL(c, buffer[2]);
    CHECK_EQUAL('\0', buffer[3]);
}

TEST(LineBufferTest, MoveCursorRight_IsOnTheEnd)
{
    LineBuffer<SIZE> buffer;
    char a = 'A';
    char b = 'B';
    
    buffer.Put(a);
    buffer.Put(b);

    CHECK_FALSE(buffer.MoveCursorRight());
}

TEST(LineBufferTest, Delete)
{
    LineBuffer<SIZE> buffer;
    char a = 'A';
    char b = 'B';
    
    buffer.Put(a);
    buffer.Put(b);
    buffer.MoveCursorLeft();

    CHECK(buffer.Delete());
    CHECK_EQUAL(1, buffer.Count());
    CHECK_EQUAL(1, buffer.Cursor());
    CHECK_EQUAL(a, buffer[0]);
    CHECK_EQUAL('\0', buffer[1]);
}

TEST(LineBufferTest, Delete_InTheMiddle)
{
    LineBuffer<SIZE> buffer;
    char a = 'A';
    char b = 'B';
    char c = 'C';
    
    buffer.Put(a);
    buffer.Put(b);
    buffer.Put(c);
    buffer.MoveCursorLeft();
    buffer.MoveCursorLeft();

    CHECK(buffer.Delete());
    CHECK_EQUAL(2, buffer.Count());
    CHECK_EQUAL(1, buffer.Cursor());
    CHECK_EQUAL(a, buffer[0]);
    CHECK_EQUAL(c, buffer[1]);
    CHECK_EQUAL('\0', buffer[2]);
}

TEST(LineBufferTest, Delete_OneChar)
{
    LineBuffer<SIZE> buffer;
    char a = 'A';
    
    buffer.Put(a);
    buffer.MoveCursorLeft();

    CHECK(buffer.Delete());
    CHECK_EQUAL(0, buffer.Count());
    CHECK_EQUAL(0, buffer.Cursor());
    CHECK_EQUAL('\0', buffer[0]);
}

TEST(LineBufferTest, IsEmpty)
{
    LineBuffer<SIZE> buffer;
    
    CHECK_FALSE(buffer.Delete());
}

TEST(LineBufferTest, Delete_OnTheEnd)
{
    LineBuffer<SIZE> buffer;
    char a = 'A';
    
    buffer.Put(a);
    CHECK_FALSE(buffer.Delete());
}