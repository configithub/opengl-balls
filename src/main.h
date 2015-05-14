#ifndef _main_H_
#define _main_H_

#include "constants.h"
#include "render_tools.h"

void manage_inputs();
void key_up(SDLKey sym, SDLMod mod, Uint16 unicode);

void add_ball();

void add_random_ball();

void add_hard_ball();

void add_random_hard_ball();

void switch_mode();

void init_entities();

void loop();

int main(int argc, char** argv);

extern int entities[max_entity_nb];
extern int entity_nb;

extern int mode;

extern const int speed_factor;
extern const int size_factor;

typedef enum {
  FIXED_BALL_SPAWN = 0,
  RANDOM_BALL_SPAWN,
  FIXED_HARD_BALL_SPAWN,
  RANDOM_HARD_BALL_SPAWN,
  MAX_MODE
} GAME_MODE;


#endif
