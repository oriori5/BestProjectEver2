/*
 * Map.cpp
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */

#include "Map.h"

double Map::map_resolution_in_cm = 0;
double Map::grid_resolution_in_cm = 0;

Map::Map()
{
	// TODO Auto-generated constructor stub
}

Map::~Map()
{
	// TODO Auto-generated destructor stub
}

void Map::ReadMapFromPngToMatrix(const char* filename, int**& map_matrix, int& rows, int& cols)
{
	std::vector<unsigned char> image; //the raw pixels
	unsigned width, height;
	unsigned x, y;
	unsigned error = lodepng::decode(image, width, height, filename);

	rows = height;
	cols = width;

	// if there's an error, display it
	if (error)
	{
		std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
	}
	// There is no error while reading the png file
	else
	{
		// Initialize the map matrix
		map_matrix = new int*[rows];
		for (int row = 0; row < rows; row++)
		{
			map_matrix[row] = new int[cols];
		}

		// Run over all the rows
		for (y = 0; y < height; y++)
		{
			// Run over all the cols
			for (x = 0; x < width; x++)
			{
				// Checking if the current pixel is NOT BLACK (means a free cell)
				if (image[y * width * 4 + x * 4 + 0] ||
					image[y * width * 4 + x * 4 + 1] ||
					image[y * width * 4 + x * 4 + 2])
				{
					map_matrix[y][x] = 0;
				}
				// The current pixel is BLACK (means a occupied cell)
				else
				{
					map_matrix[y][x] = 1;
				}
			}
		}
	}
}

void Map::BlowCell(int**& map_matrix, int height, int width, int cell_row, int cell_col, int blowing_factor, int blow_indication)
{
	// Set the cell indices where to start scan the blown cells matrix
	int nBlowedMatrixRowStart = cell_row - blowing_factor;
	int nBlowedMatrixColStart = cell_col - blowing_factor;

	// Set the size of the blown cells matrix
	int nInflatedMatrixSize = (blowing_factor * 2) + 1;

	// Running over all the rows in the blown cells matrix
	for (int row_index = nBlowedMatrixRowStart; row_index < nBlowedMatrixRowStart + nInflatedMatrixSize; row_index++)
	{
		// Running over all the cols in the blown cells matrix
		for (int col_index = nBlowedMatrixColStart; col_index < nBlowedMatrixColStart + nInflatedMatrixSize; col_index++)
		{
			// Validating that the current cell is inside the map borders
			if (row_index >= 0 && row_index <= height - 1 && col_index >= 0 && col_index <= width - 1)
			{
				// Checking if the current cell is free
				if (map_matrix[row_index][col_index] == 0)
				{
					// Set this cell as blown
					map_matrix[row_index][col_index] = blow_indication;
				}
			}
		}
	}
}

void Map::BlowMap(int**& map_matrix, int height, int width, int blowing_factor)
{
	// Run over all the rows in the map
	for (int row = 0; row < height; row++)
	{
		// Run over all the cols in the map
		for (int col = 0; col < width; col++)
		{
			// Checking if the current cell is obstacle
			if (map_matrix[row][col] == 1)
			{
				// Blow the current cell
				BlowCell(map_matrix, height, width, row, col, blowing_factor, 2);
			}
		}
	}
}

void Map::ConvertMapToGrid()
{
	int resolutions_ratio = Map::grid_resolution_in_cm / Map::map_resolution_in_cm;

	// Set the grid matrix dimensions
	_grid._height = _map._height / resolutions_ratio + (_map._height % resolutions_ratio == 0 ? 0 : 1);
	_grid._width = _map._width / resolutions_ratio + (_map._width % resolutions_ratio == 0 ? 0 : 1);

	// Create the grid matrix
	_grid._matrix = new int*[_grid._height];
	for (int row = 0; row < _grid._height; row++)
	{
		_grid._matrix[row] = new int[_grid._width];
	}

	/*
	 * Fill the grid matrix cells
	 */

	// Running over all the grid rows
	for (int row = 0; row < _grid._height; row++)
	{
		// Running over all the grid cols
		for (int col = 0; col < _grid._width; col++)
		{
			// Checking if the current cell belongs to borders of the map
			if ((row == 0) || (row == _grid._height - 1) || (col == 0) || (col == _grid._width - 1))
			{
				// Set this cell as obstacle
				_grid._matrix[row][col] = 1;
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
						if (_map._matrix[(row * resolutions_ratio) + i][(col * resolutions_ratio) + j] != 0)
						{
							obstacle_found = true;
						}
					}
				}

				// Checking if we found at least one obstacle (and then this grid cell should be OCCUPIED)
				if (obstacle_found)
				{
					_grid._matrix[row][col] = 1;
				}
				// There is no obstacles so this cell should be FREE
				else
				{
					_grid._matrix[row][col] = 0;
				}
			}
		}
	}
}

int Map::GetGridIndexByMapIndex(int map_index)
{
	int resolutions_ratio = Map::grid_resolution_in_cm / Map::map_resolution_in_cm;

	return (map_index / resolutions_ratio);
}

void Map::WriteMapMatrixToPng(int**& map_matrix, int height, int width, const char* filename)
{
	std::vector<unsigned char> navImage;
	navImage.resize(width * height * 4);
	unsigned char color;

	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			if (map_matrix[row][col] == 0)
			{
				color = 255;
			}
			else if (map_matrix[row][col] == 1)
			{
				color = 0;
			}
			else if (map_matrix[row][col] == 2)
			{
				color = 255;
			}
			else if (map_matrix[row][col] == 5)
			{
				color = 128;
			}

			navImage[row * width * 4 + col * 4 + 0] = color;
			navImage[row * width * 4 + col * 4 + 1] = color;
			navImage[row * width * 4 + col * 4 + 2] = color;
			navImage[row * width * 4 + col * 4 + 3] = 255;
		}
	}

	encodeOneStep(filename, navImage, width, height);
}

