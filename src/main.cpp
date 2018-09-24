#include <vector>	// vector
#include <iostream>	// cerr, endl
#include <stdexcept>	// runtime_error

#include <random>
#include <ctime>

#include <Eigen/LU>

#include "Reader.hpp"	// Reader
#include "Layer.hpp"
#include "Utils.hpp"

#include <fstream>


#define ITERATIONS 50000
#define RATE 0.46875f

int main() {
	try {
		std::vector<char> imageBytes = Reader::readBytes("data/train-images-idx3-ubyte");
		Reader::readMetadata(imageBytes);
		std::vector<char> labelBytes = Reader::readBytes("data/train-labels-idx1-ubyte");
		Reader::readMetadata(labelBytes);

		std::ofstream csvFile;
		csvFile.open("testData_rateFixed.txt");

		srand(time(NULL));
		std::minstd_rand generator(std::time(0));
		std::uniform_int_distribution<> dist(0, 59999);
		Layer input(28 * 28, nullptr);
		Layer hidden(64, &input);
		Layer output(10, &hidden);
		Image img;
		std::vector<float> acts;
		Eigen::VectorXf desired(10);
		Eigen::VectorXf outputError(10);
		Eigen::VectorXf hiddenError(hidden.activations.size());
		
		for (int epoch = 0; epoch < 100; epoch++) {
			std::cout << "\n\nSTARTING EPOCH " << epoch + 1 << std::endl;
			float mse = 0;
			int correct = 0;
		
			std::cout << std::endl;
			for (int i = 0; i < ITERATIONS; i++) {
				// Forward pass
				std::cout << "\rSTARTING ITERATION " << i + 1;
				img = Reader::readImage(imageBytes, labelBytes, i);
				acts = std::vector<float>(img.bytes.begin(), img.bytes.end());
				for (unsigned int i = 0; i < acts.size(); i++) {
					acts[i] /= 255.f;
				}
			
				input.activations = Eigen::Map<Eigen::VectorXf>(acts.data(), acts.size());
				hidden.calculateActivations();
				output.calculateActivations();
				desired = Utils::getDesiredVector(img.digit);
				if (Utils::getResult(output.activations) == desired)
					correct++;
				mse += pow(Utils::vectorDiffLen(desired, output.activations), 2);

				// Backwards pass
				// deltaL = (y - y^) (.) s'(zL)
				outputError = output.activations - desired;
				
				for (int c = 0; c < output.activations.size(); c++) {
					// hadamard multiplication
					outputError(c) *= Utils::sigmoidDerivative(output.weightedInput(c));
				}
				
				hiddenError = output.weights.transpose() * outputError;
				for (int c = 0; c < hidden.activations.size(); c++) {
					hiddenError(c) *= Utils::sigmoidDerivative(hidden.weightedInput(c));
				}
				
				hidden.bias += hiddenError * -RATE;
				output.bias += outputError * -RATE;
				
				for (int row = 0; row < output.weights.rows(); row++) {
					for (int col = 0; col < output.weights.cols(); col++) {
						output.weights(row, col) += output.prev->activations(col) * outputError(row) * -RATE;
					}
				}
				for (int row = 0; row < hidden.weights.rows(); row++) {
					for (int col = 0; col < hidden.weights.cols(); col++) {
						hidden.weights(row, col) += hidden.prev->activations(col) * hiddenError(row) * -RATE;
					}
				}
			}
			mse /= 2 * ITERATIONS;
			std::cout << "\nMSE of this epoch: " << mse << std::endl;
			std::cout << "Epoch score: " << correct << "/" << ITERATIONS << std::endl;
			csvFile << epoch << "," << mse << "\n";
		}
		csvFile.close();
		Image unknownImg;
		int unknownCorrect = 0;
		std::vector<float> unknownActs;
		for (int i = 50000; i < 60000; i++) {
			unknownImg = Reader::readImage(imageBytes, labelBytes, i);
			unknownActs = std::vector<float>(unknownImg.bytes.begin(), unknownImg.bytes.end());
			for (unsigned int i = 0; i < acts.size(); i++) {
				unknownActs[i] /= 255.f;
			}
			input.activations = Eigen::Map<Eigen::VectorXf>(unknownActs.data(), unknownActs.size());
			hidden.calculateActivations();
			output.calculateActivations();
			if (Utils::getResult(output.activations) == Utils::getDesiredVector(unknownImg.digit))
				unknownCorrect++;
		}
		std::cout << "Correct: " << unknownCorrect << std::endl;
	} catch (std::runtime_error& e) {
		std::cerr << "Runtime error:\n\t" << e.what() << std::endl;
		return 1;
	}
	return 0;
}
