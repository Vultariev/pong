#include <stdbool.h>
#include <stdio.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#define PI 3.14159265358979
struct walls {
  //Values represent which wall the ball colided with last
  bool top;
  bool bottom;
  bool left;
  bool right;
} walls;

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
  return rad/PI*180;
}
double torad(double deg)
{
  return 180*PI*deg;
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

  double ballspd = 2;
  double ballang = 45;

  balldata.w = 10;
  balldata.h = 10;

  balldata.x = 0;
  balldata.y = 0;


  SDL_Event event;

  ballvel.x = 1;
  ballvel.y = -1;

  while(running)
  {
    SDL_PollEvent(&event);

    SDL_RenderClear(ren);
    SDL_RenderCopy(ren,ball,NULL,&balldata);
    SDL_RenderPresent(ren);

    if(event.type != 0)
    {
      if(event.type == SDL_QUIT)
      {
        running = false;
      }
    }
    balldata.x += ballvel.x;
    balldata.y += ballvel.y;
    if(balldata.x >= GetWindowSize(win1).x - balldata.w)
    {
      ballvel.x = -abs(ballvel.x);
      resetWalls(&walls.right);
    }
    if(balldata.x <= 0)
    {
      ballvel.x = abs(ballvel.x);
      resetWalls(&walls.left);
    }
    if(balldata.y >= GetWindowSize(win1).y - balldata.h)
    {
      ballvel.y = -abs(ballvel.y);
      resetWalls(&walls.top);
    }
    if(balldata.y <= 0)
    {
      ballvel.y = abs(ballvel.y);
      resetWalls(&walls.bottom);
    }
    setBallSpeed(ballspd,ballang);
    printf("B: s: %f  d: %f\r",getBallSpeed(),todeg(getBallDirection()));
    SDL_Delay(3);
  }
  end:
  SDL_DestroyTexture(ball);
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win1);
  SDL_Quit();
  return 0;
}
