#ifndef LONGEST_SEQUENCE_H
#define LONGEST_SEQUENCE_H

#include <string>

/**
 * @brief Find the longest common subsequence between two strings.
 * 
 * This uses bottom up dynamic programming to find the longest
 * common substring between two strings. It creates a match table
 * of which characters each string has in common. As told in the
 * book, the optimal subproblem is either both strings minus their
 * last characters or one string and the other minus its last
 * character. This is used in the table calculations.
 * @param string1 The first string to compare.
 * @param string2 The second string to compare.
 * @return The longest common substring.
 * */
inline std::string findLongestCommonSubsequence(const std::string & string1, const std::string & string2) {
	return "";
}

#endif // LONGEST_SEQUENCE_H