#pragma once

template<typename T>
const T min(T data1, T data2) {
	return data1 < data2 ? data1 : data2;
}

template<typename T>
const T max(T data1, T data2) {
	return data1 > data2 ? data1 : data2;
}

template<typename T>
void swap(T &data1, T &data2) {
	T tmp;

	tmp = data1;
	data1 = data2;
	data2 = tmp;
}
