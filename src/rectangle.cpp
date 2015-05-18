#include "rectangle.h"
#include "render_tools.h"
#include "position.h"
#include "entity.h"

Rectangle rectangles[max_entity_nb];

void render(Entity& entity) {
  if ( entity.position == NULL 
    || entity.shape == NULL) { return; }
  Position& pos = *(entity.position);
  Rectangle& rect = *(entity.shape);
  int w = rect.w/2; int h = rect.h/2;
  draw_hollow_square(pos.x-w, pos.y-h,
                     pos.x+w, pos.y-h,
                     pos.x+w, pos.y+h,
                     pos.x-w, pos.y+h);
}


Rectangle* RectangleFactory::create() {
  Rectangle& rect = rectangles[nb_rectangle];
  ++nb_rectangle;
  return &rect;
}
