#pragma once
#include <iostream>
#include <vector>
#include <deque>

template <typename T>
class PmergeMe {

	private:

	public:
		PmergeMe(void);
		PmergeMe(const PmergeMe& cpy);
		PmergeMe& operator=(const PmergeMe& rhs);
		~PmergeMe(void);

		void printList(const T list);
		void sortList(T &list);
		void insertionSort(T &List, int left, int right);
		void Merge(T &List, int left, int mid, int right);
		double size(const T List);
		void MergeSort(T &list, int left, int right, int threshold);
		T processInput(int argc, char** input);
};

#include "PmergeMe.tpp"
