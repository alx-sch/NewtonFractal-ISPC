#ifndef NEWTON_FRACTAL_HPP
# define NEWTON_FRACTAL_HPP

# include "../include/defines.hpp"	// For Color struct
# include <vector>
# include <complex>
# include <utility>	// For std::pair

class Fractal
{
	public:
		using Complex = std::complex<double>; // Short-hand for complex numbers

		Fractal(int n, int width, int height);

		void	generate();
		bool	saveImage(const std::string& filename) const;

	private:
		int		n_;
		int		width_;
		int		height_;
		double	tolerance_;
		int		max_iterations_;

		// Viewport boundaries
		double	x_min_, x_max_, y_min_, y_max_;

		// Pre-computed data
		std::vector<Complex>	roots_;		// Holds the 'n' roots
		std::vector<Color>		palette_;	// The 'n' base colors

		// Final result
		std::vector<Color>		pixel_data_;	// 1D vector holding the 2D image

		void				calculateRoots();
		void				setupPalette();
		bool				newtonStep(Complex& z);
		std::pair<int, int>	solvePixel(Complex z_start, int x, int y);
		Color				calculateColor(int root_index, int iterations) const;
};

#endif
