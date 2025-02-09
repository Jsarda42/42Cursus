#include "Serializer.hpp"
#include "Data.hpp"

int main() {
	Data d;
	d.lmum = 1000000000000L;
	d.name_ = "juju";
	d.num_ = 2;

	uintptr_t raw = Serializer::serialize(&d);
	Data* deserializedData = Serializer::deserialize(raw);
	std::cout << "Original Data: " << d.name_ << ", " << d.lmum << ", " << d.num_ << std::endl;
	std::cout << "Deserialized Data: " << deserializedData->name_ << ", "<< deserializedData->lmum << ", " << deserializedData->num_ << std::endl;

	return 0;
}
