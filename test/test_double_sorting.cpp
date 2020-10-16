#include "sorting.h"

#include "gtest/gtest.h"
#include <algorithm>
#include <limits>

/**
 * @brief The test fixture that allows common sort processes for all the sort routines that operate on any
 * unsorted list without underlying assumptions as to the list.
 * 
 * In order to utilize different functions, this uses the parameter version. the parameters are actually the different
 * sort functions.
 * */
class DoubleSortFixture : public testing::TestWithParam<std::function<std::vector<double>(const std::vector<double> &)> > {
	protected:
	/**
	 * @brief Performs the sort operation.
	 * 
	 * This method first determines what the desired output should be. It then takes the provided input and
	 * calls the appropriate sort function. It will then compare the two.
	 * */
	void sort(const std::vector<double> & input) {
		auto target_output = input;
		std::sort(target_output.begin(), target_output.end());
		auto sort_function = GetParam();
		auto output = sort_function(input);
		EXPECT_EQ(target_output, output);
	}
};

// The specific functions to test. I can technically put them all on one line, but by doing it seperate,
// I will actually get different names on the output so I can identify where the failures are. I don't know
// if this is a poor design or not.
INSTANTIATE_TEST_SUITE_P(InsertionSort, DoubleSortFixture, testing::Values(Sorting::insertionSort));
INSTANTIATE_TEST_SUITE_P(MergeSort, DoubleSortFixture, testing::Values(Sorting::mergeSort));

TEST_P(DoubleSortFixture, EmptyCase) {
	std::vector<double> input;
	sort(input);
}

TEST_P(DoubleSortFixture, SingleElement) {
	std::vector<double> input;
	input.push_back(0.0);
	sort(input);
}

TEST_P(DoubleSortFixture, Simple) {
	std::vector<double> input {1, 4.5, 3.2, 2.1};
	sort(input);
}

TEST_P(DoubleSortFixture, AlreadySorted) {
	std::vector<double> input;
	for (double i = -10.0; i < 25.0; i += 1.1) {
		input.push_back(i);
	}
	sort(input);
}

TEST_P(DoubleSortFixture, ReverseSorted) {
	std::vector<double> input;
	for (double i = 25.0; i > -25.0; i -= 0.5) {
		input.push_back(i);
	}
	sort(input);
}

TEST_P(DoubleSortFixture, NumericalLimits) {
	std::vector<double> input;
	input.push_back(0.0);
	input.push_back(std::numeric_limits<double>::max());
	input.push_back(std::numeric_limits<double>::min());
	sort(input);
}