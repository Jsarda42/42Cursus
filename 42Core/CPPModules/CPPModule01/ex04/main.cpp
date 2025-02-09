#include "ReplaceLine.hpp"

int main(int argc, char **argv){
	ReplaceLine replaceLine;
	std::string buffer;
	std::string line;

	if (argc != 4)
		return (std::cout << "Wrong number of arguments : Filename | String 1 | String 2\n", 1);
	std::string fileName = argv[1];
	std::string outFileName = fileName + ".replace";
	std::ifstream inputFile(fileName.c_str());
	if (inputFile.rdstate() & std::ifstream::failbit)
		return (std::cerr << "Error opening : " << fileName << std::endl, 1);
	std::ofstream outputFile(outFileName.c_str());
	if (outputFile.rdstate() & std::ofstream::failbit)
		return (std::cerr << "Error creating : " << outFileName << std::endl, 1);
	while (std::getline(inputFile, line)){
		buffer = replaceLine.replaceLine(line, argv[2], argv[3]);
		outputFile << buffer + "\n";
	}
	return (0);
}
