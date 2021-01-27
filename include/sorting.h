#ifndef SORTING_H
#define SORTING_H

#include <cmath>
#include <cstdint>
#include <limits>
#include <stdexcept>
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
 * quick     | double
 * counting  | uint8_t
 * radix     | unsigned int
 * bucket    | double in the range [0, 1)
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
			// Since i starts at 1, j never starts less than zero.
			size_t j = i - 1;
			while (j != size_t(-1) && output[j] > key) {
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
		 * @brief Converts an array to have the heap property.
		 * 
		 * This recursively ensures that a given vector satisfies the heap property
		 * with the first, root element being the maximum. This is called
		 * recursively and assumes that all elements lower than lowest_index
		 * already meet the heap property. It takes the target index and moves it
		 * into the correct spot down the array to maintain the heap property.
		 * @param array The array to make into a heap.
		 * @param heap_size The maximum element that is considered part of the heap.
		 * @param current_index The current index to consider. It assumes all
		 * larger then this are already in heap order.
		 * */
		inline void maxHeapify(std::vector<double> & array, size_t heap_size, size_t current_index) {
			size_t left = 2 * current_index + 1;
			size_t right = 2 * current_index + 2;
			size_t largest = current_index;
			// Determine if the target value is smaller than its potential
			// children, which violates the heap property.
			if (left <= heap_size - 1 && array[left] > array[current_index]) {
				largest = left;
			}
			if (right <= heap_size - 1 && array[right] > array[largest]) {
				largest = right;
			}
			// If it is smaller, replace it with the largest child, which
			// restores the heap property.
			if (largest != current_index) {
				double key = array[current_index];
				array[current_index] = array[largest];
				array[largest] = key;
				// Continue down the tree to verify that the new location does
				// not violate the heap property for one of its new children.
				maxHeapify(array, heap_size, largest);
			}
		}

		/**
		 * @brief Build a heap-like array for sorting via Heap sort.
		 * 
		 * This puts the array in such an order that its heap property is
		 * maintained. It does this by inserting elements and calling
		 * @ref maxHeapify to ensure compliance with the heap property.
		 * @param input The array to heapify.
		 * @return The array in heap structure.
		 * */
		inline std::vector<double> buildMaxHeap(const std::vector<double> & input) {
			auto result = input;
			// The leaves are guaranteed to be in heap order, since they have
			// no children. So skip past them for fixing the heap.
			// Since the index is always 0 or positive, casting to size_t is the
			// same as the floor operation.
			size_t start_index = static_cast<size_t>((result.size() - 1) / 2.0);
			for (size_t i = start_index; i != static_cast<size_t>(-1); --i) {
				detail::maxHeapify(result, result.size(), i);
			}
			return result;
		}

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
				// Since an index is always 0 or positive, casting to size_t is the same
				// as the floor operation.
				size_t mid_index = static_cast<size_t>((start_index + end_index) / 2);
				detail::mergeSort(input, start_index, mid_index);
				detail::mergeSort(input, mid_index + 1, end_index);
				detail::merge(input, start_index, mid_index, end_index);
			}
		}

		/**
		 * @brief Perform the partition operation for quick sort.
		 * 
		 * This function takes the last value in the supplied range and uses
		 * it as a pivot. It then walks through the array and ensures that each
		 * value less then the pivot is on the left and greater than on the right.
		 * It will then put the pivot in the middle of the array.
		 * @param input The array to partition.
		 * @param start_index The first index to include in the partition.
		 * @param end_index The last index to include in the partition.
		 * @return The index around which the array is partitioned.
		 * */
		inline size_t quickPartition(std::vector<double> & input, size_t start_index, size_t end_index) {
			double pivot_value = input[end_index];
			// Track where the pivot should go
			size_t pivot_index = start_index - 1;
			for (size_t i = start_index; i < end_index; ++i) {
				// Go through each element. If it is less then the pivot,
				// it should be on the left, so increment where the pivot will
				// ultimately be placed.
				if (input[i] <= pivot_value) {
					pivot_index++;
					// Then, move the value to the last spot of the left items.
					double key = input[pivot_index];
					input[pivot_index] = input[i];
					input[i] = key;
				}
			}
			// Once everything is partitioned, put the pivot in the right spot.
			double key = input[pivot_index + 1];
			input[pivot_index + 1] = input[end_index];
			input[end_index] = key;
			return pivot_index + 1;
		}

		/**
		 * @brief A helper function for the quicksort divide and conquer.
		 * 
		 * This part partitions each array, then calls itself for each partition.
		 * @param input The array to sort.
		 * @param start_index The first index to include in the sort.
		 * @param end_index The last index to include in the sort.
		 * @*/
		inline void quickSort(std::vector<double> & input, size_t start_index, size_t end_index) {
			// Since the index is unsigned, it might roll over. This only happens to the end_index,
			// if it was provided a pivot_index of 0 in the higher recursion. So just watch if that
			// value is size_t::max, it is really -1.
			if (start_index < end_index && end_index != size_t(-1)) {
				size_t pivot_index = quickPartition(input, start_index, end_index);
				quickSort(input, start_index, pivot_index - 1);
				quickSort(input, pivot_index + 1, end_index);
			}
		}

		/**
		 * @brief A modified counting sort that operates on a single digit for each number.
		 * 
		 * This uses the same algorithm as @ref countingSort, but only compares a single digit
		 * for each number, rather than the whole number. Because of that, it only needs to
		 * allocate 10 spaces for the count.
		 * @param input The vector to sort.
		 * @param digit The digit index to sort on. 0 = ones place, 1 = tens place, etc.
		 * @return The array sorted on the select digit.
		 * */
		inline std::vector<unsigned int> radixCountSort(const std::vector<unsigned int> & input, unsigned int digit) {
			auto output = input;
			// Allocate space to count the occurrence of each digit. There is at most
			// 10 numbers to consider.
			std::vector<unsigned int> value_counts(10, 0);
			// Count the occurrence of each digit.
			for (auto && i : input) {
				// The digit under consideration is found by:
				// value = (number / 10^digit) % 10
				// The parenthesis moves the target digit to the ones place. The modulus
				// then determines the remainder to figure out what this digit is. Since
				// we are looking for an integer anyways, don't worry about truncating
				// from rounding.
				unsigned int value = static_cast<unsigned int>((i / std::pow(10, digit))) % 10;
				value_counts[value]++;
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
				unsigned int current_value = static_cast<unsigned int>((input[i] / std::pow(10, digit))) % 10;
				// Find how many elements occur before it
				auto index_position = value_counts[current_value] - 1;
				// Use that number of items to place it in the appropriate spot in
				// the sorted array.
				output[index_position] = input[i];
				// output[value_counts[input[i]]] = input[i];
				// Decrement each count so items don't get overwritten.
				value_counts[current_value] -= 1;
			}
			return output;
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
	 * order. The heap is a max heap, meaning each element is greater than
	 * its parents. Therefore, it is easy to traverse to get an ordered
	 * array. Various subfunctions ensure that the heap property is maintained.
	 * Unlike @ref mergeSort, this sorts in place.
	 * @param input A vector of numbers in any order.
	 * @return Those numbers sorted from smallest to largest.
	 * */
	inline std::vector<double> heapSort(const std::vector<double> & input) {
		// This won't work for empty arrays because of the comparisions, so
		// just return if so.
		if (input.size() < 1) {
			return input;
		}
		// First, build the heap structure
		auto output = detail::buildMaxHeap(input);
		size_t heap_size = output.size();
		// Since the heap is ordered with the max element in the first position,
		// move that element to the last position and reapply the heap
		// property. We don't need to do 0, since it will be in the
		// right spot by default.
		for (size_t i = heap_size - 1; i > 0; --i) {
			double key = output[i];
			output[i] = output[0];
			output[0] = key;
			heap_size--;
			detail::maxHeapify(output, heap_size, 0);
		}
		return output;
	}

	/**
	 * @brief Perform sorting via quicksort.
	 * 
	 * This method uses quicksort, which recursively partitions the data into
	 * halves that are greater or less than a selected pivot value. Eventually,
	 * the halves are small enough that they are automatically sorted. This is
	 * the same asymptotic complexity as some oft the other algorithms, but
	 * often performs faster. There is a randomized version that avoids the
	 * worst case. This is not that version.
	 * @param input A vector of unsorted numbers.
	 * @return Those numbers sorted from smallest to largest.
	 * */
	inline std::vector<double> quickSort(const std::vector<double> & input) {
		auto output = input;
		// Watch for the empty case.
		if (input.size() > 0) {
			detail::quickSort(output, 0, output.size() - 1);
		}
		return output;
	}

	/**
	 * @brief Perform sorting via counting sort.
	 * 
	 * This method assumes the input is all nonnegative integers. It sorts
	 * by counting up the number of instances of each possible integer and
	 * using that to determine where that integer should be placed within
	 * the ouput array.
	 * @param input A vector of unsorted integers >= 0.
	 * @return Those numbers sorted from smallest to largest.
	 * */
	inline std::vector<uint8_t> countingSort(const std::vector<uint8_t> & input) {
		auto output = input;
		// Allocate space to count the occurrences of each digit.
		std::vector<int> value_counts(std::numeric_limits<uint8_t>::max() + 1, 0);
		// Fill the array with counts of the occurrence of each index value.
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

	/**
	 * @brief Perform sorting via radix sort.
	 * 
	 * This uses a radix sort to sort on each digit from least to most significant
	 * digit. It then uses a modified counting sort algorithm under the hood for
	 * the actual sort.
	 * @param input A vector of unsorted integers >= 0.
	 * @return Those numbers sorted from smallest to largest.
	 * */
	inline std::vector<unsigned int> radixSort(const std::vector<unsigned int> & input) {
		auto output = input;
		// Watch for empty arrays, since they won't sort correctly.
		if (input.size() == 0) {
			return output;
		}
		// Determine the max number to determine which digit to iterate up to.
		unsigned int max = 0;
		for (auto && number : input) {
			max = std::max(max, number);
		}
		// The floor of log10 determines the index, since we are starting from 0. Since
		// log10(10) = 1, anything less (AKA 1 digit) will be 0. Then anytime a new digit
		// is added to the number, the result of log10 will also increase one. Because of
		// the floor, casting to int won't lose any data.
		unsigned int max_digit = static_cast<unsigned int>(std::floor(std::log10(max)));
		for (unsigned int i = 0; i <= max_digit; ++i) {
			output = detail::radixCountSort(output, i);
		}
		return output;
	}

	/**
	 * @brief Perform sorting via bucket sort.
	 * 
	 * This algorithm divides the valid range for the sort into n uniform buckets. It then
	 * places each number into the appropriate bucket. These buckets are then sorted via
	 * insertion sort. The buckets are then reassembled. Because the buckets contain only
	 * a few items, the insertion sort is fast.
	 * 
	 * @note This can be expanded to any nonnegative value by normalizing the values when
	 * placing into buckets. However, this will stick with the method shown in the book.
	 * 
	 * @param input A vector of unsorted numbers in the range [0, 1).
	 * @return Those numbers sorted from smallest to largest.
	 * @throw std::out_of_range Thrown if a number is outside the range [0, 1)
	 * */
	inline std::vector<double> bucketSort(const std::vector<double> & input) {
		// Create each bucket
		std::vector<std::vector<double>> buckets(input.size(), std::vector<double>());
		// Place each number into a bucket. Since numbers are on the range [0, 1),
		// multiplying by the total count of numbers ensures the floor yields the index
		// that number should be placed in. This is because the number of buckets is
		// also based on the total count of numbers. For example, consider 4 numbers.
		// The second bucket is the range [0.25, 0.5). So floor(4 * 0.3) = 1, which is
		// the right index.
		for (auto && i : input) {
			// Check that the value is in the correct range.
			if (i >= 1.0 || i < 0.0) {
				throw std::out_of_range("Keys must be in the range [0, )");
			}
			// Floor ensures the result is an integer, so is safe to cast.
			size_t index = static_cast<size_t>(std::floor(input.size() * i));
			buckets[index].push_back(i);
		}
		// Now sort each bucket using insertion sort. Although any sort would work.
		// As the results are returned, place them in the output array.
		std::vector<double> output;
		for (auto && bucket : buckets) {
			auto sorted_bucket = insertionSort(bucket);
			for (auto && value : sorted_bucket) {
				output.push_back(value);
			}
		}
		return output;
	}
} // namespace Sorting

#endif // SORTING_H