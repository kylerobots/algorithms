#include "sorting.h"

#include "gtest/gtest.h"
#include <algorithm>

/**
 * @brief A test fixture to aid in sorting by receiving the input
 * list and automatically comparing it to the correctly sorted
 * version.
 * */
class BucketSortFixture : public ::testing::Test {
	protected:
	/**
	 * @brief Performs the sort operation
	 * 
	 * This method first determines what the desired output should be. It then
	 * calls the sort function and compares the result.
	 * @param input The unsorted list to sort and compare.
	 * */
	void sort(const std::vector<double> & input) {
		auto target_output = input;
		std::sort(target_output.begin(), target_output.end());
		auto output = Sorting::bucketSort(input);
		EXPECT_EQ(target_output, output);
	}
};

/**
 * @brief Test an empty array.
 * */
TEST_F(BucketSortFixture, EmptyArray) {
	std::vector<double> input;
	sort(input);
}

/**
 * @brief Test a single element array.
 * */
TEST_F(BucketSortFixture, SingleElement) {
	std::vector<double> input {0.5};
	sort(input);
}

/**
 * @brief Test a simple array.
 * */
TEST_F(BucketSortFixture, Simple) {
	std::vector<double> input {0.5, 0.234, 0.756, 0.178};
	sort(input);
}

/**
 * @brief Test an already sorted array
 * */
TEST_F(BucketSortFixture, Increasing) {
	std::vector<double> input {0.1, 0.2, 0.3, 0.4};
	sort(input);
}

/**
 * @brief Test a reverse sorted array
 * */
TEST_F(BucketSortFixture, Decreasing) {
	std::vector<double> input {0.9, 0.8, 0.7, 0.6};
	sort(input);
}

/**
 * @brief Test an array where every element is the same.
 * */
TEST_F(BucketSortFixture, Uniform) {
	std::vector<double> input;
	for (size_t i = 0; i < 10; ++i) {
		input.push_back(0.0);
	}
	sort(input);
}

/**
 * @brief Test an array where the values are below the range.
 * */
TEST_F(BucketSortFixture, OOBLower) {
	std::vector<double> input {-5.0, -6.0, 0.5};
	EXPECT_THROW(Sorting::bucketSort(input), std::out_of_range);
}

/**
 * @brief Test an array where the values are above the range.
 * */
TEST_F(BucketSortFixture, OOBUpper) {
	std::vector<double> input {1.0, 0.25};
	EXPECT_THROW(Sorting::bucketSort(input), std::out_of_range);
}