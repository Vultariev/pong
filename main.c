#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "clamp.h"
#define PI 3.14159265358979
struct walls {
  //Values represent which wall the ball colided with last
  bool top;
  bool bottom;
  bool left;
  bool right;
} walls;

struct color {
  Uint8 r;
  Uint8 g;
  Uint8 b;
  Uint8 a;
};

typedef struct color color;

color toColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
  color out;
  out.r = r;
  out.g = g;
  out.b = b;
  out.a = a;
  return out;
}

struct vec2 {
  double x;
  double y;
};

typedef struct vec2 vec2;
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

vec2 ballvel;

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

/*double getBallDirection(void)
{
  return atan(ballvel.x/ballvel.y);
}
double getBallSpeed(void)
{
  return ballvel.x/sin(getBallDirection());
}*/

int main(void)
{
  bool running = true;

  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window* win1 = SDL_CreateWindow("Test",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,640,400,SDL_WINDOW_RESIZABLE);

  SDL_Renderer* ren = SDL_CreateRenderer(win1,-1,SDL_RENDERER_ACCELERATED);

  SDL_Surface* ballimg = SDL_LoadBMP("Resources/images/ball.bmp");

  //SDL_Surface* paddleimg = SDL_LoadBMP("Resources/images/paddle.bmp");

  SDL_Texture* ball = SDL_CreateTextureFromSurface(ren,ballimg);

  SDL_Rect balldata;
  SDL_Rect paddlel;
  SDL_Rect paddler;
  color uiColor = toColor(255, 255, 255, 255);

  double ballspd = 6;
  double ballang = 45;

  balldata.w = 10;
  balldata.h = 10;

  balldata.x = GetWindowSize(win1).x/2;
  balldata.y = GetWindowSize(win1).y/2;


  SDL_Event event;

  ballvel.x = 1;
  ballvel.y = -1;

  while(running)
  {
    SDL_PollEvent(&event);

    SDL_RenderFillRect(ren,NULL);

    if(event.type != 0)
    {
      if(event.type == SDL_QUIT)
      {
        running = false;
      }
    }
    if(balldata.x >= GetWindowSize(win1).x - balldata.w)
    {
      ballang = -abs(ballang);
      if(rand() / (double)RAND_MAX - 0.5 > 0)
      {
        ballang += (rand() / (double)RAND_MAX) * 10;
      }
      else
      {
        ballang -= (rand() / (double)RAND_MAX) * 10;
      }
      resetWalls(&walls.right);
    }
    if(balldata.x <= 0)
    {
      ballang = abs(ballang);
      if(rand() / (double)RAND_MAX - 0.5 > 0)
      {
        ballang += (rand() / (double)RAND_MAX) * 10;
      }
      else
      {
        ballang -= (rand() / (double)RAND_MAX) * 10;
      }
      resetWalls(&walls.left);
    }
    if(balldata.y >= GetWindowSize(win1).y - balldata.h)
    {
      ballang = ballang < 90 && ballang > -90 ? 180 - ballang : ballang;
      if(rand() / (double)RAND_MAX - 0.5 > 0)
      {
        ballang += (rand() / (double)RAND_MAX) * 10;
      }
      else
      {
        ballang -= (rand() / (double)RAND_MAX) * 10;
      }
      resetWalls(&walls.bottom);
    }
    if(balldata.y <= 0)
    {
      ballang = ballang < 90 && ballang > -90 || 1 ? 180 - ballang: ballang;
      if(rand() / (double)RAND_MAX - 0.5 > 0)
      {
        ballang += (rand() / (double)RAND_MAX) * 10;
      }
      else
      {
        ballang -= (rand() / (double)RAND_MAX) * 10;
      }
      resetWalls(&walls.top);
    }

    ballang = clamp(ballang,-180,180);
    setBallSpeed(ballspd,ballang);
    balldata.x = balldata.x + ballvel.x;
    balldata.y = balldata.y + ballvel.y;
    SDL_RenderCopy(ren,ball,NULL,&balldata);
    SDL_RenderPresent(ren);
    printf("B: s: %f  d: %f  vx: %f  vy: %f\r rnd: %f",ballspd,ballang,ballvel.x,ballvel.y,rand() / (double)RAND_MAX);
    SDL_Delay(1000/60);
  }
  printf("\n");
  SDL_DestroyTexture(ball);
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win1);
  SDL_Quit();
  return 0;
}
