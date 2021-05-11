#ifndef SMART_TILE_POINTER_H
#define SMART_TILE_POINTER_H

struct Tile;
using SmartTilePointer = std::shared_ptr<Tile>;
using STPV = std::vector<SmartTilePointer>;

#endif
