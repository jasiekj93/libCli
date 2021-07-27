/**
 * @file StringCircularLifo.test.cpp
 * @author Adrian Szczepanski
 * @date 23-07-2021
 * @brief 
 * @details
 */

#include <libCli/Utils/StringCircularLifo.hpp>

#include <CppUTest/CommandLineTestRunner.h>

using namespace Cli::Utils;

static constexpr size_t SIZE = 10;
static constexpr size_t DEPTH = 3;

TEST_GROUP(StringCircularLifoTest)
{

};

TEST(StringCircularLifoTest, Constructor)
{
    StringCircularLifo queue(SIZE, DEPTH);

    CHECK_EQUAL(0, queue.Count());
    CHECK(nullptr == queue.Get(0));
}

TEST(StringCircularLifoTest, Push_One)
{
    StringCircularLifo queue(SIZE, DEPTH);
    const char * text = "Hello";

    CHECK(queue.Push(text));

    CHECK_EQUAL(1, queue.Count());
    STRCMP_EQUAL(text, queue.Get(0));
    CHECK(nullptr == queue.Get(1));
}

TEST(StringCircularLifoTest, Push_TooBig)
{
    StringCircularLifo queue(SIZE, DEPTH);
    const char * text = "Very Big Hello";

    CHECK_FALSE(queue.Push(text));

    CHECK_EQUAL(0, queue.Count());
    CHECK(nullptr == queue.Get(0));
}

TEST(StringCircularLifoTest, Push_MoreThanDepth)
{
    StringCircularLifo queue(SIZE, DEPTH);
    const char * texts[] = { 
        "Hello",
        "How",
        "Are",
        "You"
    };

    for(size_t i = 0; i < (DEPTH + 1); i++)
        CHECK(queue.Push(texts[i]));

    CHECK_EQUAL(DEPTH, queue.Count());
    STRCMP_EQUAL(texts[3], queue.Get(0));
    STRCMP_EQUAL(texts[2], queue.Get(1));
    STRCMP_EQUAL(texts[1], queue.Get(2));
}

TEST(StringCircularLifoTest, Push_OverwriteTwoTimes)
{
    StringCircularLifo queue(SIZE, DEPTH);
    const char * texts[] = { 
        "Hello",
        "How",
        "Are",
        "You",
        "Must",
        "Be"
    };

    for(size_t i = 0; i < (2 * DEPTH); i++)
        CHECK(queue.Push(texts[i]));

    CHECK_EQUAL(DEPTH, queue.Count());
    STRCMP_EQUAL(texts[5], queue.Get(0));
    STRCMP_EQUAL(texts[4], queue.Get(1));
    STRCMP_EQUAL(texts[3], queue.Get(2));
}