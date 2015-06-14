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
