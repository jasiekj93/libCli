/**
 * @file LineBufferWithMemory.test.cpp
 * @author Adrian Szczepanski
 * @date 26-07-2021
 * @brief 
 * @details
 */

#include <libcli/internal/io/container/LineBufferWithMemory.hpp>
#include <cstring>

#include <CppUTest/CommandLineTestRunner.h>

using namespace cli::internal::io::container;

static constexpr size_t SIZE = 5;
static constexpr size_t DEPTH = 3;

TEST_GROUP(LineBufferWithMemoryTest)
{

};

TEST(LineBufferWithMemoryTest, Constructor)
{
    LineBufferWithMemory buffer(SIZE, DEPTH);

    CHECK_EQUAL(0, buffer.count());
    CHECK_EQUAL(0, buffer.cursor());
}

TEST(LineBufferWithMemoryTest, AddSecond_IsTheSame)
{
    LineBufferWithMemory buffer(SIZE, DEPTH);

    const char string[] = "aa";

    buffer.putString(string);
    buffer.clearAndMemorize();
    buffer.putString(string);

    CHECK_EQUAL(1, buffer.memoryCount());
}

TEST(LineBufferWithMemoryTest, SetPrevious)
{
    LineBufferWithMemory buffer(SIZE, DEPTH);

    const char * strings[] =
    {
        "aa",
        "bbb"
    };

    buffer.putString(strings[0]);
    buffer.clearAndMemorize();
    buffer.putString(strings[1]);

    CHECK_EQUAL(1, buffer.memoryCount());
    STRCMP_EQUAL(strings[1], buffer.data());
    CHECK_EQUAL(std::strlen(strings[1]), buffer.cursor());
    CHECK_EQUAL(std::strlen(strings[1]), buffer.count());

    CHECK(buffer.setPrevious());
    STRCMP_EQUAL(strings[0], buffer.data());
    CHECK_EQUAL(std::strlen(strings[0]), buffer.cursor());
    CHECK_EQUAL(std::strlen(strings[0]), buffer.count());
}

TEST(LineBufferWithMemoryTest, SetPrevious_NoPrevious)
{
    LineBufferWithMemory buffer(SIZE, DEPTH);

    const char * strings[] =
    {
        "foo",
        "bar"
    };

    buffer.putString(strings[0]);

    CHECK_FALSE(buffer.setPrevious());
}

TEST(LineBufferWithMemoryTest, SetNext)
{
    LineBufferWithMemory buffer(SIZE, DEPTH);

    const char * strings[] =
    {
        "foo",
        "bar"
    };

    buffer.putString(strings[0]);
    buffer.clearAndMemorize();
    buffer.putString(strings[1]);

    CHECK(buffer.setPrevious());
    CHECK(buffer.setNext());
    STRCMP_EQUAL(strings[1], buffer.data());
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

    buffer.putString(strings[0]);
    buffer.clearAndMemorize();
    buffer.putString(strings[1]);
    buffer.clearAndMemorize();
    buffer.putString(strings[2]);

    CHECK_EQUAL(2, buffer.memoryCount());
    buffer.setPrevious();
    buffer.setPrevious();
    STRCMP_EQUAL(strings[0], buffer.data());

    buffer.setCurrent();

    STRCMP_EQUAL(strings[2], buffer.data());
}