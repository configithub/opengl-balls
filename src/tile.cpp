#include "tile.h"
#include "entity.h"

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


void TileMap::render() {
  for(int i = 0; i < nb_tiles; ++i) {
    render_tile(tiles[i]);
  }
}


void Area::render() {
  // TODO: only render what is visible
  for(int k = 0; k < width*height; ++k) {
    tilemaps[k].render();
  }
}


Area::Area(int w, int h) {
  width = w; height = h;
  printf("creating area of size: %d, %d x %d\n", width*height, width, height);
  tilemaps[width*height];
}


Tile& Area::get_tile(int tx, int ty) {
  // find the tilemap
  int tm_x = tx / screen_width;
  int tm_y = ty / screen_height;
  TileMap& tm = tilemaps[tm_y*width + tm_x];
  // find the tile in this tilemap
  return tm.tiles[ty*screen_width+tx];
}


Tile& Area::get_tile(const Position& pos) {
  // find the tilemap
  int tm_x = pos.x / WWIDTH;
  int tm_y = pos.y / WHEIGHT;
  TileMap& tm = tilemaps[tm_y*width + tm_x];
  // find the tile in this tilemap
  return tm.tiles[((pos.y%WHEIGHT)/tile_size)*screen_width
                          +((pos.x%WWIDTH)/tile_size) ];
}


bool Area::valid_map_position(int x, int y, Entity& entity) {
  // assert mask is not null ?
  int tile_top_left_X = (x - entity.mask->w / 2) / tile_size;
  int tile_top_left_Y = (y - entity.mask->h / 2) / tile_size;
  tile_top_left_X = tile_top_left_X < 0 ? 0 : tile_top_left_X;
  tile_top_left_Y = tile_top_left_Y < 0 ? 0 : tile_top_left_Y;
  int tile_bottom_right_X = (x + entity.mask->w / 2) / tile_size;
  int tile_bottom_right_Y = (y + entity.mask->h / 2) / tile_size;
  for(int j = tile_top_left_Y; j <= tile_bottom_right_Y; j++) {
    for(int i = tile_top_left_X; i <= tile_bottom_right_X; i++) {
      if(get_tile(i, j).flags == SOLID) { return false; }
    }
  }
  return true;
}


