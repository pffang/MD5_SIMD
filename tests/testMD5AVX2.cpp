#include "MD5_AVX2.h"
#include "global_test_data.h"
#include "gtest/gtest.h"

class MD5AVX2Test : public ::testing::Test
{
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
    MD5_AVX2 md5;
};

TEST_F(MD5AVX2Test, R1)
{
    md5.update(str1.c_str(), str1.length());
    md5.finalize();
    EXPECT_EQ(md5.hexdigest(), r1);
}

TEST_F(MD5AVX2Test, R2)
{
    md5.update(str2.c_str(), str2.length());
    md5.finalize();
    EXPECT_EQ(md5.hexdigest(), r2);
}

TEST_F(MD5AVX2Test, R3)
{
    md5.update(str3.c_str(), str3.length());
    md5.finalize();
    EXPECT_EQ(md5.hexdigest(), r3);
}
