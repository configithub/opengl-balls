#ifndef _TILE_H_
#define _TILE_H_

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

};

extern Factory<Tile> tile_factory;

#endif
