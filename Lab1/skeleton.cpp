/*
 * SDL2 skeleton for lab assignments 1–3 of the KTH course DH2323,
 * Computer Graphics and Interaction (and also SU DA3001, Datalogi II).
 *
 * See README.md for details.
 */

#include <iostream>
#include <glm/glm.hpp>
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
void Interpolate( float a, float b, vector<float>& result );
void Interpolate( vec3 a, vec3 b, vector<vec3>& result );

// --------------------------------------------------------
// FUNCTION DEFINITIONS

int main(int argc, char* argv[])
{
  sdlAux = new SDL2Aux(SCREEN_WIDTH, SCREEN_HEIGHT);

  while (!sdlAux->quitEvent()) {
    Draw();
  }

  sdlAux->saveBMP("screenshot.bmp");
  return 0;
}

void Draw()
{

  vec3 topLeft(1,0,0); // red
  vec3 topRight(0,0,1); // blue
  vec3 bottomLeft(1,1,0); // green
  vec3 bottomRight(0,1,0); // yellow

  vector<vec3> leftSide( SCREEN_HEIGHT );
  vector<vec3> rightSide( SCREEN_HEIGHT );
  Interpolate( topLeft, bottomLeft, leftSide );
  Interpolate( topRight, bottomRight, rightSide );

  sdlAux->clearPixels();

  for (int y = 0; y < SCREEN_HEIGHT; ++y) {

    vector<vec3> color( SCREEN_WIDTH );
    Interpolate(leftSide[y], rightSide[y], color);

    for (int x = 0; x < SCREEN_WIDTH; ++x) {
      sdlAux->putPixel(x, y, color[x]);
    }
  }

  sdlAux->render();
}

/*void Draw()
{
  sdlAux->clearPixels();

  for (int y = 0; y < SCREEN_HEIGHT; ++y) {
    for (int x = 0; x < SCREEN_WIDTH; ++x) {
      vec3 color(1.0, 0.3, 0.7);
      sdlAux->putPixel(x, y, color);
    }
  }

  sdlAux->render();
}*/

vec3 numToVec3(float num)
{
  return vec3(num, num, num);
}

float calcInterpolationValue(float a, float b, float c)
{
  return (b - a + 1 * ((b-a)/abs(b-a)))/c;
}

void Interpolate( vec3 a, vec3 b, vector<vec3>& result )
{

  if (result.size() == 1)
    result[0] = a;

  //vec3 interpolation = (b - a + (numToVec3(1) * sign(b - a))) / numToVec3(result.size());
  vec3 interpolation = (b - a ) / (numToVec3(result.size() - 1));

  result[0] = a;

  for (int i = 1; i < result.size(); i++)
  {
    result[i] = result[i - 1] + interpolation;
  }
}

void Interpolate( float a, float b, vector<float>& result )
{
  //float interpolation = b / (a + 1);
  //float interpolationValue = interpolation / result.size();

  // Base case handling.
  if (result.size() == 1)
    result[0] = a;
  
  //float interpolation = (b - a + 1 * ((b-a)/abs(b-a)))/result.size();
  float interpolation = (b - a)/(result.size()-1);

  result[0] = a;

  for (int i = 1; i < result.size(); i++)
  {
    //result[i] = result[i - 1] + interpolationValue;
    result[i] = result[i - 1] + interpolation;
  }
}

void InterpolationTest()
{
  vector<float> resultFloatA( 10 ); // Create a vector width 10 floats
  Interpolate( 5, 14, resultFloatA ); // Fill it with interpolated values
  for( int i=0; i<resultFloatA.size(); ++i )
    cout << resultFloatA[i] << " "; // Print the result to the terminal
  
  printf("\n\n\n");

  vector<float> resultFloatB( 10 ); // Create a vector width 10 floats
  Interpolate( 14, 5, resultFloatB ); // Fill it with interpolated values
  for( int i=0; i<resultFloatB.size(); ++i )
    cout << resultFloatB[i] << " "; // Print the result to the terminal
  
  printf("\n\n\n");

  vector<float> resultFloatC( 4 ); // Create a vector width 10 floats
  Interpolate( 9.2, 9.8, resultFloatC ); // Fill it with interpolated values
  for( int i=0; i<resultFloatC.size(); ++i )
    cout << resultFloatC[i] << " "; // Print the result to the terminal
  
  printf("\n\n\n");

  vector<vec3> result( 4 );
  vec3 a(1,4,9.2);
  vec3 b(4,1,9.8);
  Interpolate( a, b, result );
  for( int i=0; i<result.size(); ++i )
  {
        cout << "( "
        << result[i].x << ", "
        << result[i].y << ", "
        << result[i].z << " ) ";
  }
}
