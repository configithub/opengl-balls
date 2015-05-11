#include "render_tools.h"
#include "constants.h"


bool init_sdl() {
  if ( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO|SDL_INIT_JOYSTICK) == -1 ) {
    return false;
  }
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
  SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
  if(! SDL_SetVideoMode(WWIDTH, WHEIGHT, BPP_DEPTH, SDL_OPENGL|SDL_DOUBLEBUF)  ) {
    return false;
  }
  glEnable(GL_BLEND);
  glViewport(0, 0, WWIDTH, WHEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, WWIDTH, WHEIGHT, 0, -1, 1);
  glScalef(1, 1, 1);
  glMatrixMode(GL_MODELVIEW);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glDisable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);
  return true;
}


void clear_screen() {
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}


void draw_line(int x1, int y1, int x2, int y2) {
  glColor4f(0.0f,1.0f,0.0f,1.0f);
  GLfloat vertices[] = {x1,y1, x2,y2};
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, 0, vertices);
  glDrawArrays(GL_LINES, 0, 2);
  glDisableClientState(GL_VERTEX_ARRAY);
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void draw_white_line(int x1, int y1, int x2, int y2) {
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  GLfloat vertices[] = {x1,y1, x2,y2};
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, 0, vertices);
  glDrawArrays(GL_LINES, 0, 2);
  glDisableClientState(GL_VERTEX_ARRAY);
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}


void draw_triangle(int x1, int y1, int x2, int y2, 
                                        int x3, int y3) {
  GLfloat vertices[] = {x1,y1, x2,y2, x3,y3};
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, 0, vertices);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableClientState(GL_VERTEX_ARRAY);
}




void draw_hollow_square(int x1, int y1, int x2, int y2, 
                 int x3, int y3, int x4, int y4) {
  draw_line(x1, y1, x2, y2);
  draw_line(x2, y2, x3, y3);
  draw_line(x3, y3, x4, y4);
  draw_line(x4, y4, x1, y1);
}

void draw_square(int x1, int y1, int x2, int y2, 
                 int x3, int y3, int x4, int y4) {
  GLfloat vertices[] = {x1,y1, x2,y2, x3,y3, x4,y4};
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, 0, vertices);
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
  glDisableClientState(GL_VERTEX_ARRAY);
}


void draw_square_gradient(int x1, int y1, int x2, int y2, 
                        int x3, int y3, int x4, int y4,
                        float r1, float g1, float b1,
                        float r2, float g2, float b2,
                        float r3, float g3, float b3,
                        float r4, float g4, float b4) {
  GLfloat vertices[] = {x1,y1, x2,y2, x3,y3, x4,y4};
  GLfloat colors[] = { r1,g1,b1, r2,g2,b2,
                       r3,g3,b3, r4,g4,b4 };
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glVertexPointer(2, GL_FLOAT, 0, vertices);
  glColorPointer(3, GL_FLOAT, 0, colors);
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
}









