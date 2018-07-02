#include "Reader.hpp"

std::vector<char> Reader::readBytes(const char* path) {
	std::cout << "Reading " << path << "..." << std::endl;
	// Open het bestand in binary mode (er wordt geen preprocessing op het bestand gedaan)
	std::ifstream ifstr(path, std::ios::binary);
	// vector<T> heeft een constructor die 2 iterators aanneemt, een voor het begin en een voor het einde.
	// Deze constructor doet alle data tussen dit begin en eind in de vector.
	// streambuf_iterator<T>(stream) maakt een iterator die naar het begin van de stream wijst
	// De standaard constructor istreambuf_iterator<T>() maakt een zogenaamde "end-of-stream iterator"
	// 	die naar het einde van de stream wijst
	std::vector<char> res((std::istreambuf_iterator<char>(ifstr)), std::istreambuf_iterator<char>());
		
	std::cout << "Read " << res.size() << " bytes" << std::endl;
	
	return res;
}

bool Reader::readMetadata(std::vector<char> &data) {
	// Lees magic number uit data
	uint32_t magic = readMagic(data);
	bool isImage = false;
	std::cout << "Magic number: " << magic << " (";
	// Check of magic number correct is
	switch (magic) {
		case 2049:
			// 0x00000801 / 2049 = magic number voor label
			std::cout << "Labels)" << std::endl;
			break;
		case 2051:
			// 0x00000803 / 2051 = magic number voor afbeelding
			std::cout << "Images)" << std::endl;
			isImage = true;
			break;
		default:
			// Als een ander magic number wordt gevonden, throw een runtime_error
			std::cout << "n/a)" << std::endl;
			std::stringstream errStream;
			errStream << "Wrong magic number: expected 2049 or 2051, got ";
			errStream << magic;
			errStream << " instead!";
			throw std::runtime_error(errStream.str());
	}
	// Aantal items in dataset als gespecificeerd op http://yann.lecun.com/exdb/mnist
	std::cout << "Number of items: " << make32bit(data[4], data[5], data[6], data[7]) << std::endl;
	if (isImage) {
		// Afbeelding dimensies als gespecificeerd op http://yann.lecun.com/exdb/mnist
		std::cout << "Number of rows: " << make32bit(data[8], data[9], data[10], data[11]) << std::endl;
		std::cout << "Number of columns: " << make32bit(data[12], data[13], data[14], data[15]) << std::endl;
	}
	return isImage;
}

uint32_t Reader::make32bit(char b0, char b1, char b2, char b3) {
	// Maakt een unsigned 4-byte (32-bit) integer van 4 verschillende bytes
	// Voorbeeld:
	// make32bit(0b1000, 0b0100, 0b0010, 0b0001) -> 0b1000 0100 0010 0001 
	return (uint32_t) ((unsigned char) b0 << 24 | (unsigned char) b1 << 16 | 
			   (unsigned char) b2 << 8  | (unsigned char) b3);
}

uint32_t Reader::readMagic(const std::vector<char> &data) {
	// Leest de magic number van de data als gespecifeerd op http://yann.lecun.com/exdb/mnist
	return make32bit(data[0], data[1], data[2], data[3]);
}
