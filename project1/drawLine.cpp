/* 
** File:	drawLine.cpp
** Author:	Liam Morris - lcm1115
** Template by:	Warren R. Carithers
*/

#include <drawLine.h>

/*
** drawLine
**
** Draw a line from vertex (x0,y0) to vertex (x1,y1) using
** the midpoint line algorithm (as discussed in class).
*/

// Swaps the values of two GLints
void swap(GLint &a, GLint &b) {
  a ^= b;
  b ^= a;
  a ^= b;
}

// Draws a line from (x0, y0) to (x1, y1) using the Bresenham line algorithm.
void drawLine( GLint x0, GLint y0, GLint x1, GLint y1 ) {
  // Calculate dx and dy to determine slope.
  int dx = abs(x1 - x0);
  int dy = abs(y1 - y0);

  // If slope > 1, reflect across y=x axis.
  bool isSteep = dy > dx;
  if (isSteep) {
    swap(x0, y0);
    swap(x1, y1);
  }

  // If drawing right to left, swap points.
  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }

  // Get new dx and dy values in case things were moved around.
  dx = x1 - x0;
  dy = abs(y1 - y0);

  // Still using dE and dNE since inapplicable values will be reflected or
  // values have already been swapped to make them valid.
  int dE = 2 * dy;
  int dNE = 2 * (dy - dx);

  // Initial d value.
  int d = dE - dx;

  // Determine if y is increasing or decreasing.
  int ychange = y0 < y1 ? 1 : -1;

  for (int x = x0, y = y0; x <= x1; ++x) {
    // If slope > 1, draw pixel at swapped (x, y) position (reflection across
    // y=x).
    if (isSteep) {
      setPixel(y, x);
    } else {
      setPixel(x, y);
    }
    if (d <= 0) { // If we chose E, increment d by dE.
      d += dE;
    } else { // Otherwise increment d by dNE and [in/de]crement y.
      y += ychange;
      d += dNE;
    }
  }
}
