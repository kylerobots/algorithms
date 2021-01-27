# Algorithms #
A collection of implementations from my Algorithms class. This is done to practice their implementation, since practice makes perfect. They all use Google Test's framework for unit testing.

## Algorithm Overview ##
There are a number of algorithms in this collection. Some are implemented as classes, some as functions, depending on
the best fit. They all come from an introductory algorithms course. The current list includes:

- Comparison Sorting Algorithms
	- Insertion Sort
	- Merge Sort
	- Heap Sort
	- Quick Sort
- Other Sorts
	- Counting Sort
	- Bucket Sort
	- Radix Sort
- Binary Trees
- Longest Common Substring
- Maximum Sub Array

More are still to come, but my course load picked up and I wasn't able to add additional algorithms as I learned them.
Additionally, I chose to simplify things by avoiding templating. So most algorithms are targeted at a specific data
type, such as a vector of floats. As this is a practice repository, I felt this was reasonable.

## Implementation ##
If you wish to use this library, it is set up as a header only library via CMake. The compile time is fairly quick, so
including it should not add too much overhead.

## Unit Testing ##
The code uses Google Test for unit testing. The CMakeLists file is structured to automatically download Google Test
into a subfolder within the *build* folder if it isn't already there. This comes per their recommendation. Any future
algorithms should include their own test files as well. A GitHub action ensures that the code compiles and passes all
tests on several different platforms prior to allowing any merge into main.