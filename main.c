#include <stdbool.h>
#include <stdio.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

int main(void)
{
  bool running = true;

  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window* win1 = SDL_CreateWindow("Test",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,640,400,0);

  SDL_Renderer* ren = SDL_CreateRenderer(win1,-1,SDL_RENDERER_ACCELERATED);

  SDL_Surface* ballimg = SDL_LoadBMP("Resources/images/ball.bmp");

  //SDL_Surface* paddleimg = SDL_LoadBMP("Resources/images/paddle.bmp");

  SDL_Texture* ball = SDL_CreateTextureFromSurface(ren,ballimg);

  SDL_Rect balldata;

  balldata.w = 20;
  balldata.h = 20;

  balldata.x = 0;
  balldata.y = 0;


  SDL_Event event;

  bool ballright = true;

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
    if(ballright)
    {
      balldata.x += 1;
    }
    else
    {
      balldata.x -= 1;
    }
    if(balldata.x >=640 - balldata.w)
    {
      ballright = false;
    }
    if(balldata.x <= 0)
    {
      ballright = true;
    }
    SDL_Delay(3);
  }
  end:
  SDL_DestroyTexture(ball);
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win1);
  SDL_Quit();
  return 0;
}
