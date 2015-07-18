#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include "constants.h"
#include "component.h"

class Entity;
class Tile;
class Texture;

class Rectangle : public Component {
public:
  int w;
  int h;
  Rectangle(): w(0), h(0) {}
};

void render(Entity& entity, const Entity& camera);
void render_tile(Tile& tile, const Entity& camera);
void render_tile_textured(const Texture& t, Tile& tile, const Entity& camera);
void render_rotated(Entity& entity, const Entity& camera);

#endif
