#ifndef SORTING_H
#define SORTING_H

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
		}
		void mergeSort(std::vector<double> & input, size_t start_index, size_t end_index) {
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