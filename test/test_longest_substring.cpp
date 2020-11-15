#include "longest_substring.h"

#include "gtest/gtest.h"

/**
 * @brief Test empty strings.
 * */
TEST(LCS, Empty) {
	auto result = findLongestCommonSubstring("", "");
	EXPECT_EQ(result, "");
	result = findLongestCommonSubstring("1234", "");
	EXPECT_EQ(result, "");
	result = findLongestCommonSubstring("", "abcd");
	EXPECT_EQ(result, "");
}

/**
 * @brief Test if no common characters.
 * */
TEST(LCS, NoMatch) {
	auto result = findLongestCommonSubstring("abcd", "1234");
	EXPECT_EQ(result, "");
}

/**
 * @brief Test simple case.
 * */
TEST(LCS, Simple) {
	auto result = findLongestCommonSubstring("ABCBDAB", "BDCABA");
	EXPECT_EQ(result, "BCBA");
}

/**
 * @brief Test if one string is a complete substring of another.
 * */
TEST(LCS, CompleteSubstring) {
	auto result = findLongestCommonSubstring("BAT", "BATTER");
	EXPECT_EQ(result, "BAT");
}