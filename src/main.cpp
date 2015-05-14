#include "main.h"
#include <stdio.h>
#include "render_tools.h"

#include "position.h"
#include "rectangle.h"
#include "aabb_collision.h"

SDL_Event events;
bool running;
int entities[max_entity_nb];
int entity_nb = 0;

const int speed_factor = 5;
const int size_factor = 20;

int mode = 3;


void manage_inputs() {
  while(SDL_PollEvent(&events)) {
    if(events.type == SDL_QUIT)
      running = false;
    if(events.type ==  SDL_KEYUP) 
      key_up(events.key.keysym.sym,events.key.keysym.mod,
                       events.key.keysym.unicode);
  }
}


void key_up(SDLKey sym, SDLMod mod, Uint16 unicode) { 
  switch(sym) {
    case SDLK_SPACE:
      switch(mode) {
        case FIXED_BALL_SPAWN:
          add_ball();
        break;
        case RANDOM_BALL_SPAWN:
          add_random_ball();
        break;
        case FIXED_HARD_BALL_SPAWN:
          add_hard_ball();
        break;
        case RANDOM_HARD_BALL_SPAWN:
          add_random_hard_ball();
        break;
      }
    break;
    case SDLK_m:
      switch_mode();
    break;
  }
}


void add_ball() {
  Position& pos = positions[entity_nb];
  Speed& speed = speeds[entity_nb];
  Rectangle& rect = rectangles[entity_nb];
  pos.x = 0;
  pos.y = 0;
  speed.vx = speed_factor;
  speed.vy = speed_factor;
  rect.w = size_factor;
  rect.h = size_factor;
  ++entity_nb;
}


void add_random_ball() {
  Position& pos = positions[entity_nb];
  Speed& speed = speeds[entity_nb];
  Rectangle& rect = rectangles[entity_nb];
  pos.x = rand() % WWIDTH;
  pos.y = rand() % WHEIGHT;
  speed.vx = rand() % 4*speed_factor - 2*speed_factor;
  speed.vy = rand() % 4*speed_factor - 2*speed_factor;
  rect.w = size_factor;
  rect.h = size_factor;
  ++entity_nb;
}


void add_hard_ball() {
  Position& pos = positions[entity_nb];
  Speed& speed = speeds[entity_nb];
  Rectangle& rect = rectangles[entity_nb];
  AABB& mask = aabbs[entity_nb];
  pos.x = 0;
  pos.y = 0;
  speed.vx = speed_factor;
  speed.vy = speed_factor;
  rect.w = size_factor;
  rect.h = size_factor;
  mask.w = size_factor;
  mask.h = size_factor;
  ++entity_nb;
}


void add_random_hard_ball() {
  Position& pos = positions[entity_nb];
  Speed& speed = speeds[entity_nb];
  Rectangle& rect = rectangles[entity_nb];
  AABB& mask = aabbs[entity_nb];
  pos.x = rand() % WWIDTH;
  pos.y = rand() % WHEIGHT;
  speed.vx = rand() % 4*speed_factor - 2*speed_factor;
  speed.vy = rand() % 4*speed_factor - 2*speed_factor;
  rect.w = size_factor;
  rect.h = size_factor;
  mask.w = size_factor;
  mask.h = size_factor;
  ++entity_nb;
}


void switch_mode() {
  ++mode;
  mode = mode % (int)MAX_MODE;
  printf("switch to mode : %d\n", mode);
}


void init_entities() {
  // add_ball();
}


void loop() {
  running = true;
  while(running) { 
    clear_screen();
    manage_inputs();
    for (int i = 0; i <= entity_nb; ++i) {
      update_position(i);
      check_collision(i);
      render(i);
    }
    SDL_GL_SwapBuffers(); // refresh screen
  }
}


int main(int argc, char** argv) {
  init_sdl();
  init_entities();
  printf("starting pong\n"); 
  loop();
  printf("stopping pong\n");
  return 0;
}
