#include "sorting.h"

#include "gtest/gtest.h"
#include <algorithm>
#include <limits>

TEST(TestSorting, EmptyCase) {
	std::vector<double> input;
	auto output = Sorting::insertionSort(input);
	EXPECT_EQ(input, output);
}

TEST(TestSorting, SingleElement) {
	std::vector<double> input;
	input.push_back(0.0);
	auto output = Sorting::insertionSort(input);
	EXPECT_EQ(input, output);
}

TEST(TestSorting, Simple) {
	std::vector<double> input {1, 4.5, 3.2, 2.1};
	auto target_output = input;
	std::sort(target_output.begin(), target_output.end());
	auto output = Sorting::insertionSort(input);
	EXPECT_EQ(output, target_output);
}

TEST(TestSorting, AlreadySorted) {
	std::vector<double> input;
	for (size_t i = -10; i < 25; i++) {
		input.push_back(i);
	}
	auto output = Sorting::insertionSort(input);
	EXPECT_EQ(input, output);
}

TEST(TestSorting, ReverseSorted) {
	std::vector<double> input;
	for (size_t i = 25; i > -25; i--) {
		input.push_back(i);
	}
	auto target_output = input;
	std::sort(target_output.begin(), target_output.end());
	auto output = Sorting::insertionSort(input);
	EXPECT_EQ(output, target_output);
}

TEST(TestSorting, BigNumberSort) {
	std::vector<double> input;
	input.push_back(0.0);
	input.push_back(std::numeric_limits<double>::max());
	input.push_back(std::numeric_limits<double>::min());
	auto target_output = input;
	std::sort(target_output.begin(), target_output.end());
	auto output = Sorting::insertionSort(input);
	EXPECT_EQ(output, target_output);
}