#ifndef _main_H_
#define _main_H_

#include "entity.h"
#include "tile.h"
#include "constants.h"
#include "render_tools.h"

void manage_inputs();

void key_up(SDLKey sym, SDLMod mod, Uint16 unicode);

void key_down(SDLKey sym, SDLMod mod, Uint16 unicode);

void init_camera();

void add_ball();

void add_random_ball();

void add_hard_ball();

void add_random_hard_ball();

void add_random_rotated_ball();

void add_random_rotating_ball();

void add_falling_ball();

void add_ephemeral_ball();

void add_firework();

void add_specu_colliding_ball();

void add_contact_tree_ball();

void remove_random_ball();

void switch_mode(int val = 1);

void init_entities();

void init_tile_map();

void load_tile_map();

void init_player();

void clear_tile_map();

void set_square_tile_map();

void set_gravity(int ax, int ay);

void spawn();

void respawn();

void clear_all();

void apply_gravity();

void cap_player_speed();

void cap_all_entities_speeds();

void update_positions();

void do_collisions();

void do_render();

void process_ephemerals();

void reset_moves();

void apply_player_moves();

void loop();

int main(int argc, char** argv);

extern int mode;

extern const int speed_factor;
extern const int size_factor;
extern const int speed_cap;

extern const int starting_entity_nb;

extern bool move_left;
extern bool move_right;
extern bool move_up;
extern bool move_down;

// for now, only one player controlled entity
extern Entity* player;

extern bool tile_map_active;

extern Accel gravity;
extern Area area;

extern Entity camera;

typedef enum {
  FIXED_BALL_SPAWN = 0,
  RANDOM_BALL_SPAWN,
  FIXED_HARD_BALL_SPAWN,
  RANDOM_HARD_BALL_SPAWN,
  RANDOM_ROTATED_BALL_SPAWN,
  RANDOM_ROTATING_BALL_SPAWN,
  RANDOM_FALLING_BALL_SPAWN,
  SPECU_COLLIDING_BALL_SPAWN,
  CONTACT_TREE_BALL_SPAWN,
  EPHEMERAL_BALL_SPAWN,
  FIREWORK_SPAWN,
  MAX_MODE
} GAME_MODE;


#endif
