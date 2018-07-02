#include <vector>	// vector
#include <iostream>	// cerr, endl
#include <stdexcept>	// runtime_error

#include "Reader.hpp"	// Reader

int main() {
	try {
		std::vector<char> imageBytes = Reader::readBytes("data/train-images-idx3-ubyte");
		Reader::readMetadata(imageBytes);
		std::vector<char> labelBytes = Reader::readBytes("data/train-labels-idx1-ubyte");
		Reader::readMetadata(labelBytes);
	} catch (std::runtime_error& e) {
		std::cerr << "Runtime error:\n\t" << e.what() << std::endl;
		return 1;
	}
	return 0;
}
