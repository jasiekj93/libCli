/**
 * @file StringCircularLifo.test.cpp
 * @author Adrian Szczepanski
 * @date 23-07-2021
 * @brief 
 * @details
 */

#include <libcli/internal/io/container/StringCircularLifo.hpp>

#include <CppUTest/CommandLineTestRunner.h>

using namespace cli::internal::io::container;

static constexpr size_t SIZE = 10;
static constexpr size_t DEPTH = 3;

TEST_GROUP(StringCircularLifoTest)
{

};

TEST(StringCircularLifoTest, Constructor)
{
    StringCircularLifo queue(SIZE, DEPTH);

    CHECK_EQUAL(0, queue.count());
    CHECK(nullptr == queue.get(0));
}

TEST(StringCircularLifoTest, push_One)
{
    StringCircularLifo queue(SIZE, DEPTH);
    const char * text = "Hello";

    CHECK(queue.push(text));

    CHECK_EQUAL(1, queue.count());
    STRCMP_EQUAL(text, queue.get(0));
    CHECK(nullptr == queue.get(1));
}

TEST(StringCircularLifoTest, push_TooBig)
{
    StringCircularLifo queue(SIZE, DEPTH);
    const char * text = "Very Big Hello";

    CHECK_FALSE(queue.push(text));

    CHECK_EQUAL(0, queue.count());
    CHECK(nullptr == queue.get(0));
}

TEST(StringCircularLifoTest, push_MoreThanDepth)
{
    StringCircularLifo queue(SIZE, DEPTH);
    const char * texts[] = { 
        "Hello",
        "How",
        "Are",
        "You"
    };

    for(size_t i = 0; i < (DEPTH + 1); i++)
        CHECK(queue.push(texts[i]));

    CHECK_EQUAL(DEPTH, queue.count());
    STRCMP_EQUAL(texts[3], queue.get(0));
    STRCMP_EQUAL(texts[2], queue.get(1));
    STRCMP_EQUAL(texts[1], queue.get(2));
}

TEST(StringCircularLifoTest, push_OverwriteTwoTimes)
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
        CHECK(queue.push(texts[i]));

    CHECK_EQUAL(DEPTH, queue.count());
    STRCMP_EQUAL(texts[5], queue.get(0));
    STRCMP_EQUAL(texts[4], queue.get(1));
    STRCMP_EQUAL(texts[3], queue.get(2));
}