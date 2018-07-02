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

// Klasse voor het lezen en interpreteren van de dataset
class Reader {
public:
	// Lees alleen de bytes uit een bestand zonder er enige operaties op uit te voeren
	static std::vector<char> readBytes(const char* path);
	// Lees de metadata uit gelezen bytes (aannemend dat de data in het formaat is als gespecificeerd op http://yann.lecun.com/exdb/mnist)
	static bool readMetadata(std::vector<char> &data);
private:
	// Zet 4 1-byte (8-bit) integer om in 1 4-byte (32-bit) integer
	static uint32_t make32bit(char b0, char b1, char b2, char b3);
	// Lees het magic number uit gelezen bytes (aannemend dat de data in het formaat is als gespecificeerd op http://yann.lecun.com/exdb/mnist)
	static uint32_t readMagic(const std::vector<char> &data);
};

#endif
