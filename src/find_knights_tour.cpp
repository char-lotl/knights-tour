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
			//std::cout << "Looked at all available neighbors.\n";
			continue;
		}
		
		if (t->neighbors[t->direction]->used) {
			//std::cout << "This one's being used.\n";
			t->increment_direction(); continue;
		}
		
		//std::cout << "Let's try this way!\n";
		SmartTilePointer& new_tile = t->neighbors[t->direction];
		b.add_tile_to_route(new_tile, route);
		
		if (b.unsolvable(new_tile)) {
			//std::cout << "Oops! This way's no good.\n";
			b.remove_tile_from_route(route);
			route.back()->increment_direction();
		}
		
		// check that the current direction corresponds to a node
		//   if not, pop the current node and zero its direction
		//   and increment the new latest tile's direction. continue.
		// check that the node in the current direction is unused
		//   if it is, add the node in the current "direction"
		//   if it's not, increment the direction.
		
		// if a node was added, confirm we aren't left with an unsolvable problem.
		// if we are, pop the new node back off, and increment direction.
	}
	
	if (success) {
	
		std::cout << "Success! The path was...\n";
		
		/*for (SmartTilePointer t : route) {
			std::cout << t->direction << " ";
		}*/
		
		b.print_path();
		
		std::cout << "\nAnd we used " << tracker << " iterations to do it.\n";
		
	} else {
		
		std::cout << "Couldn't find a knight's tour!\n";
		
	}
	
	
}
