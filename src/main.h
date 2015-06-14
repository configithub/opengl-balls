#ifndef _main_H_
#define _main_H_

#include "entity.h"
#include "tile.h"
#include "constants.h"
#include "render_tools.h"

void manage_inputs();

void key_up(SDLKey sym, SDLMod mod, Uint16 unicode);

void add_ball();

void add_random_ball();

void add_hard_ball();

void add_random_hard_ball();

void add_random_rotated_ball();

void add_random_rotating_ball();

void add_falling_ball();

void add_ephemeral_ball();

void add_firework();

void remove_random_ball();

void switch_mode();

void init_entities();

void init_tile_map();

void respawn();

void apply_gravity();

void update_positions();

void do_collisions();

void do_render();

void process_ephemerals();

void loop();

int main(int argc, char** argv);

extern int mode;

extern const int speed_factor;
extern const int size_factor;

extern const int starting_entity_nb;

extern Area area;

typedef enum {
  FIXED_BALL_SPAWN = 0,
  RANDOM_BALL_SPAWN,
  FIXED_HARD_BALL_SPAWN,
  RANDOM_HARD_BALL_SPAWN,
  RANDOM_ROTATED_BALL_SPAWN,
  RANDOM_ROTATING_BALL_SPAWN,
  RANDOM_FALLING_BALL_SPAWN,
  EPHEMERAL_BALL_SPAWN,
  FIREWORK_SPAWN,
  MAX_MODE
} GAME_MODE;


#endif
