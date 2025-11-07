#include "Args.hpp"
#include "defines.hpp"	// color codes

#include <iostream>
#include <stdexcept>	// For std::invalid_argument
#include <cctype>		// For std::isdigit
#include <string>		// For std::stoi
#include <cmath>		// For std::abs

// Constructor takes command-line arguments and initializes member variables.	
Args::Args(int argc, char** argv)
	: n_orig(0), width(DEF_WIDTH), height(DEF_HEIGHT)
{
	// Check 'n'
	if (argc < 2)
		throw std::invalid_argument("Error: Missing required argument <n>");

	if (!isInteger(argv[1]))
		throw std::invalid_argument("Error: <n> must be a valid integer");

	n_orig = std::stoi(argv[1]);
	int	n = std::abs(n_orig); // Use absolute value of n, as z^-n = 1 is same as z^n = 1
	if (n == 0)
		throw std::invalid_argument("Error: <n> must not be 0. No derivative exists.");

	if (n < 3) // OK but boring (no fractals)
	{
		std::cerr	<< YELLOW << BOLD << "Warning: Low degree polynomial (n="
					<< n_orig << ")." << RESET <<std::endl;
		std::cerr	<< YELLOW << "         Results will be non-fractal (straight lines/monochrome). Use |n| >= 3 for chaos."
					<< RESET << std::endl;
	}

	// Check for optional 'width'
	if (argc >= 3)
	{
		if (!isInteger(argv[2]))
			throw std::invalid_argument("Error: [width] must be a valid integer");
		width = std::stoi(argv[2]);
		if (width <= 0)
			throw std::invalid_argument("Error: [width] must be a positive integer");
	}

	// Check for optional 'height'
	if (argc >= 4)
	{
		if (!isInteger(argv[3]))
		{
			throw std::invalid_argument("Error: [height] must be a valid integer");
		}
		height = std::stoi(argv[3]);
		if (height <= 0)
		{
			throw std::invalid_argument("Error: [height] must be a positive integer");
		}
	}
}

// Prints usage information
void	Args::printUsage(const char* progName)
{
	std::cout	<< BOLD << YELLOW << "Usage: " << progName << " <n> [width] [height]" << RESET << std::endl;
	std::cout	<< "  <n>      : Degree of the polynomial (integer != 0)" << std::endl;
	std::cout	<< "  [width]  : Width of the output image (optional, positive integer, default: "
				<< DEF_WIDTH << ")" << std::endl;
	std::cout	<< "  [height] : Height of the output image (optional, positive integer, default: "
				<< DEF_HEIGHT << ")" << std::endl;
}

/**
 @brief Checks if a string contains only a valid integer.
 
 Allows an optional '+' or '-' sign at the beginning.
 Does NOT allow whitespace or any other characters.
*/
bool	Args::isInteger(const std::string& str)
{
	if (str.empty())
		return false;

	size_t start = 0;
	if (str[0] == '-' || str[0] == '+')
		start = 1;

	for (size_t i = start; i < str.length(); ++i)
	{
		if (!std::isdigit(str[i]))
			return false;
	}
	return true;
}
