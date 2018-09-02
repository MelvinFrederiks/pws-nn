#ifndef LAYER_HPP
#define LAYER_HPP

#include <vector>

#include <Eigen/Core>

#include "Utils.hpp"

class Layer {
public:
	// Pointer naar vorige laag
	Layer* prev;
	// Vector met neuronen
	Eigen::VectorXf weightedInput;
	Eigen::VectorXf activations;
	Eigen::VectorXf bias;
	// Waardes van connecties tussen this en prev
	// Matrix met grootte axb met:
	// a = activations.size();
	// b = prev.activations.size();
	// dus: weights[a][b] = gewicht van prev.activations[b] naar activations[a] (zie illustratie)
	Eigen::MatrixXf weights;

	Layer(int activationAmt, Layer* previousLayer);
	void calculateActivations();
};

#endif
