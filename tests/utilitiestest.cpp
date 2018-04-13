/* 
 * File:   utilitestest.cpp
 * Author: Sam Rappl and Jacob Inkrote
 *
 */

#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>
#include "utilities.h"
#include "gtest/gtest.h"

TEST(utilitiesTest, jsonTest) {
	// This is here to ensure nlohmann's json library is included properly
	nlohmann::json j;
	j["hi"] = "good morning";
	ASSERT_EQ("good morning", j["hi"]);
}
