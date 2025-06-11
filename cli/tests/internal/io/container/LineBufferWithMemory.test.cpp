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

TEST_GROUP(LineBufferWithMemoryTest)
{
};

TEST(LineBufferWithMemoryTest, Constructor)
{
    LineBufferWithMemory buffer;

    CHECK_EQUAL(0, buffer.getCount());
    CHECK_EQUAL(0, buffer.getCursor());
}

TEST(LineBufferWithMemoryTest, AddSecond_IsTheSame)
{
    LineBufferWithMemory buffer;

    const char string[] = "aa";

    buffer.push(string);
    buffer.clearAndMemorize();
    buffer.push(string);

    CHECK_EQUAL(1, buffer.memoryCount());
}

TEST(LineBufferWithMemoryTest, SetPrevious)
{
    LineBufferWithMemory buffer;

    const char * strings[] =
    {
        "aa",
        "bbb"
    };

    buffer.push(strings[0]);
    buffer.clearAndMemorize();
    buffer.push(strings[1]);

    CHECK_EQUAL(1, buffer.memoryCount());
    STRCMP_EQUAL(strings[1], buffer.getData().c_str());
    CHECK_EQUAL(std::strlen(strings[1]), buffer.getCursor());
    CHECK_EQUAL(std::strlen(strings[1]), buffer.getCount());

    CHECK(buffer.setPrevious());
    STRCMP_EQUAL(strings[0], buffer.getData().c_str());
    CHECK_EQUAL(std::strlen(strings[0]), buffer.getCursor());
    CHECK_EQUAL(std::strlen(strings[0]), buffer.getCount());
}

TEST(LineBufferWithMemoryTest, SetPrevious_NoPrevious)
{
    LineBufferWithMemory buffer;

    const char * strings[] =
    {
        "foo",
        "bar"
    };

    buffer.push(strings[0]);

    CHECK_FALSE(buffer.setPrevious());
}

TEST(LineBufferWithMemoryTest, SetNext)
{
    LineBufferWithMemory buffer;

    const char * strings[] =
    {
        "foo",
        "bar"
    };

    buffer.push(strings[0]);
    buffer.clearAndMemorize();
    buffer.push(strings[1]);

    CHECK(buffer.setPrevious());
    CHECK(buffer.setNext());
    STRCMP_EQUAL(strings[1], buffer.getData().c_str());
}

TEST(LineBufferWithMemoryTest, SetCurrent)
{
    LineBufferWithMemory buffer;

    const char * strings[] =
    {
        "foo",
        "bar",
        "baz"
    };

    buffer.push(strings[0]);
    buffer.clearAndMemorize();
    buffer.push(strings[1]);
    buffer.clearAndMemorize();
    buffer.push(strings[2]);

    CHECK_EQUAL(2, buffer.memoryCount());
    buffer.setPrevious();
    buffer.setPrevious();
    STRCMP_EQUAL(strings[0], buffer.getData().c_str());

    buffer.setCurrent();

    STRCMP_EQUAL(strings[2], buffer.getData().c_str());
}