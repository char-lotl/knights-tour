#include "Tile.h"

Tile::Tile() : used{false}, total_neighbors{0},
num_unused_neighbors{0}, direction{0}, path_index{0}
{}

void Tile::add_neighbor(SmartTilePointer& stp) {
	neighbors.push_back(stp);
	++total_neighbors;
	++num_unused_neighbors;
}

void Tile::reset_direction() {
	direction = 0;
}

void Tile::increment_direction() {
	++direction;
}

bool Tile::has_singleton_neighbor() {
	bool exists = false;
	for (SmartTilePointer& t : neighbors)
		if (!(t->used) && (t->num_unused_neighbors == 1))
			exists = true;
	return exists;
}
