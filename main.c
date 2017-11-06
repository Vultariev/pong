#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "clamp.h"
#include "frame.h"


int main(void)
{
  bool running = true;

  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window* win1 = SDL_CreateWindow("Test",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,900,400,SDL_WINDOW_RESIZABLE);

  SDL_Renderer* ren = SDL_CreateRenderer(win1,-1,SDL_RENDERER_ACCELERATED);

  SDL_Surface* ballimg = SDL_LoadBMP("Resources/images/ball.bmp");

  //SDL_Surface* paddleimg = SDL_LoadBMP("Resources/images/paddle.bmp");

  SDL_Texture* ball = SDL_CreateTextureFromSurface(ren,ballimg);

  SDL_Rect balldata;
  SDL_Rect paddlel;
  SDL_Rect paddler;

  color uiColor = toColor(255, 255, 255, 255);
  color bColor = toColor(0,0,0,255);

  paddler.h = 50;
  paddler.w = 10;

  double ballspd = 6;
  double ballang = 45;

  balldata.w = 10;
  balldata.h = 10;

  balldata.x = GetWindowSize(win1).x/2;
  balldata.y = GetWindowSize(win1).y/2;


  SDL_Event event;

  ballvel.x = 1;
  ballvel.y = -1;

  void resetBall()
  {
    balldata.x = GetWindowSize(win1).x/2;
    balldata.y = GetWindowSize(win1).y/2;
    double ballspd = 6;
    double ballang = 45;
  }

  while(running)
  {
    SetRenderDrawColor(ren,bColor);
    SDL_RenderFillRect(ren,NULL);

    while(SDL_PollEvent(&event))
    {
      if(event.type != 0)
      {
        if(event.type == SDL_QUIT)
        {
          running = false;
        }
      }
      if(event.type == SDL_MOUSEMOTION)
      {
        paddler.y = event.motion.y - paddler.h/2;
      }
    }
    if(balldata.x >= paddler.x - balldata.w && balldata.x <= paddler.x + paddler.w)
    {
      if(balldata.y - balldata.h < paddler.y + paddler.h && balldata.y > paddler.y)
      {
        ballspd += 1;
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
    }
    if(balldata.x + balldata.w >= GetWindowSize(win1).x)
    {
      //resetBall();
      running = false;
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
    paddler.x = 0.9*GetWindowSize(win1).x;
    SetRenderDrawColor(ren,uiColor);
    SDL_RenderFillRect(ren,&paddler);
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
