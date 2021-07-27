/**
 * @file LineBufferWithMemory.test.cpp
 * @author Adrian Szczepanski
 * @date 26-07-2021
 * @brief 
 * @details
 */

#include <libCli/Utils/LineBufferWithMemory.hpp>
#include <cstring>

#include <CppUTest/CommandLineTestRunner.h>

using namespace Cli::Utils;

static constexpr size_t SIZE = 5;
static constexpr size_t DEPTH = 3;

TEST_GROUP(LineBufferWithMemoryTest)
{

};

TEST(LineBufferWithMemoryTest, Constructor)
{
    LineBufferWithMemory buffer(SIZE, DEPTH);

    CHECK_EQUAL(0, buffer.Count());
    CHECK_EQUAL(0, buffer.Cursor());
}

TEST(LineBufferWithMemoryTest, SetPrevious)
{
    LineBufferWithMemory buffer(SIZE, DEPTH);

    const char * strings[] =
    {
        "aa",
        "bbb"
    };

    buffer.PutString(strings[0]);
    buffer.ClearAndMemorize();
    buffer.PutString(strings[1]);

    CHECK_EQUAL(1, buffer.MemoryCount());
    STRCMP_EQUAL(strings[1], buffer.Data());
    CHECK_EQUAL(std::strlen(strings[1]), buffer.Cursor());
    CHECK_EQUAL(std::strlen(strings[1]), buffer.Count());

    CHECK(buffer.SetPrevious());
    STRCMP_EQUAL(strings[0], buffer.Data());
    CHECK_EQUAL(std::strlen(strings[0]), buffer.Cursor());
    CHECK_EQUAL(std::strlen(strings[0]), buffer.Count());
}

TEST(LineBufferWithMemoryTest, SetPrevious_NoPrevious)
{
    LineBufferWithMemory buffer(SIZE, DEPTH);

    const char * strings[] =
    {
        "foo",
        "bar"
    };

    buffer.PutString(strings[0]);

    CHECK_FALSE(buffer.SetPrevious());
}

TEST(LineBufferWithMemoryTest, SetNext)
{
    LineBufferWithMemory buffer(SIZE, DEPTH);

    const char * strings[] =
    {
        "foo",
        "bar"
    };

    buffer.PutString(strings[0]);
    buffer.ClearAndMemorize();
    buffer.PutString(strings[1]);

    CHECK(buffer.SetPrevious());
    CHECK(buffer.SetNext());
    STRCMP_EQUAL(strings[1], buffer.Data());
}

TEST(LineBufferWithMemoryTest, SetCurrent)
{
    LineBufferWithMemory buffer(SIZE, DEPTH);

    const char * strings[] =
    {
        "foo",
        "bar",
        "baz"
    };

    buffer.PutString(strings[0]);
    buffer.ClearAndMemorize();
    buffer.PutString(strings[1]);
    buffer.ClearAndMemorize();
    buffer.PutString(strings[2]);

    CHECK_EQUAL(2, buffer.MemoryCount());
    buffer.SetPrevious();
    buffer.SetPrevious();
    STRCMP_EQUAL(strings[0], buffer.Data());

    buffer.SetCurrent();

    STRCMP_EQUAL(strings[2], buffer.Data());
}