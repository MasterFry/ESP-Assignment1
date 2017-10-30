//-----------------------------------------------------------------------------
// ass1.c
//
// The user can input a number of triangles he wants to get checked
// then the user can input the length of every side of every triangle
// the program now tells the user if each triangle is a triangle or not and
// if it is a triangle it can tell you if it is an equilateral, isosceles
// and/or a right triangle.
// The program handles invalid inputs and asks the user to correct is.
//
// Group: Group 2, study assistant Florian Hager
//
// Authors:
// Stefan Fragner 11703708
// Tobias Topar 11710538
//-----------------------------------------------------------------------------
//
//test

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


// This is the main function of the program, it combines all subfunctions
int main() {

  // an array to write out 1st 2nd and 3rd
  char* textNumber[TRIANGLE_SIDES] = {"first","second","third"};

  // a variable containing the number of triangles to process,
  // after gerNumTriangles() was successful
  int numTriangles = getNumTriangles();

  // EOF used to terminate the program
  if (numTriangles == 0)
  {
    return 0;
  }

  // this 2D array contains 3 (TRIANGLE_SIDES) variables for a length value
  // per triangle the program wants to process
  float triangles[numTriangles][TRIANGLE_SIDES];

  // goes through every triangle
  for(int i = 0; i < numTriangles;  i++)
  {
    // goes through every side of every triangle
    // and saves the value for the length of each side of each triangle
    for (int side = 0; side < TRIANGLE_SIDES; side++)
    {
      triangles[i][side] = getTriangleSide(textNumber[side]);
    }
  }

  // a buffer to swap the values of two variables
  float buffer;

  // goes through every triangle
  for(int i = 0; i < numTriangles; i++)
  {
    // run through the array for each triangle side
    // compare two sides, swap them if the first is greater then the second
    // repeat the process until the sides of the triangle are sorted
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

  // goes through every triangle (testIfTriangle outputs the results
  // (i+1) to output the correct number of the triangle
  // starting from 1 instead of 0
  for(int i = 0; i < numTriangles; i++)
  {
    testIfTriangle(i + 1, triangles[i]);
  }

  return 0;
}


//-----------------------------------------------------------------------------
///
/// This function reads in all the remaining characters after the last input
///
/// @return the count of characters (including '\n', excluding ' ') that have
///         been red, returns 0 if EOF has been reached.
//
int clearInput()
{
  char c;
  int counter = 0;

  do
  {
    // Check if EOF has been reached or not
    if(scanf("%c", &c) < 0)
    {
      return 0;
    }

    // Check if the character is a space character, increment counter if not
    if(c != ' ')
    {
      ++counter;
    }

    // repeat until the new line character has been red
  } while(c != '\n');

  return counter;
}


//-----------------------------------------------------------------------------
///
/// This function asks the user to input a number of triangles to process
/// and makes sure the user enters something the program can work with
///
/// @return the number of triangles to process
//
int getNumTriangles()
{
  int result, clearedCharacters, numTriangles;

  // until a correct input is made the program stays here
  while(1)
  {
    printf("Please enter the number of triangles to check: ");

    // reads the return of scanf, to know if it matches the criteria
    result = scanf("%i", &numTriangles);
    clearedCharacters = clearInput();

    // used to terminate the Program
    if (result < 0 || clearedCharacters == 0)
    {
      return 0;
    }

    // if the input is valid the function returns the input
    if (clearedCharacters == 1 && result == 1 && numTriangles >= 1 &&
        numTriangles <= UCHAR_MAX)
    {
      return numTriangles;
    }

    // if the input cant be processed
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
  float triangleSide;

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

