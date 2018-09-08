#ifndef LAYER_HPP
#define LAYER_HPP

#include <Eigen/Core>	// VectorXf, MatrixXf

#include "Utils.hpp"	// sigmoid

// Klasse die een laag in het netwerk beschrijft
class Layer {
public:
	// Pointer naar vorige laag
	Layer* prev;
	// Weighted input (weights * prev->activations + bias)
	Eigen::VectorXf weightedInput;
	// Neuronen in laag (sigmoid(weightedInput))
	Eigen::VectorXf activations;
	// Biases in laag (1 per neuron)
	Eigen::VectorXf bias;
	// Waardes van connecties tussen this en prev
	// Matrix met grootte axb met:
	// a = activations.size();
	// b = prev.activations.size();
	// dus: weights[a][b] = gewicht van prev.activations[b] naar activations[a] (zie illustratie)
	Eigen::MatrixXf weights;
	
	// Maak een laag met activationAmt neuronen
	// De vorige laag kan worden gespecificeerd door een pointer naar de vorige Layer object (nullptr voor input layer)
	Layer(int activationAmt, Layer* previousLayer);
	// Bereken de neuronen van de laag op basis van de neuronen van de vorige laag
	void calculateActivations();
};

#endif
