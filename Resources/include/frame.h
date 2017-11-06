#include "SDL2/SDL.h"
#include <stdbool.h>

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
struct vec2 {
  double x;
  double y;
};

typedef struct color color;
typedef struct vec2 vec2;

color toColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

vec2 GetWindowSize(SDL_Window* window);

int SetRenderDrawColor(SDL_Renderer *renderer, color in);

void resetWalls(bool *wall);

vec2 ballvel;

double todeg(double rad);
double torad(double deg);

void setBallSpeed(double speed, double direction);

//void resetBall();
