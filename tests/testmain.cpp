/* 
 * File:   testmain.cpp
 * Author: Sam Rappl and Jacob Inkrote
 *
 */

#include "gtest/gtest.h"

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}