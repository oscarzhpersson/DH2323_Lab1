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

// --------------------------------------------------------
// GLOBAL VARIABLES

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL2Aux *sdlAux;

// --------------------------------------------------------
// FUNCTION DECLARATIONS

void Draw();

// --------------------------------------------------------
// FUNCTION DEFINITIONS

int main(int argc, char* argv[]) {
  sdlAux = new SDL2Aux(SCREEN_WIDTH, SCREEN_HEIGHT);

  while (!sdlAux->quitEvent()) {
    Draw();
  }

  sdlAux->saveBMP("screenshot.bmp");
  return 0;
}

void Draw() {
  sdlAux->clearPixels();

  for (int y = 0; y < SCREEN_HEIGHT; ++y) {
    for (int x = 0; x < SCREEN_WIDTH; ++x) {
      vec3 color(0.0, 0.0, 1.0);
      sdlAux->putPixel(x, y, color);
    }
  }

  sdlAux->render();
}
