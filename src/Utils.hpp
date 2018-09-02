#ifndef UTILS_HPP
#define UTILS_HPP

#include <Eigen/Core>

#include "Image.hpp"

class Utils {
public:
	static float sigmoid(float f);
	static float sigmoidDerivative(float f);
	static Eigen::VectorXf getDesiredVector(short label);
	static Eigen::VectorXf getResult(Eigen::VectorXf output);
	static float vectorDiffLen(Eigen::VectorXf desired, Eigen::VectorXf actual);
	static float cost(Image img, Eigen::VectorXf networkOutput);
};

#endif
