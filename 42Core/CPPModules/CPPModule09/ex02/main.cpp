#include "PmergeMe.hpp"
#include <vector>
#include <deque>
#include <ctime>
#include <iomanip>
#include <iostream>

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "Error: At least one argument is required.\n";
		return 1;
	}

	try {
		PmergeMe< std::vector<int> > vectorSorter;

		clock_t startVector = clock();
		std::vector<int> vectorList = vectorSorter.processInput(argc, argv);
		std::cout << "Before : ";
		vectorSorter.printList(vectorList);
		std::cout << std::endl;
		vectorSorter.sortList(vectorList);
		std::cout << "After : ";
		vectorSorter.printList(vectorList);
		std::cout << std::endl;
		clock_t endVector = clock();
		double elapsedTimeVector = static_cast<double>(endVector - startVector) / CLOCKS_PER_SEC * 1e3;
		std::cout << std::fixed << std::setprecision(2)
			<< "Time to process a range of " << vectorList.size()
			<< " elements with std::vector: " << elapsedTimeVector << " ms" << std::endl;

		PmergeMe< std::deque<int> > dequeSorter;

        clock_t startDeque = clock();
		std::deque<int> dequeList = dequeSorter.processInput(argc, argv);
		dequeSorter.sortList(dequeList);
		clock_t endDeque = clock();
		double elapsedTimeDeque = static_cast<double>(endDeque - startDeque) / CLOCKS_PER_SEC * 1e3;
		std::cout << std::fixed << std::setprecision(2)
				<< "Time to process a range of " << dequeList.size()
				<< " elements with std::deque: " << elapsedTimeDeque << " ms" << std::endl;

	} 
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << "\n";
		return 1;
	}

	return 0;
}
