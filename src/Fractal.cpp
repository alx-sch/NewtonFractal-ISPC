#include "../include/Fractal.hpp"
#include "../include/defines.hpp"	// DEBUG_PRINT

#include <iostream>

#include <cmath>	// For M_PI, cos, sin

Fractal::Fractal(int n, int width, int height) :
	n_(n), width_(width), height_(height)
{}

/**
 @brief Calculates all n solutions to z^n = 1 and adds them to the roots_ vector.

 This function solves z^n = 1 by finding the 'n' complex roots
 using the formula:
 r_k = cos(2*pi*k/n) + i*sin(2*pi*k/n)
 for k = 0 to n-1.
*/
void	Fractal::calculateRoots(int n)
{
	roots_.clear(); // Clear vector from previous calculations

	DEBUG_PRINT("--- Calculating " << n << " Roots ---");

	for (int k = 0; k < n; ++k)
	{
		double					theta = 2 * M_PI * static_cast<double>(k) / n;
		std::complex<double>	root(cos(theta), sin(theta));
		DEBUG_PRINT("Root " << k << ": " << root);
		roots_.push_back(root);
	}
	DEBUG_PRINT("---------------------------");
}
