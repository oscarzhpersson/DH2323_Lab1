/*
 * SDL2 skeleton for lab assignments 1–3 of the KTH course DH2323,
 * Computer Graphics and Interaction (and also SU DA3001, Datalogi II).
 *
 * See README.md for details.
 */

#include <iostream>
//#include <glm/glm.hpp>
#include "/usr/local/include/glm/glm.hpp"
#include <vector>
#include "SDL2auxiliary.h"

using namespace std;
using glm::vec3;
using glm::vec2;

// --------------------------------------------------------
// GLOBAL VARIABLES

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL2Aux *sdlAux;

int t;

vector<vec3> stars( 1000 );

// --------------------------------------------------------
// FUNCTION DECLARATIONS

void Draw();

// --------------------------------------------------------
// FUNCTION DEFINITIONS

vec2 projection(vec3 position, float h, float w)
{
  float focalLength = h / 2;
  float u = ( focalLength * (position.x / position.z) ) + (w / 2);
  float v = ( focalLength * (position.y / position.z) ) + (h / 2);

  return vec2(u, v);
}

void Update()
{
  float velocity = 0.001;

  // Calculate the delta between frames (function calls).
  int t2 = SDL_GetTicks();
  float dt = float(t2-t);
  t = t2;

  for( int s=0; s<stars.size(); ++s )
  {
        // Add code for update of stars.
        stars[s] = vec3(stars[s].x, stars[s].y, stars[s].z - velocity * dt);

        // Wrap-around functionality.
        if( stars[s].z <= 0 )
          stars[s].z += 1;
        if( stars[s].z > 1 )
          stars[s].z -= 1;
  }

}

int main(int argc, char* argv[])
{

  //Create a for-loop in the beginning of the main function that loops through all stars and sets random positions within.
  for (int i = 0; i < stars.size(); ++i)
  {
    // ? Hacky solution, maybe change?
    float x = (float(rand()) / float(RAND_MAX) * 2) - 1;
    float y = (float(rand()) / float(RAND_MAX) * 2) - 1;
    float z = float(rand()) / float(RAND_MAX);

    //Test printout.
    //std::cout << '(' << x << ' ' << y << ' ' << z << ')' << '\n';

    stars[i] = vec3(x, y, z);
  }

  sdlAux = new SDL2Aux(SCREEN_WIDTH, SCREEN_HEIGHT);

  while (!sdlAux->quitEvent())
  {
    Update();
    Draw();
  }

  sdlAux->saveBMP("screenshot.bmp");
  return 0;
}

void Draw() {

  sdlAux->clearPixels();
  
  // TODO: Temporary for SDL_FillRect as I can't get this to work on SDL2.0. Change this ASAP.
  for (int y = 0; y < SCREEN_HEIGHT; ++y)
  {
    for (int x = 0; x < SCREEN_WIDTH; ++x)
    {
      vec3 color(0.0, 0.0, 0.0);
      sdlAux->putPixel(x, y, color);
    }
  }

  for( size_t s=0; s<stars.size(); ++s )
  {
        // Add code for projecting and drawing each star
        vec2 pos = projection(stars[s], SCREEN_HEIGHT, SCREEN_WIDTH);
        vec3 color = 0.2f * vec3(1,1,1) / (stars[s].z*stars[s].z);
        sdlAux->putPixel(pos.x, pos.y, color);
  }

  sdlAux->render();
}


/*SDL_Surface *s;
  s = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
  SDL_FillRect(s, 0, 0);
  //SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 0, 0, 0));

  //SDL_FillRect( sdlAux, 0, 0 );

  //SDL_FillRect*/