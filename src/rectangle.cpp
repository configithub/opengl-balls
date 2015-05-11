#include "rectangle.h"
#include "render_tools.h"
#include "position.h"

Rectangle rectangles[max_entity_nb];

void render(int entity) {
  Position& pos = positions[entity];
  Rectangle& rect = rectangles[entity];
  draw_hollow_square(pos.x, pos.y,
                     pos.x+rect.w, pos.y,
                     pos.x+rect.w, pos.y+rect.h,
                     pos.x, pos.y+rect.h);
}

