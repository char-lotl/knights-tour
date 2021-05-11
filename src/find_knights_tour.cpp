#include <utility>
#include <iostream>

#include "find_knights_tour.h"
#include "board/Board.h"
#include "board/Tile.h"

void find_knights_tour(Board& b, int sr, int sc) {
	
	SmartTilePointer start_tile{b[sr][sc]};
	STPV route;
	
	b.add_tile_to_route(start_tile, route);
	
	bool success = true;
	
	int tracker = 0;
	
	while (b.get_used_tiles() < b.get_area()) {
		
		++tracker;
		
		if (b.get_used_tiles() == 0) {
			success = false;
			break;
		}
		
		SmartTilePointer& t = route.back();
		
		if (t->direction >= t->total_neighbors) {
			b.remove_tile_from_route(route);
			if (!route.empty())		// this would cause a segfault if the route were empty
				route.back()->increment_direction();
			continue;
		}
		
		if (t->neighbors[t->direction]->used) {
			t->increment_direction(); continue;
		}
		
		SmartTilePointer& new_tile = t->neighbors[t->direction];
		b.add_tile_to_route(new_tile, route);
		
		if (b.unsolvable(new_tile)) {
			b.remove_tile_from_route(route);
			route.back()->increment_direction();
		}
		
	}
	
	if (success) {
	
		std::cout << "Success! The path was...\n";
		
		b.print_path();
		
		std::cout << "\nAnd we used " << tracker << " iterations to do it.\n";
		
	} else {
		
		std::cout << "Couldn't find a knight's tour!\n";
		
	}
	
	
}
