#ifndef TILE_H
#define TILE_H

#include <vector>
#include "SmartTilePointer.h"

struct Tile {
public:
	bool used;
	int total_neighbors;
	int num_unused_neighbors;
	int direction;
	int path_index;
	STPV neighbors;
	Tile();
	void add_neighbor(SmartTilePointer& stp);
	void reset_direction();
	void increment_direction();
	bool has_singleton_neighbor();
};

#endif
