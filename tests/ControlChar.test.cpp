/**
 * @file ControlChar.test.cpp
 * @author Adrian Szczepanski
 * @date 26-07-2021
 * @brief 
 * @details
 */

#include <libCli/ControlChar.hpp>

#include <CppUTest/CommandLineTestRunner.h>

using namespace Cli;


TEST_GROUP(ControlCharTest)
{

};

TEST(ControlCharTest, DefaultConstructor)
{
    ControlChar character;
}

TEST(ControlCharTest, Put)
{
    ControlChar character;
    char a = 'A';

    CHECK(character.Put(a));
    CHECK_EQUAL(1, character.Count());
    CHECK_EQUAL(a, character[0]);
    CHECK_EQUAL('\0', character[1]);
}

TEST(ControlCharTest, Put_MoreThanMaxSize)
{
    ControlChar character;
    char a = 'A';

    for(unsigned int i = 0; i < ControlChar::MAX_SIZE; i++)
        CHECK(character.Put(a));

    CHECK_FALSE(character.Put(a));

    CHECK_EQUAL(ControlChar::MAX_SIZE, character.Count());
    CHECK_EQUAL('\0', character[ControlChar::MAX_SIZE]);
}

TEST(ControlCharTest, Clear)
{
    ControlChar character;
    char a = 'A';

    character.Put(a);
    character.Clear();

    CHECK_EQUAL(0, character.Count());
    CHECK_EQUAL('\0', character[0]);

}

TEST(ControlCharTest, GetType)
{
    ControlChar arrowUp(ControlChar::Type::ArrowUp);
    ControlChar arrowDown(ControlChar::Type::ArrowDown);
    ControlChar arrowLeft(ControlChar::Type::ArrowLeft);
    ControlChar arrowRight(ControlChar::Type::ArrowRight);
    ControlChar deleteChar(ControlChar::Type::Delete);
    ControlChar unknown;

    CHECK(ControlChar::Type::ArrowUp == arrowUp.GetType());
    CHECK(ControlChar::Type::ArrowDown == arrowDown.GetType());
    CHECK(ControlChar::Type::ArrowLeft == arrowLeft.GetType());
    CHECK(ControlChar::Type::ArrowRight == arrowRight.GetType());
    CHECK(ControlChar::Type::Delete == deleteChar.GetType());
    CHECK(ControlChar::Type::Unknown == unknown.GetType());
}