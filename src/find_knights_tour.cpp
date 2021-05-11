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
		// if the algorithm backtracks from the very first node, it has exhausted the tree
		
		SmartTilePointer& t = route.back();
		// for brevity, more than anything
		
		if (t->direction >= t->total_neighbors) {
			b.remove_tile_from_route(route);
			if (!route.empty())		// this would cause a segfault if the route were empty
				route.back()->increment_direction();
			continue;
		}
		// if we've exhausted all possible directions from a node, the node itself is exhausted
		
		if (t->neighbors[t->direction]->used) {
			t->increment_direction(); continue;
		}
		// if a neighbor is already being used by the path, we can't use it again
		
		// if none of the above occurs, we can add a new node to the path!
		SmartTilePointer& new_tile = t->neighbors[t->direction];
		b.add_tile_to_route(new_tile, route);
		
		// but if adding this node causes a dead-end board-state, we consider the new node exhausted and backtrack
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
