#ifndef MAX_SUBARRAY_H
#define MAX_SUBARRAY_H

#include <cmath>
#include <limits>
#include <stdexcept>
#include <tuple>
#include <vector>

/**
 * @brief This is a namespace with some under the hood functions.
 * 
 * These should generally not be called by the user unless you are
 * very sure what you are doing and have a very good reason for
 * doing so.
 * */
namespace detail {
	/**
	 * @brief Find the maximum subarray that is guaranteed to cross the value of mid.
	 * 
	 * Since the goal is to find a crossing array, this algorithm starts in the middle and
	 * extends out in each direction. At each new index, it computes the new total to determine
	 * if the inclusion of the extra element results in a larger sum total. Once finished,
	 * it adds both directions together for the complete crossing array.
	 * @param input The array to search.
	 * @param low The lowest index to include in the search.
	 * @param mid The middle value that is guaranteed to be part of the array.
	 * @param high The highest index to include in the search.
	 * @return A tuple with the lower and upper indices for the crossing array, as well as the
	 * total sum.
	 * */
	inline std::tuple<size_t, size_t, double> findMaxCrossingArray(const std::vector<float> & input, size_t low, size_t mid, size_t high) {
		double left_sum = std::numeric_limits<double>::lowest();
		double sum = 0.0;
		size_t max_left = mid;
		// If low is zero, this will wrap around to the max value. Since i starts at the midpoint, it
		// will always be less than size_t::max, so the only time the comparison will be true is if
		// the end of the iteration has truly been reached.
		for (size_t i = mid; i >= low && i != size_t(-1); --i) {
			sum += input[i];
			if (sum > left_sum) {
				left_sum = sum;
				max_left = i;
			}
		}
		double right_sum = std::numeric_limits<double>::lowest();
		sum = 0.0;
		size_t max_right = mid;
		for (size_t i = mid + 1; i <= high; ++i) {
			sum += input[i];
			if (sum > right_sum) {
				right_sum = sum;
				max_right = i;
			}
		}
		return std::make_tuple(max_left, max_right, left_sum + right_sum);
	}

	/**
	 * @brief Recursively find the maximum subarray.
	 * 
	 * This function considers three cases. Either the max array is entirely in the left, entirely
	 * in the right, or crosses some midpoint. This is then broken down into subproblems until the
	 * left and right are each only one element long. The results are then compared as the
	 * solution is reassembled. Each result is either a left or right for comparision in the next
	 * higher iteration.
	 * @param input The array to search through.
	 * @param low The smallest index to include.
	 * @param high The highest index to include.
	 * @return A tuple with the lower and upper indices for the maximum array, as well as the
	 * total sum.
	 * */
	inline std::tuple<size_t, size_t, double> findMaxSubarray(const std::vector<float> & input, size_t low, size_t high) {
		// If the array is only one element, the subarray is trivial to computer.
		if (high == low) {
			return std::make_tuple(low, high, input[low]);
		} else {
			// Since indices are always positive, casting will drop the decimal, which is
			// the equivalent of floor.
			size_t mid = static_cast<size_t>((low + high) / 2.0);
			size_t left_low;
			size_t left_high;
			size_t right_low;
			size_t right_high;
			size_t cross_low;
			size_t cross_high;
			double left_sum;
			double right_sum;
			double cross_sum;
			// Determine the three options
			std::tie(left_low, left_high, left_sum) = findMaxSubarray(input, low, mid);
			std::tie(right_low, right_high, right_sum) = findMaxSubarray(input, mid + 1, high);
			std::tie(cross_low, cross_high, cross_sum) = findMaxCrossingArray(input, low, mid, high);
			// Compare to see which is actually the maximum array.
			if (left_sum >= right_sum && left_sum >= cross_sum) {
				return std::make_tuple(left_low, left_high, left_sum);
			} else if (right_sum >= left_sum && right_sum >= cross_sum) {
				return std::make_tuple(right_low, right_high, right_sum);
			} else {
				return std::make_tuple(cross_low, cross_high, cross_sum);
			}
		}
	}
} // namespace detail

/**
 * @brief Find the subarray that contains the largest increase from start
 * to finish.
 * 
 * This will recursively look through the array to find max subarray. That
 * is defined as the array that produces the largest change when subtracting
 * its first element from its last.
 * @param The array to search.
 * @return A tuple containing (starting index, ending index, sum) where sum is
 * input[ending index] - input[starting index].
 * @throw std::invalid_argument Thrown if the provided array is less than two elements, as no
 * difference even exists in that case.
 * */
inline std::tuple<size_t, size_t, double> maxSubarray(const std::vector<float> & input) {
	// Verify that there are at least two elements in order to even form a difference between values.
	if (input.size() < 2) {
		throw std::invalid_argument("Provided array must have at least two elements.");
	}
	// First, create an array of differences.
	std::vector<float> differences;
	for (size_t i = 1; i < input.size(); ++i) {
		float difference = input[i] - input[i - 1];
		differences.push_back(difference);
	}
	// Now, call the recursive routine to find the array.
	auto result = detail::findMaxSubarray(differences, 0, differences.size() - 1);
	// These are indices for the difference array. Create the corresponding indices
	// for the actual array.
	size_t low_index = std::get<0>(result);
	size_t high_index = std::get<1>(result);
	double sum = std::get<2>(result);
	return std::make_tuple(low_index, high_index + 1, sum);
}
#endif // MAX_SUBARRAY_H