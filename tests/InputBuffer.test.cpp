/**
 * @file InputBuffer.test.cpp
 * @author Adrian Szczepanski
 * @date 23-07-2021
 * @brief 
 * @details
 */

#include <libCli/InputBuffer.hpp>

#include <CppUTest/CommandLineTestRunner.h>

using namespace Cli;

static constexpr size_t SIZE = 5;

TEST_GROUP(InputBufferTest)
{

};

TEST(InputBufferTest, Constructor)
{
    InputBuffer<SIZE> buffer;

    CHECK_EQUAL(0, buffer.Count());
    CHECK_EQUAL(0, buffer.Cursor());
}

TEST(InputBufferTest, AddOneChar)
{
    InputBuffer<SIZE> buffer;
    char c = 'A';

    CHECK(buffer.Put(c));
    
    CHECK_EQUAL(1, buffer.Count());
    CHECK_EQUAL(1, buffer.Cursor());
    CHECK_EQUAL(c, buffer[0]);
}

TEST(InputBufferTest, AddMoreThanSize)
{
    InputBuffer<SIZE> buffer;
    char c = 'A';

    for(size_t i = 0; i < SIZE; i++)
        CHECK(buffer.Put(c++));
    
    CHECK_FALSE(buffer.Put(c));
    c--;
    
    CHECK_EQUAL(SIZE, buffer.Count());
    CHECK_EQUAL(SIZE, buffer.Cursor());
    CHECK_EQUAL(c, buffer[SIZE - 1]);
}

TEST(InputBufferTest, Clear)
{
    InputBuffer<SIZE> buffer;
    char c = 'A';

    for(size_t i = 0; i < SIZE; i++)
        buffer.Put(c++);
    
    CHECK_EQUAL(SIZE, buffer.Count());
    CHECK_EQUAL(SIZE, buffer.Cursor());

    buffer.Clear();

    CHECK_EQUAL(0, buffer.Count());
    CHECK_EQUAL(0, buffer.Cursor());
}

TEST(InputBufferTest, MoveCursorLeft)
{
    InputBuffer<SIZE> buffer;
    char a = 'A';
    char b = 'B';

    buffer.Put(a);
    CHECK(buffer.MoveCursorLeft());
    buffer.Put(b);

    CHECK_EQUAL(1, buffer.Count());
    CHECK_EQUAL(1, buffer.Cursor());
    CHECK_EQUAL(b, buffer[0]);
}

TEST(InputBufferTest, MoveCursorLeft_IsEmpty)
{
    InputBuffer<SIZE> buffer;

    CHECK_FALSE(buffer.MoveCursorLeft());
}