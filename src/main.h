#ifndef _main_H_
#define _main_H_

#include "constants.h"
#include "render_tools.h"

#include "component.h"
#include "position.h"
#include "rectangle.h"
#include "aabb_collision.h"
#include "angle.h"

void manage_inputs();
void key_up(SDLKey sym, SDLMod mod, Uint16 unicode);

void add_ball();

void add_random_ball();

void add_hard_ball();

void add_random_hard_ball();

void add_random_rotated_ball();

void add_random_rotating_ball();

void switch_mode();

void init_entities();

void update_positions();

void do_collisions();

void do_render();

void loop();

int main(int argc, char** argv);

extern Entity entities[max_entity_nb];
extern int entity_nb;

extern int mode;

extern const int speed_factor;
extern const int size_factor;

extern const int starting_entity_nb;

typedef enum {
  FIXED_BALL_SPAWN = 0,
  RANDOM_BALL_SPAWN,
  FIXED_HARD_BALL_SPAWN,
  RANDOM_HARD_BALL_SPAWN,
  RANDOM_ROTATED_BALL_SPAWN,
  RANDOM_ROTATING_BALL_SPAWN,
  MAX_MODE
} GAME_MODE;


// component factories
extern ComponentFactory<Position> position_factory;
extern ComponentFactory<Speed> speed_factory;
extern ComponentFactory<Rectangle> shape_factory;
extern ComponentFactory<AABB> mask_factory;
extern ComponentFactory<Angle> angle_factory;
extern ComponentFactory<AngularSpeed> ang_speed_factory;


#endif
