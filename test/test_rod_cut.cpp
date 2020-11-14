#include "rod_cut.h"

#include "gtest/gtest.h"
#include <map>

/**
 * @brief Create a price table.
 * 
 * This creates the price map shown in the book.
 * @return A map with prices for different lengths.
 * */
std::map<unsigned int, double> createPrices() {
	std::map<unsigned int, double> prices;
	prices[1] = 1.0;
	prices[2] = 5.0;
	prices[3] = 8.0;
	prices[4] = 9.0;
	prices[5] = 10.0;
	prices[6] = 17.0;
	prices[7] = 17.0;
	prices[8] = 20.0;
	prices[9] = 24.0;
	prices[10] = 30.0;
	return prices;
}

/**
 * @brief Evaluate a particular solution versus what is in the book.
 * 
 * This will test the results against what the book lists as the best
 * options and call the appropriate EXPECT functions.
 * @param length The length of the original rod.
 * @param cuts The cuts selected.
 * @param price The total price obtained.
 * */
void testOutput(unsigned int length, double price) {
	// Each case has its own solution, so unfortunately test them all.
	double expected_price = 0.0;
	switch (length) {
		case 1:
			expected_price = 1.0;
			break;
		case 2:
			expected_price = 5.0;
			break;
		case 3:
			expected_price = 8.0;
			break;
		case 4:
			expected_price = 10.0;
			break;
		case 5:
			expected_price = 13.0;
			break;
		case 6:
			expected_price = 17.0;
			break;
		case 7:
			expected_price = 18.0;
			break;
		case 8:
			expected_price = 22.0;
			break;
		case 9:
			expected_price = 25.0;
			break;
		case 10:
			expected_price = 30.0;
			break;
		default:
			FAIL();
			break;
	}
	EXPECT_DOUBLE_EQ(price, expected_price);
}

/**
 * @brief Test the top down approach.
 * 
 * As this isn't really an algorithm and more of a script,
 * this is the only unit test for this function. I could test
 * edge cases with equal prices at all lengths or something
 * like that, but it isn't readily apparent. This will do
 * for now.
 * */
TEST(RodCut, TopDown) {
	auto prices = createPrices();
	// Try for each length listed in the table.
	for (unsigned int i = 1; i <= 10; ++i) {
		double total_price = RodCut::bestRodCutTopDown(i, prices);
		testOutput(i, total_price);
	}
}

/**
 * @brief Test the bottom up approach.
 * 
 * As this isn't really an algorithm and more of a script,
 * this is the only unit test for this function. I could test
 * edge cases with equal prices at all lengths or something
 * like that, but it isn't readily apparent. This will do
 * for now.
 * */
TEST(RodCut, BottomUp) {
	auto prices = createPrices();
	// Try for each length listed in the table.
	for (unsigned int i = 1; i <= 10; ++i) {
		double total_price = RodCut::bestRodCutBottomUp(i, prices);
		testOutput(i, total_price);
	}
}