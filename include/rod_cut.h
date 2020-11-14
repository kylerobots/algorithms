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
	 * @brief This is a namespace with some under the hood functions.
	 * 
	 * These should generally not be called by the user unless you are
	 * very sure what you are doing and have a very good reason for
	 * doing so.
	 * */
	namespace detail {
		/**
		 * @brief Performs the actual top down memoization.
		 * 
		 * This is just a recursive call that calls each sub solution
		 * if it doesn't already have a value computed.
		 * @param length The length to find a solution for.
		 * @param prices The prices for each length.
		 * @param solutions The vector of solutions for each length.
		 * @return The best prices for a rod of length @ref length.
		 * */
		inline double memoizedCutRod(unsigned int length, const std::map<unsigned int, double> & prices, std::vector<double> solutions) {
			// Return a value if it has already been computed.
			if (solutions[length] >= 0) {
				return solutions[length];
			}
			double best_price;
			// We know a length of 0 has a price of 0.0.
			if (length == 0) {
				best_price = 0.0;
			} else {
				best_price = std::numeric_limits<double>::lowest();
				// Recursively calculate the optimal solution for this
				// length by picking the first cut and computing the
				// optimal solution for the remaining length.
				for (unsigned int i = 1; i <= length; ++i) {
					double candidate_price = prices.at(i) + memoizedCutRod(length - i, prices, solutions);
					best_price = std::max(best_price, candidate_price);
				}
			}
			// Store this price for future lookup.
			solutions[length] = best_price;
			return best_price;
		}
	} // namespace detail

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
			for (unsigned int j = 1; j <= i; ++j) {
				// Prices[j] represents the price for the first cut. Solutions[i-j]
				// is then the ideal price for the remaining length.
				best_price = std::max(best_price, prices.at(j) + solutions[i - j]);
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
		std::vector<double> solutions(length + 1, std::numeric_limits<double>::lowest());
		return detail::memoizedCutRod(length, prices, solutions);
	}
} // namespace RodCut

#endif // ROD_CUT_H