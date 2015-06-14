#include "tile.h"

Factory<Tile> tile_factory;
// component factories
ComponentFactory<Position> tposition_factory;
ComponentFactory<Rectangle> tshape_factory;
ComponentFactory<AABB> tmask_factory;


void Tile::remove() {
  flags = VOID;
  if(position != NULL) {
    tposition_factory.remove(position);
    position = NULL;
  }
  if(shape != NULL) {
    tshape_factory.remove(shape);
    shape = NULL;
  }
  if(mask != NULL) {
    tmask_factory.remove(mask);
    mask = NULL;
  }
}


TileMap::TileMap() {
  nb_tiles = (WWIDTH / tile_size) * (WHEIGHT / tile_size);
}


void TileMap::render() {
  for(int i = 0; i < nb_tiles; ++i) {
    render_tile(tiles[i]);
  }
}

void Area::render() {
  // todo: only render what is visible
  for(int i = 0; i < area_size; ++i) {
    tilemaps[i].render();
  }
}




