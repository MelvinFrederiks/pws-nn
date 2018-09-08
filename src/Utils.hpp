#ifndef UTILS_HPP
#define UTILS_HPP

#include <Eigen/Core> 	// VectorXf

#include "Image.hpp"	// Image

class Utils {
public:
	// Sigmoid functie (y = (1 + e^-x)^-1
	// Mapt alle waardes in R tot [0, 1] met s(0) = 0.5
	static float sigmoid(float f);
	// De afgeleide van de sigmoid functie:
	// s(x) * (1 - s(x))
	static float sigmoidDerivative(float f);
	// Returnt een vector met element # label een 1 en de rest een 0
	// Dit is de ideale ouptut van een netwerk
	static Eigen::VectorXf getDesiredVector(short label);
	// Zoekt in vector output welk element e het grootst is, en returnt dan getDesiredVector(e)
	static Eigen::VectorXf getResult(Eigen::VectorXf output);
	// Berekent de lengte van het verschil tussen vector desired en actual
	static float vectorDiffLen(Eigen::VectorXf desired, Eigen::VectorXf actual);
	// Berekent de cost voor een enkele training sample
	static float cost(Image img, Eigen::VectorXf networkOutput);
};

#endif
