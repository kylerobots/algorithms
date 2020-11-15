#ifndef LONGEST_SEQUENCE_H
#define LONGEST_SEQUENCE_H

#include <string>
#include <vector>

/**
	 * @brief This is a namespace with some under the hood functions.
	 * 
	 * These should generally not be called by the user unless you are
	 * very sure what you are doing and have a very good reason for
	 * doing so.
	 * */
namespace detail {
	/**
	 * @brief A representation of the directions stored in the table.
	 * 
	 * These represent the different directions used to determine how
	 * to walk along the substring solution table.
	 * */
	enum class Direction {
		DIAGONAL,
		LEFT,
		NOTHING,
		UP
	};

	/**
	 * @brief The table that stores the values for each pair of characters.
	 * */
	typedef std::vector<std::vector<unsigned int>> Values;

	/**
	 * @brief The table that stores teh directions for each pair of characters.
	 * */
	typedef std::vector<std::vector<Direction>> Directions;

	/**
	 * @brief Compute the tables used for finding the LCS.
	 * 
	 * This creates two tables. One stores the values given
	 * in the recursive formula. The other gives th directions
	 * used to reconstruct the string.
	 * @param string1 The first string to compare.
	 * @param string2 The second string to compare.
	 * @return A pair of the two tables.
	 * */
	inline std::pair<Values, Directions> computeLCS(const std::string & string1, const std::string & string2) {
		// Create each table and initialize with empty values.
		Values values;
		Directions directions;
		// for (size_t i = 0; i < string1.length(); ++i) {
		// 	std::vector<unsigned int> value_row;
		// 	std::vector<Direction> direction_row;
		// 	for (size_t j = 0; j < string2.length(); ++j) {
		// 		value_row.push_back(0);
		// 		direction_row.push_back(Direction::NOTHING);
		// 	}
		// 	values.push_back(value_row);
		// 	directions.push_back(direction_row);
		// }
		// Now, build up all the solutions.
		for (size_t i = 0; i <= string1.length(); ++i) {
			std::vector<unsigned int> value_row;
			std::vector<Direction> direction_row;
			for (size_t j = 0; j <= string2.length(); ++j) {
				// The first row and column are all zero.
				if (i == 0 || j == 0) {
					value_row.push_back(0);
					direction_row.push_back(Direction::NOTHING);
				} else {
					// These three cases come from the recursive formula in the book.
					if (string1.at(i - 1) == string2.at(j - 1)) {
						value_row.push_back(values[i - 1][j - 1] + 1);
						direction_row.push_back(Direction::DIAGONAL);
						// Values doesn't have the current row yet, so use the value_row instead.
					} else if (values[i - 1][j] >= value_row.at(j - 1)) {
						value_row.push_back(values[i - 1][j]);
						direction_row.push_back(Direction::UP);
					} else {
						value_row.push_back(value_row.at(j - 1));
						direction_row.push_back(Direction::LEFT);
					}
				}
			}
			values.push_back(value_row);
			directions.push_back(direction_row);
		}
		return std::make_pair(values, directions);
	}

	/**
	 * @brief Takes the computed solution tables and recursively extracts
	 * the LCS.
	 * @param direction The table that stores directions.
	 * @param string1 One of the strings, used to extract characters.
	 * @param length1 The length of the substring solution for @ref string1.
	 * @param length2 The length of the substring solution for the other string.
	 * */
	inline std::string printLCS(const Directions & direction, const std::string & string1, unsigned int length1, unsigned int length2) {
		if (length1 == 0 || length2 == 0) {
			return "";
		}
		std::string result("");
		if (direction[length1][length2] == Direction::DIAGONAL) {
			result = printLCS(direction, string1, length1 - 1, length2 - 1);
			// The table has a zero row and column so indices into the string need
			// to be offset by one to be accurate.
			result += string1.at(length1 - 1);
		} else if (direction[length1][length2] == Direction::UP) {
			result = printLCS(direction, string1, length1 - 1, length2);
		} else {
			result = printLCS(direction, string1, length1, length2 - 1);
		}
		return result;
	}
} // namespace detail

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
	// If either string is empty, then the longest substring is an empty string.
	if (string1.empty() || string2.empty()) {
		return "";
	}
	// First, create the tables that hold each of the subproblems (and
	// the actual problem solution).
	auto tables = detail::computeLCS(string1, string2);
	std::string result = detail::printLCS(tables.second, string1, string1.length(), string2.length());
	return result;
}

#endif // LONGEST_SEQUENCE_H