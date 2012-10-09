/*
** File:	clipPolygon.cpp
** Author:	Liam Morris - lcm1115
** Template by:	Warren R. Carithers
*/

#include <clipPolygon.h>
#include <iostream>
#include <vector>

using namespace std;

/*
** clipPolygon
**
** Clip a polygon using the Sutherland-Hodgman Polygon Clipping algorithm
** discussed in class and in the text. The polygon is specified with vertex
** count in and vertices inv; the clipping region is rectangular, and has
** lower-left corner ll and upper-right corner ur. The resulting vertices
** are placed in outv, with the vertex count returned as the function's
** result.
*/


// Given a vertex and a pair of coordinates for an edge, determine if the vertex
// is inside the clipping window/edge.
bool inside(const Vertex &v, int x0, int y0, int x1, int y1) {
  // Top edge
  if (y0 == y1 && x0 > x1) {
    return v.y <= y0;
  }
  // Bottom edge
   else if (y0 == y1 && x0 < x1) {
    return v.y >= y0;
  }
  // Left edge
   else if (x0 == x1 && y0 > y1) {
    return v.x >= x0;
  }
  // Right edge
   else if (x0 == x1 && y0 < y1) {
    return v.x <= x0;
  }
}

// Given two vertices and a clipping edge, find the intersection of the line
// segment between the two vertices and the clipping edge.
Vertex intersect(Vertex v, Vertex w, int x0, int y0, int x1, int y1) {
  Vertex newEdge;
  double m = static_cast<double>(v.y - w.y) / (v.x - w.x);
  int b = v.y - m * v.x;

  if (y0 == y1) {
    // Add special case for testing horizontal edges but vertices share x
    // coordinate (therefore division by zero is posible)
    if (v.x == w.x) {
      newEdge.x = v.x;
    } else {
      newEdge.x = (y0 - b) / m;
    }
    newEdge.y = y0;
  } else if (x0 == x1) {
    newEdge.x = x0;
    newEdge.y = m * x0 + b;
  }

  return newEdge;
}

// Clip the set of vertices against one edge of the clipping window
int SHPC(Vertex outv[], const Vertex inv[], int in,
          int x0, int y0, int x1, int y1) {
  int outLength = 0;
  Vertex p = inv[in - 1];
  for (int i = 0; i < in; ++i) {
    Vertex s = inv[i];

    if (inside(s, x0, y0, x1, y1)) {
      if (inside(p, x0, y0, x1, y1)) {
        outv[outLength] = s;
        ++outLength;
      } else {
        Vertex i = intersect(s, p, x0, y0, x1, y1);
        outv[outLength] = i;
        ++outLength;
        outv[outLength] = s;
        ++outLength;
      }
    } else {
      if (inside(p, x0, y0, x1, y1)) {
        Vertex i = intersect(s, p, x0, y0, x1, y1);
        outv[outLength] = i;
        ++outLength;
      }
    }
    p = s;
  }

  return outLength;
}

// Copy vertices from one array to another
void copyvertices(Vertex dest[], Vertex source[], int n) {
  for (int i = 0; i < n; ++i) {
    dest[i] = source[i];
  }
}

GLint clipPolygon( GLint in, const Vertex inv[], Vertex outv[],
		  Vertex ll, Vertex ur ) {
  int outLength = 0;

  Vertex v[50];

  // Clip top edge
  outLength = SHPC(outv, inv, in, ur.x, ur.y, ll.x, ur.y);
  copyvertices(v, outv, outLength);

  // Clip left edge
  outLength = SHPC(outv, v, outLength, ll.x, ur.y, ll.x, ll.y);
  copyvertices(v, outv, outLength);

  // Clip bottom edge
  outLength = SHPC(outv, v, outLength, ll.x, ll.y, ur.x, ll.y);
  copyvertices(v, outv, outLength);

  // Clip right edge
  outLength = SHPC(outv, v, outLength, ur.x, ll.y, ur.x, ur.y);

  return outLength;
}

