#include <vector>	// vector
#include <iostream>	// cerr, endl
#include <stdexcept>	// runtime_error

#include "Reader.hpp"	// Reader
#include "Layer.hpp"

int main() {
	try {
		std::vector<char> imageBytes = Reader::readBytes("data/train-images-idx3-ubyte");
		Reader::readMetadata(imageBytes);
		std::vector<char> labelBytes = Reader::readBytes("data/train-labels-idx1-ubyte");
		Reader::readMetadata(labelBytes);

		Image img = Reader::readImage(imageBytes, labelBytes, 420);
		img.draw(28);
		std::vector<float> acts(img.bytes.begin(), img.bytes.end());
		for (unsigned int i = 0; i < acts.size(); i++) {
			acts[i] /= 255.f;
		}
		Layer input(28 * 28, nullptr);
		Layer hidden(64, &input);
		Layer output(10, &hidden);
		input.activations = Eigen::Map<Eigen::VectorXf>(acts.data(), acts.size());
		hidden.calculateActivations();
		output.calculateActivations();
		std::cout << output.activations << std::endl;
	} catch (std::runtime_error& e) {
		std::cerr << "Runtime error:\n\t" << e.what() << std::endl;
		return 1;
	}
	return 0;
}
