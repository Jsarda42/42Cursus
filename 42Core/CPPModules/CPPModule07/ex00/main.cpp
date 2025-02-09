#include "Whatever.hpp"
#include <iostream>


int main() {
	std::cout << "------------------------ int-----------------" << std::endl;
{	std::cout << "------------------------ smaller-------------" << std::endl;
	int data1 = 2;
	std::cout << "data1 is :" << data1 << std::endl;
	int data2 = 3;
	std::cout << "data2 is :" << data2 << std::endl;

	std::cout << "the min is : "  << min(data1, data2) << std::endl;}

{	std::cout << "------------------------ bigger -------------" << std::endl;
	int data1 = 5;
	std::cout << "data1 is :" << data1 << std::endl;
	int data2 = 3;
	std::cout << "data2 is :" << data2 << std::endl;
	std::cout << "the max is : " << max(data1, data2) << std::endl;}

{	std::cout << "------------------------ equal max-----------------" << std::endl;
	int data1 = 3;
	std::cout << "data1 is :" << data1 << std::endl;
	int data2 = 3;
	std::cout << "data2 is :" << data2 << std::endl;
	std::cout << "the result is : " << max(data1, data2) << std::endl;}

	{std::cout << "------------------------ equal min-----------------" << std::endl;
	int data1 = 3;
	std::cout << "data1 is :" << data1 << std::endl;
	int data2 = 3;
	std::cout << "data2 is :" << data2 << std::endl;
	std::cout << "the result is : " << min(data1, data2) << std::endl;}

	{std::cout << "------------------------ swap -----------------" << std::endl;
	int data1 = 2;
	std::cout << "data1 is :" << data1 << std::endl;
	int data2 = 3;
	std::cout << "data2 is :" << data2 << std::endl;
	std::cout << "swapping data : ....." << std::endl;
	swap(data1,data2);
	std::cout << "data1 is :" << data1 << std::endl;
	std::cout << "data2 is :" << data2 << std::endl;}


	std::cout << "------------------------ string -----------------" << std::endl;
	{	std::cout << "------------------------ smaller-------------" << std::endl;
	std::string data1 = "Data 1";
	std::cout << "data1 is :" << data1 << std::endl;
	std::string data2 = "Data 2";
	std::cout << "data2 is :" << data2 << std::endl;

	std::cout << "the min is : "  << ::min(data1, data2) << std::endl;}

{	std::cout << "------------------------ bigger -------------" << std::endl;
	std::string data1 = "Data 1";
	std::cout << "data1 is :" << data1 << std::endl;
	std::string data2 = "Data 2";
	std::cout << "data2 is :" << data2 << std::endl;
	std::cout << "the max is : " << ::max(data1, data2) << std::endl;}

{	std::cout << "------------------------ equal max-----------------" << std::endl;
	std::string data1 = "Data 2";
	std::cout << "data1 is :" << data1 << std::endl;
	std::string data2 = "Data 2";
	std::cout << "data2 is :" << data2 << std::endl;
	std::cout << "the result is : " << ::max(data1, data2) << std::endl;}

	{std::cout << "------------------------ equal min-----------------" << std::endl;
	std::string data1 = "Data 2";
	std::cout << "data1 is :" << data1 << std::endl;
	std::string data2 = "Data 2";
	std::cout << "data2 is :" << data2 << std::endl;
	std::cout << "the result is : " << ::min(data1, data2) << std::endl;}

	{std::cout << "------------------------ swap -----------------" << std::endl;
	std::string data1 = "Data 1";
	std::cout << "data1 is :" << data1 << std::endl;
	std::string data2 = "Data 2";
	std::cout << "data2 is :" << data2 << std::endl;
	std::cout << "swapping data : ....." << std::endl;
	swap(data1,data2);
	std::cout << "data1 is :" << data1 << std::endl;
	std::cout << "data2 is :" << data2 << std::endl;}
}
