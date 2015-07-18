/*
 * pngUtil.h
 *
 *  Created on: Mar 30, 2015
 *      Author: colman
 */

#ifndef PNGUTIL_H_
#define PNGUTIL_H_
#include <iostream>
#include <vector>
void encodeOneStep(const char* filename, std::vector<unsigned char> image, unsigned width, unsigned height);
void decodeOneStep(const char* filename);
void ConvertMapBlackToWhiteAndWhiteToBlack(const char* filename);
void ConvertMapFromPngToMatrix(const char* filename, int**& map_matrix, int& rows, int& cols);
void InflateCell(int**& map_matrix, int height, int width, int cell_row, int cell_col, int inflation_factor);
void PrintMap(int**& map_matrix, int rows_num, int cols_num);
void ConvertMapToGrid(int**& map_matrix, int**& grid_matrix, int grid_rows, int grid_cols, int resolutions_ratio);


#endif /* PNGUTIL_H_ */
