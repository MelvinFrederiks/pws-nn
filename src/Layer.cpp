#include <iostream>

#include "Layer.hpp"

Layer::Layer(int activationAmt, Layer* previousLayer) {
	prev = previousLayer;
	activations = Eigen::VectorXf(activationAmt);
	weightedInput = Eigen::VectorXf(activationAmt);
	if (prev != nullptr) {
		// he et al initialization
		weights = Eigen::MatrixXf::Random(activationAmt, prev->activations.size()) * sqrt(2.f / prev->activations.size());
		bias = Eigen::VectorXf::Random(activationAmt);
	}
}

void Layer::calculateActivations() {
	activations = weights * prev->activations + bias;
	weightedInput = activations;
	for (int i = 0; i < activations.size(); i++) {
		activations(i) = Utils::sigmoid(activations(i));
	}
};

