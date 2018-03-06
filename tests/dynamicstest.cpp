/* 
 * File:   dynamicstest.cpp
 * Author: Sam Rappl
 *
 */

#include "dynamics.h"
#include "constants.h"
#include "gtest/gtest.h"

TEST(dynamicstest, defaultConstructorTest) {
	Dynamics dynamic;
	ASSERT_EQ(mp, dynamic.volume);
	ASSERT_EQ(false, dynamic.cresc);
	ASSERT_EQ(false, dynamic.decresc);
}

TEST(dynamicstest, allArgsConstructorTest) {
	Dynamics dynamic(ff, true, false);
	ASSERT_EQ(ff, dynamic.volume);
	ASSERT_EQ(true, dynamic.cresc);
	ASSERT_EQ(false, dynamic.decresc);
}
