#ifndef _TILE_H_
#define _TILE_H_

#include <vector>

#include "object.h"
#include "component.h"

#include "position.h"
#include "aabb_collision.h"
#include "rectangle.h"

// tiled interface 
#include <TMXParser.h>
#include <TSXParser.h>

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
  int tileset_part; // the part of the tileset to use for rendering

  // init all components to null
  Tile():  position(NULL), shape(NULL), mask(NULL),
           tileset_part(-1) {};

  void remove();
  void set_void();

};


// map the same size as the screen size
class Map {
public:
  Map() {}
  std::vector<Tile> tiles;
  void render(const Entity& camera);
};


class Area {
public:
  Area(int w, int h);
  Area();
  void render(const Entity& camera);

  // get tile at tile coordinates
  const Tile& get_tile(int tx, int ty) const;
  // get tile at game position
  const Tile& get_tile(const Position& pos) const;
  // check if position is valid against the map
  bool valid_map_position(int x, int y, Entity& entity) const;
  // load area from tmx file
  void load_from_tmx(const char* tmx_filename);
  void load_tilesets(const TMX::Parser& tmx);

  // dimension in screen sizes or Maps objects
  int width;
  int height;

  std::vector<Map> tilemaps;
  Tile default_void_tile;
  Tile default_solid_tile;
  std::vector<TSX::Parser> tilesets;
};


#endif
