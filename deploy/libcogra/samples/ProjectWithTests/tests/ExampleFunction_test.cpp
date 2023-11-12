#include <gtest/gtest.h>
#include "../ExampleFunctions.h"
TEST(ExampleFunctions, ConvertTriangluatedLion)
{
	EXPECT_EQ(cogra::ExampleFunctions::powerOfTwo(2U), 4U);
}