#ifndef _TILE_H_
#define _TILE_H_

#include <vector>

#include "object.h"
#include "component.h"

#include "position.h"
#include "aabb_collision.h"
#include "rectangle.h"

// component factories
extern ComponentFactory<Position> tposition_factory;
extern ComponentFactory<Rectangle> tshape_factory;
extern ComponentFactory<AABB> tmask_factory;

typedef enum {
  VOID = 0,
  SOLID =  1,
  ONEWAY = 2
} EN_TileType;


class Tile : public Object {
public:
  Position* position;
  Rectangle* shape;
  AABB* mask;

  // init all components to null
  Tile():  position(NULL), 
            shape(NULL), mask(NULL) {};

  void remove();
  void set_void();

};


class TileMap {
public:
  TileMap() {}
  std::vector<Tile> tiles;
  void render(const Entity& camera);
};

class Area {
public:
  Area(int w, int h);
  int width;
  int height;

  std::vector<TileMap> tilemaps;
  Tile default_void_tile;
  Tile default_solid_tile;
  void render(const Entity& camera);

  // in tile coordinates
  const Tile& get_tile(int tx, int ty) const;
  // in game position
  const Tile& get_tile(const Position& pos) const;
  
  bool valid_map_position(int x, int y, Entity& entity) const;

};


#endif
