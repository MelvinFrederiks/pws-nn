#include "Image.hpp"

#include <iostream>

void Image::draw(int width) {
	// Loop door alle bytes
	for (unsigned int i = 0; i < bytes.size(); i++) {
		char b = bytes[i];
		// Als de huidige bytes niet 0 is (grijs-zwart), print een karakter
		if (b != 0)
			std::cout << "█";
		// Als de huidige bytes 0 is (wit), print niks
		else
			std::cout << " ";
		// als het einde van de regel bereikt is, print een newline
		if (i % width == 0) {
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}
