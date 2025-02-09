#pragma once

#include <iostream>
#include "Data.hpp"
#include <stdint.h>


class Serializer {
	private:
		Serializer(void);
		~Serializer(void);
		Serializer& operator=(const Serializer& rhs);
		Serializer(const Serializer& cpy);


	public:
		static uintptr_t serialize(Data* ptr);
		static Data* deserialize(uintptr_t raw);
};
