#ifndef ROD_CUT_H
#define ROD_CUT_H

#include <limits>
#include <map>
#include <vector>

/**
 * @brief A collection of methods to compute the optimal way to cut a rod.
 * 
 * This provides two methods to compute the best way to cut a rod to maximize
 * profit, when given the price of different lengths of rods. It assumes all
 * cuts are whole units of measure. The two methods are both dynamic programming
 * methods - bottom-up and top-down methods. These work because the problem
 * has an optimal substructure. An optimal cut has a first cut on the rod, then
 * an optimal combination of cuts for the rest of the rod.
 * */
namespace RodCut {
	/**
	 * @brief Calculate the optimal cut pattern for a rod with bottom-up
	 * calculations.
	 * 
	 * This uses a bottoms up approach by calculating all the ideal prices
	 * for the subproblems from 1 to length. Then the solution is just
	 * combinations of these precomputed values.
	 * @param length The uncut length of the rod.
	 * @param prices A map of the prices obstained for each length of
	 * rod. Assumed to have all integers from 1 to length.
	 * @return The best price that can be obtained.
	 * */
	inline double bestRodCutBottomUp(unsigned int length, std::map<unsigned int, double> prices) {
		// Create the storage for the computed values.
		std::vector<double> solutions(length + 1, 0.0);
		solutions[0] = 0.0;
		for (size_t i = 1; i <= length; ++i) {
			double best_price = std::numeric_limits<double>::lowest();
			// The solution is determined by the exploration of all possible
			// first cuts plus the optimal solution of the remaining length.
			// Since this is bottom up, the remaining length solutions have
			// already been computed.
			for (size_t j = 1; j <= i; ++j) {
				// Prices[j] represents the price for the first cut. Solutions[i-j]
				// is then the ideal price for the remaining length.
				best_price = std::max(best_price, prices[j] + solutions[i - j]);
			}
			// Store the best price for this length for use by higher solutions.
			solutions[i] = best_price;
		}
		return solutions[length];
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

#endif // ROD_CUT_H