#include "Board.h"
#include "Tile.h"
#include <iostream>

void add_neighbor_if_in_bounds(int r, int c, int h, int w, STPV2& con, SmartTilePointer& t);
bool is_in_bounds(int r, int c, int h, int w);
int count_digits(int num);

Board::Board(int h, int w) :
height{h}, width{w}, area{h * w}, used_tiles{0}, contents{static_cast<unsigned long>(h), STPV{}} {
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			contents[i].push_back(std::make_shared<Tile>());
		}
	}
	establish_adjacencies();
	initialize_statistics();
}

const std::vector<std::vector<int> > KNIGHTS_MOVES = {
	{-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}
};

void Board::establish_adjacencies() {
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			for (int k = 0; k < 8; ++k) {
				add_neighbor_if_in_bounds(i - KNIGHTS_MOVES[k][0], j + KNIGHTS_MOVES[k][1], height, width, contents, contents[i][j]);
			}
		}
	}
}

STPV& Board::operator[](int row) {
	return contents[row];
}

void Board::add_tile_to_route(SmartTilePointer& stp, STPV& r) {
	++used_tiles;
	r.push_back(stp);
	stp->path_index = r.size();
	stp->used = true;
	--adjacency_stats[stp->num_unused_neighbors];
	for (SmartTilePointer s : stp->neighbors) {
		if (!(s->used)) {
			--adjacency_stats[s->num_unused_neighbors];
			--(s->num_unused_neighbors);
			++adjacency_stats[s->num_unused_neighbors];
		}
	}
}

void Board::remove_tile_from_route(STPV& r) {
	SmartTilePointer& stp = r.back();
	stp->reset_direction();
	for (SmartTilePointer s : stp->neighbors) {
		if (!(s->used)) {
			--adjacency_stats[s->num_unused_neighbors];
			++(s->num_unused_neighbors);
			++adjacency_stats[s->num_unused_neighbors];
		}
	}
	++adjacency_stats[stp->num_unused_neighbors];
	stp->used = false;
	stp->path_index = 0;
	r.pop_back();
	--used_tiles;
}

int Board::get_used_tiles() {
	return used_tiles;
}

void add_neighbor_if_in_bounds(int r, int c, int h, int w, STPV2& contents, SmartTilePointer& t) {
	bool in_bounds = is_in_bounds(r, c, h, w);
	if (in_bounds) t->add_neighbor(contents[r][c]);
}

bool is_in_bounds(int r, int c, int h, int w) {
	return (r >= 0) && (r < h) && (c >= 0) && (c < w);
}

void Board::initialize_statistics() {
	std::vector<int> temp_stats(9, 0);
	
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			++temp_stats[contents[i][j]->num_unused_neighbors];
		}
	}
	adjacency_stats = temp_stats;
}

int Board::geth() { return height; }
int Board::getw() { return width; }
int Board::get_area() { return area; }

bool Board::unsolvable(SmartTilePointer& t) {
	bool singleton_dead_end = (adjacency_stats[0] > 0) && (used_tiles + 1 < area);
	if (singleton_dead_end || (adjacency_stats[1] > 2)) return true;
	
	// early return to avoid the has_singleton_neighbor loop where possible
	
	bool doubleton_dead_end = (adjacency_stats[1] > 1) && !(t->has_singleton_neighbor());
	return doubleton_dead_end;
}

void Board::print_path() {
	int max_digits = count_digits(area);
	int col_width = max_digits + 1;
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			int p_i = contents[i][j]->path_index;
			int left_spacing = col_width - count_digits(p_i);
			std::cout << std::string(left_spacing, ' ') << p_i;
		}
		std::cout << '\n';
	}
}

int count_digits(int num) {
	int num_digits = 0;
	while (num > 0) {
		++num_digits;
		num /= 10;
	}
	return num_digits;
}
