#include <math.h>
#include <stdbool.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "frame.h"
#define PI 3.14159265358979

#define PI 3.14159265358979

//typedef struct color color;

/*double getBallDirection(void)
{
  return atan(ballvel.x/ballvel.y);
}
double getBallSpeed(void)
{
  return ballvel.x/sin(getBallDirection());
}*/

color toColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
  color out;
  out.r = r;
  out.g = g;
  out.b = b;
  out.a = a;
  return out;
}

//typedef struct vec2 vec2;
vec2 GetWindowSize(SDL_Window* window)
{
  vec2 out;
  int x,y;
  SDL_GetWindowSize(window,&x,&y);
  out.x = x;
  out.y = y;
  return out;
}

int SetRenderDrawColor(SDL_Renderer *renderer, color in)
{
  return SDL_SetRenderDrawColor(renderer, in.r, in.g, in.b, in.a);
}

void resetWalls(bool *wall)
{
  walls.top = false;
  walls.bottom = false;
  walls.left = false;
  walls.right = false;
  *wall = true;
}


double todeg(double rad)
{
  return (rad/PI)*180;
}
double torad(double deg)
{
  return (PI*deg)/180;
}

void setBallSpeed(double speed, double direction)
{
  ballvel.x = sin(torad(direction))*speed;
  ballvel.y = cos(torad(direction))*speed;
}
