#ifndef SORTING_H
#define SORTING_H

#include <cmath>
#include <cstdint>
#include <limits>
#include <vector>

/**
 * @brief A collection of sorting algorithms discussed in class.
 * 
 * This includes the following algorithms and the types of inputs
 * the handle (stored within std::vector):
 * 
 * algorithm | input type
 * --------- | ----------
 * insertion | double
 * merge     | double
 * heap      | double
 * counting  | uint8_t
 * 
 * */
namespace Sorting {
	/**
	 * @brief Perform sort via insertion.
	 * 
	 * This is the simplist code, but also the most costly in terms of performance. It
	 * does operate in place though, so there are only fixed memory costs.
	 * 
	 * @param input The unsorted array.
	 * @return The provided array, sorted from least to greatest.
	 * */
	inline std::vector<double> insertionSort(const std::vector<double> & input) {
		auto output = input;
		for (size_t i = 1; i < output.size(); ++i) {
			double key = output[i];
			int j = i - 1;
			while (j >= 0 && output[j] > key) {
				output[j + 1] = output[j];
				j--;
			}
			output[j + 1] = key;
		}
		return output;
	}

	/**
	 * @brief This is a namespace with some under the hood functions.
	 * 
	 * These should generally not be called by the user unless you are
	 * very sure what you are doing and have a very good reason for
	 * doing so.
	 * */
	namespace detail {
		/**
		 * @brief The helper function that performs the actual merge of mergesort.
		 * 
		 * This creates the two stacks, which are already in sorted order, and pops whichever
		 * value off the top is smaller. This leads to a single array that is completely sorted.
		 * @param input The array to sort. This will be operated on in-place.
		 * @param p The smallest index to include in the sort.
		 * @param q The midpoint of the sorting selection. It is assumed that and values from [p, q]
		 * are already sorted as well as all values from [q+1, r].
		 * @param r The largest index to include in the sort.
		 * */
		inline void merge(std::vector<double> & input, size_t p, size_t q, size_t r) {
			size_t size_left = q - p + 1;
			size_t size_right = r - q;
			std::vector<double> left;
			std::vector<double> right;
			for (size_t i = 0; i < size_left; ++i) {
				left.push_back(input[p + i]);
			}
			for (size_t i = 1; i <= size_right; ++i) {
				right.push_back(input[q + i]);
			}
			left.push_back(std::numeric_limits<double>::max());
			right.push_back(std::numeric_limits<double>::max());
			size_t i = 0;
			size_t j = 0;
			for (size_t k = p; k <= r; ++k) {
				if (left[i] <= right[j]) {
					input[k] = left[i];
					i++;
				} else {
					input[k] = right[j];
					j++;
				}
			}
		}

		/**
		 * @brief A helper function for merge sort that divides the problem.
		 * 
		 * This method recursively divides up the array into half. Eventually, the problem is broken
		 * down into individual elements, which are by definition sorted. This then uses @ref merge
		 * to combine the elements back together in sorted order.
		 * @param input The vector to operate on. This will be modified in place.
		 * @param start_index The smallest index to consider in sorting.
		 * @param end_index The largest index to consider in sorting.
		 * */
		inline void mergeSort(std::vector<double> & input, size_t start_index, size_t end_index) {
			if (start_index < end_index) {
				size_t mid_index = std::floor((start_index + end_index) / 2);
				detail::mergeSort(input, start_index, mid_index);
				detail::mergeSort(input, mid_index + 1, end_index);
				detail::merge(input, start_index, mid_index, end_index);
			}
		}
	} // namespace detail

	/**
	 * @brief Perform sorting via merge sort.
	 * 
	 * This method is faster than insertion sort, but does take up
	 * additional memory, due to the temporary arrays created.
	 * @param input A vector of numbers in any order.
	 * @return Those numbers sorted from smallest to largest.
	 * */
	inline std::vector<double> mergeSort(const std::vector<double> & input) {
		auto output = input;
		// The implementation doesn't work for empty vectors, do to underflow.
		// So check for that case here. If the vector is empty, it is already
		// sorted, so just return it.
		if (input.size() >= 1) {
			detail::mergeSort(output, 0, input.size() - 1);
		}
		return output;
	}

	/**
	 * @brief Perform sorting via heap sort.
	 * 
	 * This method builds a heap out of the data then reads it in printed
	 * order. The heap is representative of a binary structure, so is easy
	 * to traverse after. Various subfunctions ensure that the heap property
	 * is maintained. Unlike @ref mergeSort, this sorts in place.
	 * @param input A vector of numbers in any order.
	 * @return Those numbers sorted from smallest to largest.
	 * */
	inline std::vector<double> heapSort(const std::vector<double> & input) {
		auto output = input;
		return output;
	}

	/**
	 * @brief Perform sorting via counting sort.
	 * 
	 * This method assumes the input is all nonnegative integers. It sorts
	 * by counting up the number of instances of each possible integer and
	 * using that to determine where that integer should be placed within
	 * the ouput array.
	 * @param input A vector of unsorting integers >= 0.
	 * @return Those numbers sorted from smallest to largest.
	 * */
	inline std::vector<uint8_t> countingSort(const std::vector<uint8_t> & input) {
		auto output = input;
		// Allocate space to count the occurances of each digit.
		std::vector<int> value_counts(std::numeric_limits<uint8_t>::max() + 1, 0);
		// Fill the array with counts of the occurence of each index value.
		for (auto && i : input) {
			value_counts[i]++;
		}
		// Now go through and perform summations to account for multiple instances
		// of the same value.
		for (size_t i = 1; i < value_counts.size(); ++i) {
			value_counts[i] += value_counts[i - 1];
		}
		// Use these counts to determine where each element should go in the output
		// array.
		for (size_t i = input.size() - 1; i < static_cast<size_t>(-1); --i) {
			// Determine which value is currently under consideration.
			uint8_t current_value = input[i];
			// Find how many elements occur before it
			auto index_position = value_counts[current_value] - 1;
			// Use that number of items to place it in the appropriate spot in
			// the sorted array.
			output[index_position] = current_value;
			// output[value_counts[input[i]]] = input[i];
			// Decrement each count so items don't get overwritten.
			value_counts[current_value] -= 1;
		}
		return output;
	}
} // namespace Sorting

#endif // SORTING_H