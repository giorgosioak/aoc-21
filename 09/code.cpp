#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <string>
#include <numeric>
#include <bits/stdc++.h>

std::vector<std::vector<int>> bit;

void print_basins(std::vector<std::vector<int>> matrix);

bool is_low_point(int col, int row, std::vector<std::vector<int>> matrix) {

    int col_size = matrix.size();
    int row_size = matrix[0].size();

    int up   = ( row == 0 ) ? 10 : matrix[col][row-1];
    int left = ( col == 0 ) ? 10 : matrix[col-1][row];

    int down  = ( row == row_size-1 ) ? 10 : matrix[col][row+1];
    int right = ( col == col_size-1 ) ? 10 : matrix[col+1][row];
    
    if ( matrix[col][row] >= up )    return false;
    if ( matrix[col][row] >= left )  return false;
    if ( matrix[col][row] >= down )  return false;
    if ( matrix[col][row] >= right ) return false;

    return true;

}

// gbs : get_basin_size
int gbs(int col, int row, std::vector<std::vector<int>> matrix) {
    
    if ( col == -1 || row == -1 || col == matrix.size() || row == matrix[0].size() ) return 0;
    if ( matrix[col][row] == 9 || bit[col][row] == 1 ) return 0;

    bit[col][row] = 1;

    return gbs(col,row-1,matrix) + gbs(col-1,row,matrix) + gbs(col,row+1,matrix) + gbs(col+1,row,matrix) + 1;
}


int main () {

	/* Read input */

	if ( !std::filesystem::exists("input") ){
		std::cout << "input file does not exist" << std::endl;
		return 1;
	}

	std::ifstream input("input");

	/* Read data */
    
    std::vector<std::vector<int>> points;
    std::vector<std::pair<int,int>> low_points;
    
     
    while ( !input.eof() ) {
        bool is_input = true;
		std::string line;
        char c;

        std::vector<int> row;

		std::getline(input, line);
        std::istringstream linestream(line);
		while (linestream >> c) {

            row.push_back(c-'0');
		}
        points.push_back(row);
	}

    int col_size = points.size();
    int row_size = points[0].size();

	/* --- Part 1 --- */

    int sum = 0;
    for ( int i = 0; i < col_size; i++ ) {
        for ( int k = 0; k < row_size; k++ ) {

            if ( is_low_point(i,k,points) ) {
                std::cout << "\033[0;31m" << points[i][k] << "\033[0m ";
                low_points.push_back({i,k});
                sum += points[i][k] + 1;
            } else {
                std::cout << points[i][k] << " ";
            }


        }
        std::cout << std::endl;
    }

	std::cout << "Part1: " << sum << std::endl;

	/* --- Part 2 --- */

    bit = std::vector(col_size, std::vector<int> (row_size, 0));
    std::vector<int> basins;

    for ( auto lp : low_points ) {
        basins.push_back(gbs(lp.first,lp.second,points));
    }

    sort(basins.begin(), basins.end(), std::greater<int>());

    print_basins(points);

	std::cout << "Part2: " <<  basins[0] * basins[1] * basins[2] << std::endl;

    return 0;
}

/* Pretty print because i can */

void print_basins(std::vector<std::vector<int>> matrix) {

    int col_size = matrix.size();
    int row_size = matrix[0].size();

    for ( int i = 0; i < col_size; i++ ) {
        for ( int k = 0; k < row_size; k++ ) {

            if ( bit[i][k] == 1 ) {
                std::cout << "\033[0;35m" << matrix[i][k] << "\033[0m ";
            } else {
                std::cout << "\033[0;33m" << matrix[i][k] << "\033[0m ";
            }
        }
        std::cout << std::endl;
    }
}