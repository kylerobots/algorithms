#include <iostream>

int main() {
	std::cout << "The version of C++ is ";
	switch (__cplusplus) {
		case 201703L:
			std::cout << "C++17";
			break;
		case 201402L:
			std::cout << "C++14";
			break;
		case 201103L:
			std::cout << "C++11";
			break;
		case 199711L:
			std::cout << "C++98";
			break;
		default:
			std::cout << "pre-standard C++ or Unknown.";
			break;
	}
	std::cout << std::endl;
	return 0;
}
