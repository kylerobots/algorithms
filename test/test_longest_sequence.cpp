#include "longest_sequence.h"

#include "gtest/gtest.h"

/**
 * @brief Test empty strings.
 * */
TEST(LCS, Empty) {
	auto result = findLongestCommonSubsequence("", "");
	EXPECT_EQ(result, "");
	result = findLongestCommonSubsequence("1234", "");
	EXPECT_EQ(result, "");
	result = findLongestCommonSubsequence("", "abcd");
	EXPECT_EQ(result, "");
}

/**
 * @brief Test if no common characters.
 * */
TEST(LCS, NoMatch) {
	auto result = findLongestCommonSubsequence("abcd", "1234");
	EXPECT_EQ(result, "");
}

/**
 * @brief Test simple case.
 * */
TEST(LCS, Simple) {
	auto result = findLongestCommonSubsequence("ABCBDAB", "BDCABA");
	EXPECT_EQ(result, "BCBA");
}

/**
 * @brief Test if one string is a complete substring of another.
 * */
TEST(LCS, CompleteSubstring) {
	auto result = findLongestCommonSubsequence("BAT", "BATTER");
	EXPECT_EQ(result, "BAT");
}