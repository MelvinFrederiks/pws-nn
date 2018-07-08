#ifndef READER_HPP
#define READER_HPP

#include <stdint.h> 	// uint32_t
#include <vector>	// vector
#include <iostream>	// cout, endl
#include <ios>		// ios
#include <fstream>	// ifstream
#include <iterator>	// istreambuf_iterator
#include <sstream>	// stringstream	
#include <stdexcept>	// runtime_error

#include "Image.hpp"	// Image

// Klasse voor het lezen en interpreteren van de dataset
class Reader {
public:
	// Lees alleen de bytes uit een bestand zonder er enige operaties op uit te voeren
	static std::vector<char> readBytes(const char* path);
	// Lees de metadata uit gelezen bytes (aannemend dat de data in het formaat is als gespecificeerd op http://yann.lecun.com/exdb/mnist)
	static bool readMetadata(const std::vector<char> &data);
	// Lees bytes uit de image data voor de gegeven index
	static std::vector<char> readImageBytes(const std::vector<char> &bytes, int idx);
	// Lees byte uit de label data voor de gegeven index
	static short readLabel(const std::vector<char> &bytes, int idx);
	// Lees image bytes en bijbehorende label en returnt het in een Image struct
	static Image readImage(const std::vector<char> &imageBytes, const std::vector<char> &labelBytes, int idx);
private:
	// Zet 4 1-byte (8-bit) integers om in 1 4-byte (32-bit) integer
	static uint32_t make32bit(const char b0, const char b1, const char b2, const char b3);
	// Lees het magic number uit gelezen bytes (aannemend dat de data in het formaat is als gespecificeerd op http://yann.lecun.com/exdb/mnist)
	static uint32_t readMagic(const std::vector<char> &data);
};

#endif
