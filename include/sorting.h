#ifndef SORTING_H
#define SORTING_H

#include <cmath>
#include <limits>
#include <vector>

/**
 * @brief A collection of sorting algorithms discussed in class.
 * 
 * This includes insertion sort, ...
 * For now, this only works on std::vector<double> for simplicity,
 * unless otherwise noted. Future versions might expand to any
 * iterable.
 * */
namespace Sorting {
	std::vector<double> insertionSort(const std::vector<double> & input) {
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

	namespace {
		void merge(std::vector<double> & input, size_t p, size_t q, size_t r) {
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
		void mergeSort(std::vector<double> & input, size_t start_index, size_t end_index) {
			if (start_index < end_index) {
				size_t mid_index = std::floor((start_index + end_index) / 2);
				mergeSort(input, start_index, mid_index);
				mergeSort(input, mid_index + 1, end_index);
				merge(input, start_index, mid_index, end_index);
			}
		}
	} // namespace

	/**
	 * @brief Perform sorting via merge sort.
	 * 
	 * This method is faster than insertion sort, but does take up
	 * additional memory, due to the temporary arrays created.
	 * @param input A vector of numbers in any order.
	 * @return Those numbers sorted from smallest to largest.
	 * */
	std::vector<double> mergeSort(const std::vector<double> & input) {
		auto output = input;
		// The implementation doesn't work for empty vectors, do to underflow.
		// So check for that case here. If the vector is empty, it is already
		// sorted, so just return it.
		if (input.size() >= 1) {
			mergeSort(output, 0, input.size() - 1);
		}
		return output;
	}
} // namespace Sorting

#endif // SORTING_H