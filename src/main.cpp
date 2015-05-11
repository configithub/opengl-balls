#include "main.h"
#include <stdio.h>
#include "render_tools.h"

#include "position.h"
#include "rectangle.h"

SDL_Event events;
bool running;
int entities[max_entity_nb];
int entity_nb = 0;

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
      add_ball();
    break;
  }
}


void add_ball() {
  Position& pos = positions[entity_nb];
  Speed& speed = speeds[entity_nb];
  Rectangle& rect = rectangles[entity_nb];
  pos.x = 0;
  pos.y = 0;
  speed.vx = 10;
  speed.vy = 10;
  rect.w = 5;
  rect.h = 5;
  ++entity_nb;
}

void init_entities() {
  add_ball();
}


void loop() {
  running = true;
  while(running) { 
    clear_screen();
    manage_inputs();
    for (int i = 0; i <= entity_nb; ++i) {
      update_position(i);
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
