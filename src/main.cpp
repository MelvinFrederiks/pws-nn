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
		for (unsigned int c = 0; c < 10; c++) {
			Image img = Reader::readImage(imageBytes, labelBytes, c);
			for (unsigned int i = 0; i < img.bytes.size(); i++) {
				char b = img.bytes[i];
				if (b != 0)
					std::cout << "█";
				else
					std::cout << " ";
				if (i % 28 == 0) {
					std::cout << std::endl;
				}
			}
			std::cout << "\nLabel: " << img.digit << std::endl;
		}
	} catch (std::runtime_error& e) {
		std::cerr << "Runtime error:\n\t" << e.what() << std::endl;
		return 1;
	}
	return 0;
}
