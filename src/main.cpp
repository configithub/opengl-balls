#include "main.h"
#include <stdio.h>
#include "render_tools.h"

#include "entity.h"

SDL_Event events;
bool running;
Entity entities[max_entity_nb];
int entity_nb = 0;

const int speed_factor = 2;
const int size_factor = 20;

const int starting_entity_nb = 20;

int mode = 3;

// component factories
PositionFactory position_factory;
SpeedFactory speed_factory;
RectangleFactory shape_factory;
AABBFactory mask_factory;


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
  Entity& entity = entities[entity_nb];
  entity.id = entity_nb;
  entity.position = position_factory.create();
  entity.speed = speed_factory.create();
  entity.shape = shape_factory.create();
  entity.position->x = 0;
  entity.position->y = 0;
  entity.speed->vx = speed_factor;
  entity.speed->vy = speed_factor;
  entity.shape->w = size_factor;
  entity.shape->h = size_factor;
  ++entity_nb;
}


void add_random_ball() {
  Entity& entity = entities[entity_nb];
  entity.id = entity_nb;
  entity.position = position_factory.create();
  entity.speed = speed_factory.create();
  entity.shape = shape_factory.create();
  entity.position->x = rand() % WWIDTH;
  entity.position->y = rand() % WHEIGHT;
  entity.speed->vx = rand() % 4*speed_factor - 2*speed_factor;
  entity.speed->vy = rand() % 4*speed_factor - 2*speed_factor;
  entity.shape->w = size_factor;
  entity.shape->h = size_factor;
  ++entity_nb;
}


void add_hard_ball() {
  Entity& entity = entities[entity_nb];
  entity.id = entity_nb;
  entity.position = position_factory.create();
  entity.speed = speed_factory.create();
  entity.shape = shape_factory.create();
  entity.mask = mask_factory.create();
  entity.position->x = 0;
  entity.position->y = 0;
  entity.speed->vx = speed_factor;
  entity.speed->vy = speed_factor;
  entity.shape->w = size_factor;
  entity.shape->h = size_factor;
  entity.mask->w = size_factor;
  entity.mask->h = size_factor;
  ++entity_nb;
}


void add_random_hard_ball() {
  Entity& entity = entities[entity_nb];
  entity.id = entity_nb;
  entity.position = position_factory.create();
  entity.speed = speed_factory.create();
  entity.shape = shape_factory.create();
  entity.mask = mask_factory.create();
  entity.position->x = rand() % WWIDTH;
  entity.position->y = rand() % WHEIGHT;
  entity.speed->vx = rand() % 4*speed_factor - 2*speed_factor;
  entity.speed->vy = rand() % 4*speed_factor - 2*speed_factor;
  entity.shape->w = size_factor;
  entity.shape->h = size_factor;
  entity.mask->w = size_factor;
  entity.mask->h = size_factor;
  ++entity_nb;
}


void switch_mode() {
  ++mode;
  mode = mode % (int)MAX_MODE;
  printf("switch to mode : %d\n", mode);
}


void init_entities() {
  for (int i = 0; i < starting_entity_nb; i++) {
    add_random_hard_ball();
  }
}


void update_positions() {
  for (int i = 0; i <= entity_nb; ++i) {
    Entity& entity = entities[i];
    update_position(entity);
  }
}


void do_collisions() {
  for (int i = 0; i <= entity_nb; ++i) {
    Entity& entity = entities[i];
    check_collision(entity);
  }
}


void do_render() {
  for (int i = 0; i <= entity_nb; ++i) {
    Entity& entity = entities[i];
    render(entity);
  }
}


void loop() {
  running = true;
  while(running) { 
    clear_screen();
    manage_inputs();
    update_positions();
    do_collisions();
    do_render();
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
