/*
 * pngUtil.cpp
 *
 *  Created on: Mar 30, 2015
 *      Author: colman
 */
#include "pngUtil.h"
#include "lodepng.h"
#include <iostream>


//Encode from raw pixels to disk with a single function call
//The image argument has width * height RGBA pixels or width * height * 4 bytes
void encodeOneStep(const char* filename, std::vector<unsigned char> image,
		unsigned width, unsigned height) {
	//Encode the image
	unsigned error = lodepng::encode(filename, image, width, height);

	//if there's an error, display it
	if (error)
		std::cout << "encoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;
}

void decodeOneStep(const char* filename) {
	std::vector<unsigned char> image; //the raw pixels
	unsigned width, height;

	//decode
	unsigned error = lodepng::decode(image, width, height, filename);

	//if there's an error, display it
	if (error)
		std::cout << "decoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;

	//the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
}

void ConvertMapBlackToWhiteAndWhiteToBlack(const char* filename)
{
	std::vector<unsigned char> image; //the raw pixels
	unsigned width, height;
	unsigned x, y;
	//decode
	unsigned error = lodepng::decode(image, width, height, filename);

	//if there's an error, display it
	if (error)
		std::cout << "decoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;

	std::vector<unsigned char> navImage; //the raw pixels
	navImage.resize(width * height * 4);
	unsigned char color;
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			if (image[y * width * 4 + x * 4 + 0] ||
				image[y * width * 4 + x * 4 + 1] ||
				image[y * width * 4 + x * 4 + 2])
			{
				std::cout << " ";
				color = 0;
			}
			else
			{
				std::cout << "*";
				color = 255;
			}

			navImage[y * width * 4 + x * 4 + 0] = color;
			navImage[y * width * 4 + x * 4 + 1] = color;
			navImage[y * width * 4 + x * 4 + 2] = color;
			navImage[y * width * 4 + x * 4 + 3] = 255;
		}
		std::cout << std::endl;
	}

	encodeOneStep("newMap.png", navImage, width, height);
}

void ConvertMapFromPngToMatrix(const char* filename, int**& map_matrix, int& rows, int& cols)
{
	std::vector<unsigned char> image; //the raw pixels
	unsigned width, height;
	unsigned x, y;
	unsigned error = lodepng::decode(image, width, height, filename);

	rows = height;
	cols = width;

	//if there's an error, display it
	if (error)
	{
		std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
	}

	// Initialize the map matrix
	map_matrix = new int*[rows];
	for (int row = 0; row < rows; row++)
	{
		map_matrix[row] = new int[cols];
	}

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			if (image[y * width * 4 + x * 4 + 0] ||
				image[y * width * 4 + x * 4 + 1] ||
				image[y * width * 4 + x * 4 + 2])
			{
				map_matrix[y][x] = 0;
			}
			else
			{
				map_matrix[y][x] = 1;
			}
		}
	}
}

void InflateCell(int**& map_matrix, int height, int width, int cell_row, int cell_col, int inflation_factor)
{
	// Set the cell indices where to start scan the inflated cells matrix
	int nInflatedMatrixRowStart = cell_row - inflation_factor;
	int nInflatedMatrixColStart = cell_col - inflation_factor;

	// Set the size of the inflated cells matrix
	int nInflatedMatrixSize = (inflation_factor * 2) + 1;

	// Running over all the rows in the inflated cells matrix
	for (int row_index = nInflatedMatrixRowStart; row_index < nInflatedMatrixRowStart + nInflatedMatrixSize; row_index++)
	{
		// Running over all the cols in the inflated cells matrix
		for (int col_index = nInflatedMatrixColStart; col_index < nInflatedMatrixColStart + nInflatedMatrixSize; col_index++)
		{
			// Validating that the current cell is inside the map borders
			if (row_index >= 0 && row_index <= height - 1 && col_index >= 0 && col_index <= width - 1)
			{
				// Checking if the current cell is free
				if (map_matrix[row_index][col_index] == 0)
				{
					// Set this cell as inflated
					map_matrix[row_index][col_index] = 2;
				}
			}
		}
	}
}

void PrintMap(int**& map_matrix, int rows_num, int cols_num)
{
	std::cout << "printing the map: " << std::endl << std::endl;
	for (int row = 0; row < rows_num; row++)
	{
		for (int col = 0; col < cols_num; col++)
		{
			if (map_matrix[row][col] == 0)
			{
				std::cout << " ";
			}
			else if (map_matrix[row][col] == 1)
			{
				std::cout << "*";
			}
			else if (map_matrix[row][col] == 2)
			{
				std::cout << "#";
			}
		}
		std::cout << std::endl;
	}
}

void ConvertMapToGrid(int**& map_matrix, int**& grid_matrix, int grid_rows, int grid_cols, int resolutions_ratio)
{
	/*
	 * Fill the grid matrix cells
	 */

	// Running over all the grid rows
	for (int row = 0; row < grid_rows; row++)
	{
		// Running over all the grid cols
		for (int col = 0; col < grid_cols; col++)
		{
			// Checking if the current cell belongs to borders of the map
			if ((row == 0) || (row == grid_rows - 1) || (col == 0) || (col == grid_cols - 1))
			{
				grid_matrix[row][col] = 1;
				//bool obstacle_found = false;

				/*
				 * Run over the pixels matrix that should be represented by the current cell and searching
				 * for obstacles
				 */

				/*for (int i = 0; i < resolutions_ratio && !obstacle_found; ++i)
				{
					for (int j = 0; j < resolutions_ratio && !obstacle_found; ++j)
					{
						//std::cout << "reading cell index - " << (row * resolutions_ratio) + i << ","<< (col * resolutions_ratio) + j << " = " << map_matrix[(row * resolutions_ratio) + i][(col * resolutions_ratio) + j] << std::endl;
						// Checking if the current cell in the pixels matrix is not FREE
						if (map_matrix[(row * resolutions_ratio) + i][(col * resolutions_ratio) + j] != 0)
						{
							obstacle_found = true;
						}
					}
				}

				// Checking if we found at least one obstacle (and then this grid cell should be OCCUPIED)
				if (obstacle_found)
				{
					grid_matrix[row][col] = 1;
				}
				// There is no obstacles so this cell should be FREE
				else
				{
					grid_matrix[row][col] = 0;
				}*/
			}
			// The current cell doesn't belong to the last row or last col
			else
			{
				bool obstacle_found = false;

				/*
				 * Run over the pixels matrix that should be represented by the current cell and searching
				 * for obstacles
				 */

				for (int i = 0; i < resolutions_ratio && !obstacle_found; ++i)
				{
					for (int j = 0; j < resolutions_ratio && !obstacle_found; ++j)
					{
						// Checking if the current cell in the pixels matrix is not FREE
						if (map_matrix[(row * resolutions_ratio) + i][(col * resolutions_ratio) + j] != 0)
						{
							obstacle_found = true;
						}
					}
				}

				// Checking if we found at least one obstacle (and then this grid cell should be OCCUPIED)
				if (obstacle_found)
				{
					grid_matrix[row][col] = 1;
				}
				// There is no obstacles so this cell should be FREE
				else
				{
					grid_matrix[row][col] = 0;
				}
			}
		}
	}
}
