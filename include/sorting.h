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
namespace Sorting
{
	std::vector<double> insertionSort(const std::vector<double> &input)
	{
		auto output = input;
		for (size_t i = 1; i < output.size(); ++i)
		{
			double key = output[i];
			int j = i - 1;
			while (j >= 0 && output[j] > key)
			{
				output[j + 1] = output[j];
				j--;
			}
			output[j + 1] = key;
		}
		return output;
	}
} // namespace Sorting

#endif // SORTING_H