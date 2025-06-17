/**
 * @file Argument.test.cpp
 * @author Adrian Szczepanski
 * @date 28-07-2021
 * @brief 
 * @details
 */

#include <libcli/model/Argument.hpp>
#include <cstring>

#include <CppUTest/CommandLineTestRunner.h>

using namespace cli;
using namespace cli::model;


TEST_GROUP(ArgumentTest)
{
};

TEST(ArgumentTest, DefaultConstuctor)
{
    Argument arg;

    CHECK(Argument::Type::EMPTY == arg.getType());
    CHECK_EQUAL(Argument::INVALID_NAME, arg.getName());
    CHECK(nullptr == arg.asString());
    CHECK_FALSE(arg.asDecimal().has_value());
    CHECK_FALSE(arg.asHex().has_value());
    CHECK_FALSE(arg.asDouble().has_value());
}

TEST(ArgumentTest, NullPointer)
{
    char name = 'a';
    Argument arg(name, nullptr);

    CHECK(Argument::Type::EMPTY == arg.getType());
    CHECK_EQUAL(name, arg.getName());
    CHECK(nullptr == arg.asString());
    CHECK_FALSE(arg.asDecimal().has_value());
    CHECK_FALSE(arg.asHex().has_value());
    CHECK_FALSE(arg.asDouble().has_value());
}

TEST(ArgumentTest, Decimal)
{
    char name = 'a';
    char stringNumber[] = "5423876";
    unsigned long number = 5423876;
    unsigned long hexNumber = 0x5423876;
    double doubleNumber = 5423876;

    Argument arg(name, stringNumber);

    CHECK(Argument::Type::DECIMAL == arg.getType());
    CHECK_EQUAL(name, arg.getName());
    CHECK(stringNumber == arg.asString());
    CHECK(arg.asDecimal().has_value());
    CHECK_EQUAL(arg.asDecimal().value(), number);
    CHECK(arg.asHex().has_value());
    CHECK_EQUAL(arg.asHex().value(), hexNumber);
    CHECK(arg.asDouble().has_value());
    CHECK_EQUAL(arg.asDouble().value(), doubleNumber);
}

TEST(ArgumentTest, Hex_WithPrefix)
{
    char name = 'a';
    char stringNumber[] = "0x5423876";
    unsigned long hexNumber = 0x5423876;

    Argument arg(name, stringNumber);

    CHECK(Argument::Type::HEX == arg.getType());
    CHECK_EQUAL(name, arg.getName());
    CHECK(stringNumber == arg.asString());
    CHECK_FALSE(arg.asDecimal().has_value());
    CHECK(arg.asHex().has_value());
    CHECK_EQUAL(arg.asHex().value(), hexNumber);
    CHECK_FALSE(arg.asDouble().has_value());
}

TEST(ArgumentTest, Hex_WithLetters)
{
    char name = 'a';
    char stringNumber[] = "54238FC";
    unsigned long hexNumber = 0x54238FC;

    Argument arg(name, stringNumber);

    CHECK(Argument::Type::HEX == arg.getType());
    CHECK_EQUAL(name, arg.getName());
    CHECK(stringNumber == arg.asString());
    CHECK_FALSE(arg.asDecimal().has_value());
    CHECK(arg.asHex().has_value());
    CHECK_EQUAL(arg.asHex().value(), hexNumber);
    CHECK_FALSE(arg.asDouble().has_value());
}

TEST(ArgumentTest, NotAHex)
{
    double d;
    unsigned long ul;
    char name = 'a';
    char stringNumber[] = "54238UH";

    Argument arg(name, stringNumber);

    CHECK(Argument::Type::STRING == arg.getType());
    CHECK_EQUAL(name, arg.getName());
    CHECK(stringNumber == arg.asString());
    CHECK_FALSE(arg.asDecimal().has_value());
    CHECK_FALSE(arg.asHex().has_value());
    CHECK_FALSE(arg.asDouble().has_value());
}

TEST(ArgumentTest, String)
{
    char name = 'a';
    char stringNumber[] = "Hello";

    Argument arg(name, stringNumber);

    CHECK(Argument::Type::STRING == arg.getType());
    CHECK_EQUAL(name, arg.getName());
    CHECK(stringNumber == arg.asString());
    CHECK_FALSE(arg.asDecimal().has_value());
    CHECK_FALSE(arg.asHex().has_value());
    CHECK_FALSE(arg.asDouble().has_value());
}

TEST(ArgumentTest, Double)
{
    char name = 'a';
    char stringNumber[] = "55.12345";
    double number = 55.12345;

    Argument arg(name, stringNumber);

    CHECK(Argument::Type::DOUBLE == arg.getType());
    CHECK_EQUAL(name, arg.getName());
    CHECK(stringNumber == arg.asString());
    CHECK_FALSE(arg.asDecimal().has_value());
    CHECK_FALSE(arg.asHex().has_value());
    CHECK(arg.asDouble().has_value());
    CHECK_EQUAL(number, arg.asDouble().value());
}

TEST(ArgumentTest, Double_TwoDots)
{
    char name = 'a';
    char stringNumber[] = "55.123.45";

    Argument arg(name, stringNumber);

    CHECK(Argument::Type::STRING == arg.getType());
    CHECK_EQUAL(name, arg.getName());
    CHECK(stringNumber == arg.asString());
    CHECK_FALSE(arg.asDecimal().has_value());
    CHECK_FALSE(arg.asHex().has_value());
    CHECK_FALSE(arg.asDouble().has_value());
}

TEST(ArgumentTest, Double_DotAtBeginning)
{
    char name = 'a';
    char stringNumber[] = ".45";
    double number = 0.45;

    Argument arg(name, stringNumber);

    CHECK(Argument::Type::DOUBLE == arg.getType());
    CHECK_EQUAL(name, arg.getName());
    CHECK(stringNumber == arg.asString());
    CHECK_FALSE(arg.asDecimal().has_value());
    CHECK_FALSE(arg.asHex().has_value());
    CHECK(arg.asDouble().has_value());
    CHECK_EQUAL(number, arg.asDouble().value());
}

TEST(ArgumentTest, Double_DotAtEnd)
{
    char name = 'a';
    char stringNumber[] = "45.";
    double number = 45;

    Argument arg(name, stringNumber);

    CHECK(Argument::Type::DOUBLE == arg.getType());
    CHECK_EQUAL(name, arg.getName());
    CHECK(stringNumber == arg.asString());
    CHECK_FALSE(arg.asDecimal().has_value());
    CHECK_FALSE(arg.asHex().has_value());
    CHECK(arg.asDouble().has_value());
    CHECK_EQUAL(number, arg.asDouble().value());
}