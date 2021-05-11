#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "SmartTilePointer.h"

using STPV2 = std::vector<STPV>;

class Board {
private:
	int height;
	int width;
	int area;
	std::vector<int> adjacency_stats;
	void establish_adjacencies();
	void initialize_statistics();
	int used_tiles;
	STPV2 contents;
public:
	Board(int h, int w);
	STPV& operator[](int row);
	void add_tile_to_route(SmartTilePointer& s, STPV& r);
	void remove_tile_from_route(STPV& r);
	int geth();
	int getw();
	int get_area();
	bool unsolvable(SmartTilePointer& active_tile);
	int get_used_tiles();
	void print_path();
};

#endif
