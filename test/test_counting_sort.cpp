#include "sorting.h"

#include "gtest/gtest.h"
#include <algorithm>

/**
 * @brief This test fixture aids in sorting by receiving the
 * input list and automatically comparing it to the correctly
 * sorted version.
 * */
class CountingSortFixture : public ::testing::Test {
	protected:
	/**
	 * @brief Performs the sort operation.
	 * 
	 * This method first determines what the desired output should be. It
	 * then calls the sort function and compares the result.
	 * @param input The vector of numbers to sort.
	 * */
	void sort(const std::vector<uint8_t> & input) {
		auto target_output = input;
		std::sort(target_output.begin(), target_output.end());
		auto output = Sorting::countingSort(input);
		EXPECT_EQ(target_output, output);
	}
};

TEST_F(CountingSortFixture, EmptyArray) {
	std::vector<uint8_t> input;
	sort(input);
}

TEST_F(CountingSortFixture, SingleElement) {
	std::vector<uint8_t> input {2};
	sort(input);
}

TEST_F(CountingSortFixture, Simple) {
	std::vector<uint8_t> input {2, 5, 3, 0, 2, 3, 0, 3};
	sort(input);
}

TEST_F(CountingSortFixture, Increasing) {
	std::vector<uint8_t> input;
	for (uint8_t i = 0; i < 100; ++i) {
		input.push_back(i);
	}
	sort(input);
}

TEST_F(CountingSortFixture, Decreasing) {
	std::vector<uint8_t> input;
	for (uint8_t i = 100; i > 0; --i) {
		input.push_back(i);
	}
	sort(input);
}

TEST_F(CountingSortFixture, Uniform) {
	std::vector<uint8_t> input;
	for (uint8_t i = 0; i <= 0; ++i) {
		input.push_back(15);
	}
	sort(input);
}

TEST_F(CountingSortFixture, LargeRandom) {
	std::vector<uint8_t> input;
	// Since this is only used for initialization of a random generator,
	// I don't care about potential loss of data from casting.
	srand(static_cast<unsigned int>(time(nullptr)));
	for (size_t i = 0; i < 1000; ++i) {
		uint8_t number = rand() % std::numeric_limits<uint8_t>::max();
		input.push_back(number);
	}
	sort(input);
}