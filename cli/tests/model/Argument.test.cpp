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
    double d;
    unsigned long long ul;

    Argument arg;

    CHECK(Argument::Type::Empty == arg.GetType());
    CHECK_EQUAL(Argument::INVALID_NAME, arg.Name());
    CHECK(nullptr == arg.AsString());
    CHECK_FALSE(arg.AsDecimal(ul));
    CHECK_FALSE(arg.AsHex(ul));
    CHECK_FALSE(arg.AsDouble(d));
}

TEST(ArgumentTest, NullPointer)
{
    double d;
    unsigned long long ul;
    char name = 'a';

    Argument arg(name, nullptr);

    CHECK(Argument::Type::Empty == arg.GetType());
    CHECK_EQUAL(name, arg.Name());
    CHECK(nullptr == arg.AsString());
    CHECK_FALSE(arg.AsDecimal(ul));
    CHECK_FALSE(arg.AsHex(ul));
    CHECK_FALSE(arg.AsDouble(d));
}

TEST(ArgumentTest, Decimal)
{
    double d;
    unsigned long ul;
    char name = 'a';
    char stringNumber[] = "5423876";
    unsigned long number = 5423876;
    unsigned long hexNumber = 0x5423876;
    double doubleNumber = 5423876;

    Argument arg(name, stringNumber);

    CHECK(Argument::Type::Decimal == arg.GetType());
    CHECK_EQUAL(name, arg.Name());
    CHECK(stringNumber == arg.AsString());
    CHECK(arg.AsDecimal(ul));
    CHECK_EQUAL(ul, number);
    CHECK(arg.AsHex(ul));
    CHECK_EQUAL(ul, hexNumber);
    CHECK(arg.AsDouble(d));
    CHECK_EQUAL(doubleNumber, d);
}

TEST(ArgumentTest, Hex_WithPrefix)
{
    double d;
    unsigned long ul;
    char name = 'a';
    char stringNumber[] = "0x5423876";
    unsigned long hexNumber = 0x5423876;

    Argument arg(name, stringNumber);

    CHECK(Argument::Type::Hex == arg.GetType());
    CHECK_EQUAL(name, arg.Name());
    CHECK(stringNumber == arg.AsString());
    CHECK_FALSE(arg.AsDecimal(ul));
    CHECK(arg.AsHex(ul));
    CHECK_EQUAL(ul, hexNumber);
    CHECK_FALSE(arg.AsDouble(d));
}

TEST(ArgumentTest, Hex_WithLetters)
{
    double d;
    unsigned long ul;
    char name = 'a';
    char stringNumber[] = "54238FC";
    unsigned long hexNumber = 0x54238FC;

    Argument arg(name, stringNumber);

    CHECK(Argument::Type::Hex == arg.GetType());
    CHECK_EQUAL(name, arg.Name());
    CHECK(stringNumber == arg.AsString());
    CHECK_FALSE(arg.AsDecimal(ul));
    CHECK(arg.AsHex(ul));
    CHECK_EQUAL(ul, hexNumber);
    CHECK_FALSE(arg.AsDouble(d));
}

TEST(ArgumentTest, NotAHex)
{
    double d;
    unsigned long ul;
    char name = 'a';
    char stringNumber[] = "54238UH";

    Argument arg(name, stringNumber);

    CHECK(Argument::Type::String == arg.GetType());
    CHECK_EQUAL(name, arg.Name());
    CHECK(stringNumber == arg.AsString());
    CHECK_FALSE(arg.AsDecimal(ul));
    CHECK_FALSE(arg.AsHex(ul));
    CHECK_FALSE(arg.AsDouble(d));
}

TEST(ArgumentTest, String)
{
    double d;
    unsigned long ul;
    char name = 'a';
    char stringNumber[] = "Hello";

    Argument arg(name, stringNumber);

    CHECK(Argument::Type::String == arg.GetType());
    CHECK_EQUAL(name, arg.Name());
    CHECK(stringNumber == arg.AsString());
    CHECK_FALSE(arg.AsDecimal(ul));
    CHECK_FALSE(arg.AsHex(ul));
    CHECK_FALSE(arg.AsDouble(d));
}

TEST(ArgumentTest, Double)
{
    double d;
    unsigned long ul;
    char name = 'a';
    char stringNumber[] = "55.12345";
    double number = 55.12345;

    Argument arg(name, stringNumber);

    CHECK(Argument::Type::Double == arg.GetType());
    CHECK_EQUAL(name, arg.Name());
    CHECK(stringNumber == arg.AsString());
    CHECK_FALSE(arg.AsDecimal(ul));
    CHECK_FALSE(arg.AsHex(ul));
    CHECK(arg.AsDouble(d));
    CHECK_EQUAL(number, d);
}

TEST(ArgumentTest, Double_TwoDots)
{
    double d;
    unsigned long ul;
    char name = 'a';
    char stringNumber[] = "55.123.45";

    Argument arg(name, stringNumber);

    CHECK(Argument::Type::String == arg.GetType());
    CHECK_EQUAL(name, arg.Name());
    CHECK(stringNumber == arg.AsString());
    CHECK_FALSE(arg.AsDecimal(ul));
    CHECK_FALSE(arg.AsHex(ul));
    CHECK_FALSE(arg.AsDouble(d));
}

TEST(ArgumentTest, Double_DotAtBeginning)
{
    double d;
    unsigned long ul;
    char name = 'a';
    char stringNumber[] = ".45";
    double number = 0.45;

    Argument arg(name, stringNumber);

    CHECK(Argument::Type::Double == arg.GetType());
    CHECK_EQUAL(name, arg.Name());
    CHECK(stringNumber == arg.AsString());
    CHECK_FALSE(arg.AsDecimal(ul));
    CHECK_FALSE(arg.AsHex(ul));
    CHECK(arg.AsDouble(d));
    CHECK_EQUAL(number, d);
}

TEST(ArgumentTest, Double_DotAtEnd)
{
    double d;
    unsigned long ul;
    char name = 'a';
    char stringNumber[] = "45.";
    double number = 45;

    Argument arg(name, stringNumber);

    CHECK(Argument::Type::Double == arg.GetType());
    CHECK_EQUAL(name, arg.Name());
    CHECK(stringNumber == arg.AsString());
    CHECK_FALSE(arg.AsDecimal(ul));
    CHECK_FALSE(arg.AsHex(ul));
    CHECK(arg.AsDouble(d));
    CHECK_EQUAL(number, d);
}