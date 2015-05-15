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
  draw_hollow_square(pos.x, pos.y,
                     pos.x+rect.w, pos.y,
                     pos.x+rect.w, pos.y+rect.h,
                     pos.x, pos.y+rect.h);
}


Rectangle* RectangleFactory::create() {
  Rectangle& rect = rectangles[nb_rectangle];
  ++nb_rectangle;
  return &rect;
}
