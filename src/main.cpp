//
//  main.cpp
//  Knight's Tour Solver
//
//  Created by Charlotte on 5/10/21.
//

#include <string>
#include <vector>
#include <iostream>

#include "board/Board.h"

#include "find_knights_tour.h"

int main(int argc, char* argv[]) {
    
	int width = 5, height = 5;
	
	int start_row = 0, start_col = 0;
	
	if (argc < 3) {
		std::cout << "Enter the board dimensions as command-line arguments.\n";
		return 0;
	}
	
	std::vector<std::string> arg_strings;
	
	for (int i = 1; i < argc; ++i) {
		arg_strings.push_back(argv[i]);
	}
	
	if (argc >= 3) {
		height = std::stoi(arg_strings[0]);
		width = std::stoi(arg_strings[1]);
	}
	
	if (argc >= 5) {
		start_row = std::stoi(arg_strings[2]) - 1;
		start_col = std::stoi(arg_strings[3]) - 1;
	}
	
	Board b{height, width};
	// this should bring into existence the tiles and establish their adjacencies
	
	find_knights_tour(b, start_row, start_col);
	
}
