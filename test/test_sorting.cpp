#include "sorting.h"

#include "gtest/gtest.h"
#include <algorithm>
#include <limits>

// A test fixture to perform the actual sorting.
class SortFixture : public testing::Test {
	protected:
	std::tuple<std::vector<double>, std::vector<double> > sort(const std::vector<double> & input) {
		auto target_output = input;
		std::sort(target_output.begin(), target_output.end());
		auto output = Sorting::insertionSort(input);
		return std::make_tuple(target_output, output);
	}
};

TEST_F(SortFixture, EmptyCase) {
	std::vector<double> input;
	auto results = sort(input);
	EXPECT_EQ(std::get<0>(results), std::get<1>(results));
}

TEST_F(SortFixture, SingleElement) {
	std::vector<double> input;
	input.push_back(0.0);
	auto results = sort(input);
	EXPECT_EQ(std::get<0>(results), std::get<1>(results));
}

TEST_F(SortFixture, Simple) {
	std::vector<double> input {1, 4.5, 3.2, 2.1};
	auto results = sort(input);
	EXPECT_EQ(std::get<0>(results), std::get<1>(results));
}

TEST_F(SortFixture, AlreadySorted) {
	std::vector<double> input;
	for (size_t i = -10; i < 25; i++) {
		input.push_back(i);
	}
	auto results = sort(input);
	EXPECT_EQ(std::get<0>(results), std::get<1>(results));
}

TEST_F(SortFixture, ReverseSorted) {
	std::vector<double> input;
	for (size_t i = 25; i > -25; i--) {
		input.push_back(i);
	}
	auto results = sort(input);
	EXPECT_EQ(std::get<0>(results), std::get<1>(results));
}

TEST_F(SortFixture, NumericalLimits) {
	std::vector<double> input;
	input.push_back(0.0);
	input.push_back(std::numeric_limits<double>::max());
	input.push_back(std::numeric_limits<double>::min());
	auto results = sort(input);
	EXPECT_EQ(std::get<0>(results), std::get<1>(results));
}