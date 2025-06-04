/**
 * @file ControlSequence.test.cpp
 * @author Adrian Szczepanski
 * @date 26-07-2021
 * @brief 
 * @details
 */

#include <libcli/internal/io/ControlSequence.hpp>
#include <cstring>

#include <CppUTest/CommandLineTestRunner.h>

using namespace cli::internal::io;

TEST_GROUP(ControlSequenceTest)
{

};

TEST(ControlSequenceTest, DefaultConstructor)
{
    ControlSequence character;

    CHECK_EQUAL(0, character.getSize());
    CHECK_EQUAL('\0', character[0]);
}

TEST(ControlSequenceTest, InitalizerListConstructor)
{
    ControlSequence character{ 'h', 'i' };

    CHECK_EQUAL(2, character.getSize());
    CHECK_EQUAL('h', character[0]);
    CHECK_EQUAL('i', character[1]);
    CHECK_EQUAL('\0', character[2]);
}

TEST(ControlSequenceTest, StringConstructor)
{
    ControlSequence character("hi");

    CHECK_EQUAL(2, character.getSize());
    CHECK_EQUAL('h', character[0]);
    CHECK_EQUAL('i', character[1]);
    CHECK_EQUAL('\0', character[2]);
}

TEST(ControlSequenceTest, Clear)
{
    ControlSequence character("hi");
    character.clear();

    CHECK_EQUAL(0, character.getSize());
    CHECK_EQUAL('\0', character[0]);

}

TEST(ControlSequenceTest, GetType)
{
    ControlSequence arrowUp(ControlSequence::Type::ARROW_UP);
    ControlSequence arrowDown(ControlSequence::Type::ARROW_DOWN);
    ControlSequence arrowLeft(ControlSequence::Type::ARROW_LEFT);
    ControlSequence arrowRight(ControlSequence::Type::ARROW_RIGHT);
    ControlSequence deleteChar(ControlSequence::Type::DELETE);
    ControlSequence unknown;

    CHECK(ControlSequence::Type::ARROW_UP == arrowUp.getType());
    CHECK(ControlSequence::Type::ARROW_DOWN == arrowDown.getType());
    CHECK(ControlSequence::Type::ARROW_LEFT == arrowLeft.getType());
    CHECK(ControlSequence::Type::ARROW_RIGHT == arrowRight.getType());
    CHECK(ControlSequence::Type::DELETE == deleteChar.getType());
    CHECK(ControlSequence::Type::UNKNOWN == unknown.getType());
}

TEST(ControlSequenceTest, Arrow_ManyTimes)
{
    ControlSequence many(ControlSequence::Type::ARROW_LEFT, 5);
    ControlSequence tooMany(ControlSequence::Type::ARROW_RIGHT, ControlSequence::MAX_ARROW_REPEAT + 1);

    CHECK_EQUAL('5', many.getData()[2]);
    CHECK_EQUAL('C', tooMany.getData()[2]);
}