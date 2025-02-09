#include "PmergeMe.hpp"
#include <cstdlib>
#include <limits>
#include <set>

template <typename T>
PmergeMe<T>::PmergeMe(void) {}

template <typename T>
PmergeMe<T>::PmergeMe(const PmergeMe& cpy){
	this = cpy;
}

template <typename T>
PmergeMe<T>& PmergeMe<T>::operator=(const PmergeMe& rhs) {
	this = rhs;
	return *this;
}

template <typename T>
PmergeMe<T>::~PmergeMe(void) {}

template <typename T>
void PmergeMe<T>::MergeSort(T &list, int left, int right, int threshold) {
	if (right - left + 1 <= threshold) {
		insertionSort(list, left, right);
		return;
	}

	int mid = left + (right - left) / 2;
	MergeSort(list, left, mid, threshold);
	MergeSort(list, mid + 1, right, threshold);
	Merge(list, left, mid, right);
}

template <typename T>
void PmergeMe<T>::Merge(T &list, int left, int mid, int right) {
	std::vector<int> temp(right - left + 1);
	int i = left;
	int j = mid + 1;
	unsigned long k = 0;

	while (i <= mid && j <= right) {
		if (list[i] <= list[j])
			temp[k++] = list[i++];
	else
		temp[k++] = list[j++];
	}

	while (i <= mid)
		temp[k++] = list[i++];

	while (j <= right)
		temp[k++] = list[j++];
	for (k = 0; k < temp.size(); ++k)
		list[left + k] = temp[k];
}

template <typename T>
void PmergeMe<T>::insertionSort(T &list, int left, int right) {
	for (int i = left + 1; i <= right; ++i) {
		typename T::value_type key = list[i];
		int j = i - 1;

		while (j >= left && list[j] > key) {
			list[j + 1] = list[j];
			--j;
		}
		list[j + 1] = key;
	}
}

template <typename T>
void PmergeMe<T>::sortList(T &list) {
	int threshold = 10;
	MergeSort(list, 0, list.size() - 1, threshold);
}

template <typename T>
void PmergeMe<T>::printList(const T list) {
	for (size_t i = 0; i < list.size();i++)
		std::cout << list[i] << " ";
}

template <typename T>
double PmergeMe<T>::size(const T list) {
	size_t i = 0;
	while (i < list.size())
		i++;
	return i;
}

template <typename T>
T PmergeMe<T>::processInput(int argc, char** input) {
	T list;
	std::set<int> seen;
	size_t size = list.size();
	for (int i = 1; i < argc; i++) {
		std::string current = input[i];

		if (current.empty())
			throw std::runtime_error("Invalid input (empty)");

		for (size_t j = 0; j < size; ++j)
			if (!std::isdigit(current[j]))
				throw std::runtime_error("Invalid input (contains non-numeric characters or negative value): " + current);

		long value = std::atoll(current.c_str());
		if (value < 0 || value > std::numeric_limits<int>::max())
			throw std::runtime_error("Input value out of range or negative: " + current);

		if (seen.find(static_cast<int>(value)) != seen.end())
			throw std::runtime_error("Duplicate value detected: " + current);
		seen.insert(static_cast<int>(value));
		list.push_back(static_cast<int>(value));
	}
	return list;
}
