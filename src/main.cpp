#include "main.h"
#include <stdio.h>

SDL_Event events;
bool running;
Entity entities[max_entity_nb];
int entity_nb = 0;

const int speed_factor = 4;
const int size_factor = 20;

const int starting_entity_nb = 15;

int mode = 6; // RANDOM_FALLING_BALL_SPAWN



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
        case RANDOM_ROTATED_BALL_SPAWN:
          add_random_rotated_ball();
        break;
        case RANDOM_ROTATING_BALL_SPAWN:
          add_random_rotating_ball();
        break;
        case RANDOM_FALLING_BALL_SPAWN:
          add_falling_ball();
        break;
      }
    break;
    case SDLK_m:
      switch_mode();
    break;
    case SDLK_r:
      respawn();
    break;
  }
}


void add_ball() {
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
  entity.flags = GHOST;
  ++entity_nb;
}


void add_random_ball() {
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
  entity.flags = GHOST;
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


void add_random_rotated_ball() {
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
  entity.position->theta = 2 * PI * (float) (rand() % 100) / 100;
  ++entity_nb;
}


void add_random_rotating_ball() {
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
  entity.position->theta = 2 * PI * (float) (rand() % 100) / 100;
  entity.speed->omega = PI *( (float) (rand() % 20) / 250);
  ++entity_nb;
}


void add_falling_ball() {
  Entity& entity = entities[entity_nb];
  entity.id = entity_nb;
  entity.position = position_factory.create();
  entity.speed = speed_factory.create();
  entity.shape = shape_factory.create();
  entity.mask = mask_factory.create();
  entity.accel = accel_factory.create();
  entity.position->x = rand() % WWIDTH;
  entity.position->y = rand() % WHEIGHT;
  entity.speed->vx = rand() % 4*speed_factor - 2*speed_factor;
  entity.speed->vy = rand() % 4*speed_factor - 2*speed_factor;
  entity.shape->w = size_factor;
  entity.shape->h = size_factor;
  entity.mask->w = size_factor;
  entity.mask->h = size_factor;
  entity.position->theta = 2 * PI * (float) (rand() % 100) / 100;
  entity.speed->omega = PI *( (float) (rand() % 20) / 250);
  entity.flags = GRAVITY_BOUND;
  entity.accel->friction = 1;
  ++entity_nb;
}


void switch_mode() {
  ++mode;
  mode = mode % (int)MAX_MODE;
  printf("switch to mode : %d\n", mode);
}


void init_entities() {
  for (int i = 0; i < starting_entity_nb; i++) {
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
      case RANDOM_ROTATED_BALL_SPAWN:
        add_random_rotated_ball();
      break;
      case RANDOM_ROTATING_BALL_SPAWN:
        add_random_rotating_ball();
      break;
      case RANDOM_FALLING_BALL_SPAWN:
        add_falling_ball();
      break;
    }
  }
}


void respawn() {
  for (int i = 0; i <= entity_nb; ++i) {
    Entity& entity = entities[i];
    entity.remove();
  }
  entity_nb = 0;
  init_entities();
}


void apply_gravity() {
  for (int i = 0; i <= entity_nb; ++i) {
    Entity& entity = entities[i];
    if(entity.accel == NULL) { continue; }
    entity.accel->ay = entity.flags & GRAVITY_BOUND ? 2 : 0;
  }
}


void update_positions() {
  for (int i = 0; i <= entity_nb; ++i) {
    Entity& entity = entities[i];
    update_position_inertial(entity);
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
    render_rotated(entity);
  }
}


void loop() {
  running = true;
  while(running) { 
    clear_screen();
    manage_inputs();
    apply_gravity();
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
