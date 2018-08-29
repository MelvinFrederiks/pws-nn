#include "Image.hpp"

#include <iostream>

void Image::draw(int width) {
	for (unsigned int i = 0; i < bytes.size(); i++) {
		char b = bytes[i];
		if (b != 0)
			std::cout << "█";
		else
			std::cout << " ";
		if (i % width == 0) {
			std::cout << std::endl;
		}
	}
}
