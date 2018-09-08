#include "Layer.hpp"

Layer::Layer(int activationAmt, Layer* previousLayer) {
	// Stel klasse fields in
	prev = previousLayer;
	activations = Eigen::VectorXf(activationAmt);
	weightedInput = Eigen::VectorXf(activationAmt);
	// Als de vorige laag niet nullptr is, dus als de huidige laag niet de input layer is:
	if (prev != nullptr) {
		// He et al weights initialization
		weights = Eigen::MatrixXf::Random(activationAmt, prev->activations.size()) * sqrt(2.f / prev->activations.size());
		// Random bias initialization
		bias = Eigen::VectorXf::Random(activationAmt);
	}
}

void Layer::calculateActivations() {
	// Bereken weighted input (Wa + b)
	activations = weights * prev->activations + bias;
	weightedInput = activations;
	for (int i = 0; i < activations.size(); i++) {
		// Bereken sigmoid van weighted input
		activations(i) = Utils::sigmoid(activations(i));
	}
};

