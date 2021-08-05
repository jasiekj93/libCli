/**
 * @file ControlSequence.test.cpp
 * @author Adrian Szczepanski
 * @date 26-07-2021
 * @brief 
 * @details
 */

#include <libCli/Internal/IO/ControlSequence.hpp>
#include <cstring>

#include <CppUTest/CommandLineTestRunner.h>

using namespace Cli::Internal::IO;

TEST_GROUP(ControlSequenceTest)
{

};

TEST(ControlSequenceTest, DefaultConstructor)
{
    ControlSequence character;

    CHECK_EQUAL(0, std::strlen(character.Data()));
    CHECK_EQUAL('\0', character[0]);
}

TEST(ControlSequenceTest, InitalizerListConstructor)
{
    ControlSequence character{ 'h', 'i' };

    CHECK_EQUAL(2, std::strlen(character.Data()));
    CHECK_EQUAL('h', character[0]);
    CHECK_EQUAL('i', character[1]);
    CHECK_EQUAL('\0', character[2]);
}

TEST(ControlSequenceTest, StringConstructor)
{
    ControlSequence character("hi");

    CHECK_EQUAL(2, std::strlen(character.Data()));
    CHECK_EQUAL('h', character[0]);
    CHECK_EQUAL('i', character[1]);
    CHECK_EQUAL('\0', character[2]);
}

TEST(ControlSequenceTest, Clear)
{
    ControlSequence character("hi");
    character.Clear();

    CHECK_EQUAL(0, std::strlen(character.Data()));
    CHECK_EQUAL('\0', character[0]);

}

TEST(ControlSequenceTest, GetType)
{
    ControlSequence arrowUp(ControlSequence::Type::ArrowUp);
    ControlSequence arrowDown(ControlSequence::Type::ArrowDown);
    ControlSequence arrowLeft(ControlSequence::Type::ArrowLeft);
    ControlSequence arrowRight(ControlSequence::Type::ArrowRight);
    ControlSequence deleteChar(ControlSequence::Type::Delete);
    ControlSequence unknown;

    CHECK(ControlSequence::Type::ArrowUp == arrowUp.GetType());
    CHECK(ControlSequence::Type::ArrowDown == arrowDown.GetType());
    CHECK(ControlSequence::Type::ArrowLeft == arrowLeft.GetType());
    CHECK(ControlSequence::Type::ArrowRight == arrowRight.GetType());
    CHECK(ControlSequence::Type::Delete == deleteChar.GetType());
    CHECK(ControlSequence::Type::Unknown == unknown.GetType());
}

TEST(ControlSequenceTest, Arrow_ManyTimes)
{
    ControlSequence many(ControlSequence::Type::ArrowLeft, 5);
    ControlSequence tooMany(ControlSequence::Type::ArrowRight, ControlSequence::MAX_ARROW_REPEAT + 1);

    CHECK_EQUAL('5', many.Data()[2]);
    CHECK_EQUAL('C', tooMany.Data()[2]);
}