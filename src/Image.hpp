#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector> // vector

// Struct om data voor een image en het bijbehorende label te bewaren
struct Image {
public:
	// Image data
	std::vector<char> bytes;
	// Label
	short digit;
	
	// Print een representatie van Image struct
	void draw(int width);
};

#endif
