#include "global_test_data.h"
#include "gtest/gtest.h"

std::string str1 = "";
std::string r1   = "D41D8CD98F00B204E9800998ECF8427E";
std::string str2 = "admin";
std::string r2   = "21232F297A57A5A743894A0E4A801FC3";
std::string str3 = "123456";
std::string r3   = "E10ADC3949BA59ABBE56E057F20F883E";

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
