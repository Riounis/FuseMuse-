/* 
 * File:   dynamicstest.cpp
 * Author: Sam Rappl
 *
 */

#include "dynamics.h"
#include "constants.h"
#include "gtest/gtest.h"

TEST(dynamicsTest, defaultConstructorTest) {
	Dynamic dynamic;
	ASSERT_EQ(mp, dynamic.volume);
	ASSERT_EQ(false, dynamic.cresc);
	ASSERT_EQ(false, dynamic.decresc);
}

TEST(dynamicsTest, allArgsConstructorTest) {
	Dynamic dynamic(ff, true, false);
	ASSERT_EQ(ff, dynamic.volume);
	ASSERT_EQ(true, dynamic.cresc);
	ASSERT_EQ(false, dynamic.decresc);
}
