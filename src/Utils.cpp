#include "Utils.hpp"

float Utils::sigmoid(float f) {
	return 1 / (1 + exp(-f));
}

float Utils::sigmoidDerivative(float f) {
	// Afleiding staat in tekst
	return sigmoid(f) * (1 - sigmoid(f));
}

Eigen::VectorXf Utils::getDesiredVector(short label) {
	Eigen::VectorXf temp = Eigen::VectorXf::Zero(10);
	temp(label) = 1.0f;
	return temp;
}

Eigen::VectorXf Utils::getResult(Eigen::VectorXf output) {
	Eigen::VectorXf::Index idx;
	// VectorXf.maxCoeff(VectorXf::Index idx) stopt de index van het grootste element in idx
	output.maxCoeff(&idx);
	return getDesiredVector((int) idx);
}


float Utils::vectorDiffLen(Eigen::VectorXf desired, Eigen::VectorXf actual) {
	if (desired.size() != actual.size())
		throw std::runtime_error("Cannot calculate difference of vectors with different-sized arrays!");
	// VectorXf.norm() berekent de lengte van een vector
	return (desired - actual).norm();
}

float Utils::cost(Image img, Eigen::VectorXf networkOutput) {
	if (networkOutput.size() != 10) 
		throw std::runtime_error("Cannot calculate cost, vector wrong size!");
	Eigen::VectorXf desired = getDesiredVector(img.digit);
	float temp = 0;
	// Cost = 1/2 * s((y^(x) - y(x))^2)
	for (int i = 0; i < networkOutput.size(); i++) {
		temp += pow(desired(i) - networkOutput(i), 2);
	}
	return temp / 2;
}
