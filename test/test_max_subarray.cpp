#include "max_subarray.h"

#include "gtest/gtest.h"

/**
 * @brief Test an empty array.
 * */
TEST(MaxSubarray, EmptyArray) {
	std::vector<float> input;
	EXPECT_THROW(maxSubarray(input), std::invalid_argument);
}

/**
 * @brief Test a single element.
 * */
TEST(MaxSubarray, SingleElement) {
	std::vector<float> input;
	input.push_back(10.0);
	EXPECT_THROW(maxSubarray(input), std::invalid_argument);
}

/**
 * @brief Test a monotonic order.
 * */
TEST(MaxSubarray, Increasing) {
	std::vector<float> input;
	for (float i = -25.0; i <= 25.0; i += (float)0.3) {
		input.push_back(i);
	}
	int expected_low = 0;
	int expected_high = static_cast<int>(input.size()) - 1;
	double expected_sum = input[expected_high] - input[expected_low];
	auto results = maxSubarray(input);
	EXPECT_EQ(std::get<0>(results), 0);
	EXPECT_EQ(std::get<1>(results), input.size() - 1);
	EXPECT_NEAR(std::get<2>(results), expected_sum, 0.0001);
}

/**
 * @brief Test a decreasing order.
 * */
TEST(MaxSubarray, Decreasing) {
	std::vector<float> input;
	for (float i = 25.0; i >= -13.0; i -= (float)0.25) {
		input.push_back(i);
	}
	int expected_low = 0;
	int expected_high = 1;
	double expected_sum = input[expected_high] - input[expected_low];
	auto results = maxSubarray(input);
	EXPECT_EQ(std::get<0>(results), expected_low);
	EXPECT_EQ(std::get<1>(results), expected_high);
	EXPECT_NEAR(std::get<2>(results), expected_sum, 0.0001);
}

/**
 * @brief Test a single result.
 * 
 * This is from the book.
 * */
TEST(MaxSubarray, Simple) {
	std::vector<float> input {100.0, 113.0, 110.0, 85.0, 105.0, 102.0, 86.0, 63.0, 81.0, 101.0, 94.0, 106.0, 101.0, 79.0, 94.0, 90.0, 97.0};
	auto results = maxSubarray(input);
	EXPECT_EQ(std::get<0>(results), 7);
	EXPECT_EQ(std::get<1>(results), 11);
	EXPECT_EQ(std::get<2>(results), 43.0);
}

/**
 * @brief Test when there are two subarrays.
 * */
TEST(MaxSubarray, TwoMaxes) {
	std::vector<float> input {1.0, 2.0, 3.0, -4.0, -5.0, -4.0, -3.0};
	auto results = maxSubarray(input);
	EXPECT_EQ(std::get<0>(results), 0);
	EXPECT_EQ(std::get<1>(results), 2);
	EXPECT_EQ(std::get<2>(results), 2.0);
}