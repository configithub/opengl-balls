#include "rectangle.h"
#include "render_tools.h"
#include "entity.h"
#include "tile.h"

#include <math.h>

Rectangle rectangles[max_entity_nb];

void render(Entity& entity, const Entity& camera) {
  if ( entity.position == NULL 
    || entity.shape == NULL) { return; }
  Position& pos = *(entity.position);
  Rectangle& rect = *(entity.shape);
  int w = rect.w/2; int h = rect.h/2;
  draw_hollow_square(pos.x-w - camera.position->x, pos.y-h - camera.position->y,
                     pos.x+w - camera.position->x, pos.y-h - camera.position->y,
                     pos.x+w - camera.position->x, pos.y+h - camera.position->y,
                     pos.x-w - camera.position->x, pos.y+h - camera.position->y);
}

void render_tile(Tile& tile, const Entity& camera) {
  if ( tile.position == NULL 
    || tile.shape == NULL
    || tile.flags == VOID) { return; }
  Position& pos = *(tile.position);
  Rectangle& rect = *(tile.shape);
  int w = rect.w/2; int h = rect.h/2;
  draw_square(pos.x-w - camera.position->x, pos.y-h - camera.position->y,
              pos.x+w - camera.position->x, pos.y-h - camera.position->y,
              pos.x+w - camera.position->x, pos.y+h - camera.position->y,
              pos.x-w - camera.position->x, pos.y+h - camera.position->y);
}

void render_rotated(Entity& entity, const Entity& camera) {
  if ( entity.position == NULL 
    || entity.shape == NULL) { return; }
  if ( entity.position->theta == 0 ) { render(entity, camera); return; }
  Position& pos = *(entity.position);
  Rectangle& rect = *(entity.shape);
  int w = rect.w/2; int h = rect.h/2;
  float cos_theta = cos(pos.theta);
  float sin_theta = sin(pos.theta);
  int w_r_a = (int) (w*cos_theta + h*sin_theta + 0.5);
  int h_r_a = (int) (-w*sin_theta + h*cos_theta + 0.5);
  int w_r_b = (int) (-w*cos_theta + h*sin_theta + 0.5);
  int h_r_b = (int) (w*sin_theta + h*cos_theta + 0.5);
  draw_hollow_square(pos.x-w_r_a - camera.position->x, 
                                        pos.y-h_r_a - camera.position->y,
              pos.x-w_r_b - camera.position->x, pos.y-h_r_b - camera.position->y,
              pos.x+w_r_a - camera.position->x, pos.y+h_r_a - camera.position->y,
              pos.x+w_r_b - camera.position->x, pos.y+h_r_b - camera.position->y);
}


