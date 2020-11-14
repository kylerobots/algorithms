#ifndef ROD_CUT_H
#define ROD_CUT_H

#include <map>
#include <vector>

/**
 * @brief A collection of methods to compute the optimal way to cut a rod.
 * 
 * This provides two methods to compute the best way to cut a rod to maximize
 * profit, when given the price of different lengths of rods. It assumes all
 * cuts are whole units of measure. The two methods are both dynamic programming
 * methods - bottom-up and top-down methods.
 * */
namespace RodCut {
	/**
	 * @brief Calculate the optimal cut pattern for a rod with bottom-up
	 * calculations.
	 * 
	 * This uses a bottoms up approach by calculating all the combinations
	 * from 1 to length. It can then easily compute the ideal combination.
	 * @param length The uncut length of the rod.
	 * @param prices A map of the prices obstained for each length of
	 * rod. Assumed to have all integers from 1 to length.
	 * @return The best price that can be obtained.
	 * */
	inline double bestRodCutBottomUp(unsigned int length, std::map<unsigned int, double> prices) {
		double best_price = 0.0;
		return best_price;
	}

	/**
	 * @brief Calculate the optimal cut patter for a rod with top-down
	 * memoization.
	 * 
	 * This uses a top down approach and recursively computes and stores
	 * each subproblem when determining the rod's ideal cut length.
	 * @param length The uncut length of the rod.
	 * @param prices A map of the prices obtained for each length of
	 * rod. Assumed to have all integers from 1 to length.
	 * @return The best price that can be obtained.
	 * */
	inline double bestRodCutTopDown(unsigned int length, std::map<unsigned int, double> prices) {
		double best_price = 0.0;
		return best_price;
	}
} // namespace RodCut

#endif ROD_CUT_H