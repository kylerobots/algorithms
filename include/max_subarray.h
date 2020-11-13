#ifndef MAX_SUBARRAY_H
#define MAX_SUBARRAY_H

#include <tuple>
#include <vector>

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
 * */
std::tuple<size_t, size_t, double> maxSubarray(const std::vector<float> & input) {
	return std::make_tuple(0, input.size() - 1, 0.0);
}
#endif // MAX_SUBARRAY_H