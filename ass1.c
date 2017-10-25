//-----------------------------------------------------------------------------
// ass1.c
//
// <Explanation of the program ...>
// <... May have multiple lines.>
//
// Group: Group 2, study assistant Florian Hager TODO
//
// Authors:
// Stefan Fragner TODO: <Matriculum Number>
// Tobias Topar 11710538
//-----------------------------------------------------------------------------
//

#include <stdio.h>
#include <float.h>
#include <math.h>
#include <limits.h>


#define TRIANGLE_SIDES 3

// WETHER ? TODO

//-----------------------------------------------------------------------------
///
/// This Function tests if the three given sides can form a triangle.
/// The sides must be sorted in rising order. TODO
/// And it prints out the appropriate information.
///
/// @param index the index associated with the triangle
/// @param triangle an array containing the three sides of a triangle
//
void testIfTriangle(int index, float triangle[TRIANGLE_SIDES])
{
  // Tests if the given sides can form a triangle (triangle inequality)
  if(triangle[0] + triangle[1] > triangle[2])
  {

    // Prints out the index and sides of the given triangle
    printf("Triplet %i (a=%f, b=%f, c=%f) is a triangle.\n",
           index, triangle[0], triangle[1], triangle[2]);

    // Checks if the given triangle is an isosceles triangle
    if(fabsf(triangle[0] - triangle[1]) < FLT_EPSILON ||
        fabsf(triangle[1] - triangle[2]) < FLT_EPSILON)
    {

      // Checks if the given triangle is an equilateral triangle
      if(fabsf(triangle[0] - triangle[2]) < FLT_EPSILON)
      {
        printf("  It is an equilateral triangle.\n");
      }

      printf("  It is an isosceles triangle.\n");
    }

    // Checks if the given triangle is a right triangle
    if(fabsf((triangle[0] * triangle[0] + triangle[1] * triangle[1]) -
             triangle[2] * triangle[2]) < FLT_EPSILON)
    {
      printf("  It is a right triangle.\n");
    }
  }
  else // If the given sides can't form a triangle
  {
    // prints out the given index and sides
    printf("Triplet %i (a=%f, b=%f, c=%f) is NO triangle.\n",
           index, triangle[0], triangle[1], triangle[2]);
  }
}


int clearInput()
{
  char c;
  int counter = 0;

  do
  {
    if(scanf("%c", &c) < 0)
    {
      return 0;
    }

    if(c != ' ')
    {
      ++counter;
    }

  } while(c != '\n');

  return counter;
}


int getNumTriangles()
{
  int result, clearedCharacters, numTriangles;

  while(1)
  {
    printf("Please enter the number of triangles to check: ");

    result = scanf("%i", &numTriangles);
    clearedCharacters = clearInput();

    if (result < 0 || clearedCharacters == 0)
    {
      return 0;
    }

    if (clearedCharacters == 1 && result == 1 && numTriangles >= 1 &&
        numTriangles <= UCHAR_MAX)
    {
      return numTriangles;
    }

    printf("[ERR] Invalid number of triangles.\n");
  }

}


float getTriangleSide(char* textNumber)
{
  int result, clearedCharacters;
  double triangleSide;

  while(1)
  {
    printf("Please enter the %s number of the triplet: ", textNumber);

    result = scanf("%lf", &triangleSide);
    clearedCharacters = clearInput();

    if (result < 0 || clearedCharacters == 0)
    {
      return 0;
    }

    if (clearedCharacters == 1 && result == 1 && triangleSide > 0.0 &&
        triangleSide <= FLT_MAX)
    {
      return (float)triangleSide;
    }

    printf("[ERR] Invalid number for the triplet.\n");
  }

}


int main() {

  char* textNumber[TRIANGLE_SIDES] = {"first","second","third"};

  int numTriangles = getNumTriangles();

  if (numTriangles == 0)
  {
    return 0;
  }

  
  float triangles[numTriangles][TRIANGLE_SIDES];

  for(int i = 0; i < numTriangles;  i++)
  {
    for (int side = 0; side < TRIANGLE_SIDES; side++)
    {
      triangles[i][side] = getTriangleSide(textNumber[side]);
    }
  }

  
  float buffer;
  
  for(int i = 0; i < numTriangles; i++)
  {
    for(int run = 1; run < TRIANGLE_SIDES; run++)
    {
      for (int side = 0; side < TRIANGLE_SIDES - run; side++)
      {
        if (triangles[i][side] > triangles[i][side + 1])
        {
          buffer = triangles[i][side];
          triangles[i][side] = triangles[i][side + 1];
          triangles[i][side + 1] = buffer;
        }
      }
    }
  }

  for(int i = 0; i < numTriangles; i++)
  {
    testIfTriangle(i + 1, triangles[i]);
  }

  return 0;
}

