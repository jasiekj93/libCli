/**
 * @file ControlChar.test.cpp
 * @author Adrian Szczepanski
 * @date 26-07-2021
 * @brief 
 * @details
 */

#include <libCli/ControlChar.hpp>
#include <cstring>

#include <CppUTest/CommandLineTestRunner.h>

using namespace Cli;


TEST_GROUP(ControlCharTest)
{

};

TEST(ControlCharTest, DefaultConstructor)
{
    ControlChar character;

    CHECK_EQUAL(0, std::strlen(character.Data()));
    CHECK_EQUAL('\0', character[0]);
}

TEST(ControlCharTest, InitalizerListConstructor)
{
    ControlChar character{ 'h', 'i' };

    CHECK_EQUAL(2, std::strlen(character.Data()));
    CHECK_EQUAL('h', character[0]);
    CHECK_EQUAL('i', character[1]);
    CHECK_EQUAL('\0', character[2]);
}

TEST(ControlCharTest, StringConstructor)
{
    ControlChar character("hi");

    CHECK_EQUAL(2, std::strlen(character.Data()));
    CHECK_EQUAL('h', character[0]);
    CHECK_EQUAL('i', character[1]);
    CHECK_EQUAL('\0', character[2]);
}

TEST(ControlCharTest, Clear)
{
    ControlChar character("hi");
    character.Clear();

    CHECK_EQUAL(0, std::strlen(character.Data()));
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