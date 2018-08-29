#include "Layer.hpp"

Layer::Layer(int activationAmt, Layer* previousLayer) {
	prev = previousLayer;
	activations = Eigen::VectorXf(activationAmt);
	if (prev != nullptr) {
		// he et al initialization
		weights = Eigen::MatrixXf::Random(activationAmt, prev->activations.size()) * sqrt(2.f / prev->activations.size());
	}
}
#include <iostream>
void Layer::calculateActivations() {
	std::cout << "weight size: " << weights.rows() << "x" << weights.cols() << std::endl;
	std::cout << "prev acts size: " << prev->activations.size() << std::endl;
	activations = weights * prev->activations;
};
