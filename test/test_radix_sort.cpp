#include "sorting.h"

#include "gtest/gtest.h"
#include <algorithm>
#include <vector>

/**
 * @brief This test fixture aids in sorting by receiving the
 * input list and automatically comparing it to the correctly
 * sorted version.
 * */
class RadixSortFixture : public ::testing::Test {
	protected:
	/**
	 * @brief Performs the sort operation.
	 * 
	 * This method first determines what the desired output should be. It
	 * then calls the sort function and compares the result.
	 * */
	void sort(const std::vector<unsigned int> & input) {
		auto target_output = input;
		std::sort(target_output.begin(), target_output.end());
		auto output = Sorting::radixSort(input);
		EXPECT_EQ(target_output, output);
	}
};

/**
 * @brief Test sorting of an empty array.
 * */
TEST_F(RadixSortFixture, EmptyArray) {
	std::vector<unsigned int> input;
	sort(input);
}

/**
 * @brief Test sorting of a single element array.
 * */
TEST_F(RadixSortFixture, SingleElement) {
	std::vector<unsigned int> input {2};
	sort(input);
}

/**
 * @brief Test sorting of an arbitrary array.
 * */
TEST_F(RadixSortFixture, Simple) {
	std::vector<unsigned int> input {205, 533, 318, 420, 945, 999, 100, 327};
	sort(input);
}

/**
 * @brief Test sorting of an already sorted array.
 * */
TEST_F(RadixSortFixture, Increasing) {
	std::vector<unsigned int> input;
	for (unsigned int i = 0; i < 100; ++i) {
		input.push_back(i);
	}
	sort(input);
}

/**
 * @brief Test sorting of a reverse sorted array.
 * */
TEST_F(RadixSortFixture, Decreasing) {
	std::vector<unsigned int> input;
	for (unsigned int i = 100; i > 0; --i) {
		input.push_back(i);
	}
	sort(input);
}

/**
 * @brief Test sorting of an array with every element identical.
 * */
TEST_F(RadixSortFixture, Uniform) {
	std::vector<unsigned int> input;
	for (unsigned int i = 0; i <= 0; ++i) {
		input.push_back(15);
	}
	sort(input);
}

/**
 * @brief Test sorting where each element has a different order of
 * magnitude.
 * */
TEST_F(RadixSortFixture, DifferentROM) {
	std::vector<unsigned int> input {318, 5, 53, 4205, 99999, 9450};
	sort(input);
}