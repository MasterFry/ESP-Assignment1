//-----------------------------------------------------------------------------
// ass1.c
//
// < TODO Explanation of the program ...>
// <... May have multiple lines.>
//
// Group: Group 2, study assistant Florian Hager
//
// Authors:
// Stefan Fragner 11703708
// Tobias Topar 11710538
//-----------------------------------------------------------------------------
//

/** TODO Änderungen
 * hab die functionen ein bisschen umsortiert und auch die main funktion an den
 * Anfang gestellt. Dadurch muss man dann auch die anderen funktionen vorwärts
 * deklarieren (line 33 - 43).
 */


#include <stdio.h>
#include <float.h>
#include <math.h>
#include <limits.h>


// define the number of sides of a triangle
#define TRIANGLE_SIDES 3


// This function clears the remaining characters in the input buffer
int clearInput();

// This function is used to retrieve the number of triangles to read
int getNumTriangles();

// This function is used to read the value of one side of a single triangle
float getTriangleSide(char* textNumber);

// This function is used to test whether the given sides can form a triangle
// or not and if it is a special triangle
void testIfTriangle(int index, float triangle[TRIANGLE_SIDES]);


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


//-----------------------------------------------------------------------------
///
/// This function asks the user to enter the value for a single side of a
/// triangle and checks if the input is valid.
/// In addition it immediately returns 0 if EOF has been reached.
///
/// @param textNumber the number of the side written out as a text
///        (e.g. 1 = "first")
///
/// @return the length of a single side of the triangle
///         returns 0 if EOF has been reached
//
float getTriangleSide(char* textNumber)
{
  int result, clearedCharacters;
  float triangleSide; // TODO hab mir das nochmal genauer angeschaut wie das mit FLT_MAX und float so is.
  // Wenn du einen float wert hast der FLT_MAX überschreitet bekommt er einfach den wert "inf" was keine
  // Zahl ist sonder ein error mehr oder weniger. Wenn man "inf" > FLT_MAX vergleicht gibt das den wert 1
  // also wahr zurück. Deswegen kann man auch einfach float dafür verwenden und braucht keinen double

  // This loop will run until the user has entered a valid side length or the
  // user has stopped the program (e.g. by pressing Ctrl+D)
  while(1)
  {
    printf("Please enter the %s number of the triplet: ", textNumber);

    result = scanf("%f", &triangleSide);

    // clear the characters in the input after the entered value
    clearedCharacters = clearInput();

    // if one of these conditions is true, EOF has been reached
    if (result < 0 || clearedCharacters == 0)
    {
      return 0;
    }

    // Check if the user has entered a valid side length
    if (clearedCharacters == 1 && result == 1 && triangleSide > 0.0 &&
        triangleSide <= FLT_MAX)
    {
      return triangleSide;
    }

    printf("[ERR] Invalid number for the triplet.\n");
  }

}


//-----------------------------------------------------------------------------
///
/// This Function tests if the three given sides can form a triangle.
/// The sides must be sorted in ascending order before calling this function.
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

