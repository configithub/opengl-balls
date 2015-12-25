#ifndef _RENDER_TOOLS_H_
#define _RENDER_TOOLS_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <stdbool.h>
#include <map>
#include <string>


class Texture {
public:
  Texture() { loaded = false; }
  int w,h;
  int id; // glid
  bool loaded;
};

// hold all textures
extern std::map<std::string, Texture> textures;


bool init_sdl();

void clear_screen();

void draw_line(int x1, int y1, int x2, int y2);

void draw_triangle(int x1, int x2, int y1, int y2, 
                                        int x3, int y3);


void draw_hollow_square(int x1, int y1, int x2, int y2, 
                 int x3, int y3, int x4, int y4);

void draw_square(int x1, int y1, int x2, int y2, 
                 int x3, int y3, int x4, int y4);


void draw_square_gradient(int x1, int y1, int x2, int y2, 
                        int x3, int y3, int x4, int y4,
                        float r1, float g1, float b1,
                        float r2, float g2, float b2,
                        float r3, float g3, float b3,
                        float r4, float g4, float b4);


void load_png(const char* name);

void draw_rectangle_texture(const Texture& t, int x, int y, 
                    int xtex, int ytex, int wtex, int htex);
               // GLfloat r, GLfloat g, GLfloat b, GLfloat a);


#endif
