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

bool inside(const Vertex &v, const Vertex &ll, const Vertex &ur) {
  return v.x >= ll.x && v.x <= ur.x &&
         v.y >= ll.y && v.y <= ur.y;
}

Vertex intersect(Vertex v,
                 Vertex w,
                 Vertex ll,
                 Vertex ur) {
  Vertex newEdge;
  double m = static_cast<double>(v.y - w.y) / (v.x - w.x);
  int b = v.y - m * v.x;
  // Left edge
  if (max(v.x, w.x) > ll.x && min(v.x, w.x) < ll.x) {
    cout << "LEFT EDGE" << endl;
    newEdge.x = ll.x;
    newEdge.y = m * ll.x + b;
  }
  // Right edge
  else if (max(v.x, w.x) > ur.x && min(v.x, w.x) < ur.x) {
    cout << "RIGHT EDGE" << endl;
    newEdge.x = ur.x;
    newEdge.y = m * ur.x + b;
  }
  // Bottom edge
  else if (min(v.y, w.y) < ll.y && max(v.y, w.y) > ll.y) {
    cout << "BOTTOM EDGE" << endl;
    newEdge.x = (ll.y - b) / m;
    newEdge.y = ll.y;
  }
  // Top edge
  else if (min(v.y, w.y) < ur.y && max(v.y, w.y) > ll.y) {
    cout << "TOP EDGE" << endl;
    newEdge.x = (ur.y - b) / m;
    newEdge.y = ur.y;
  }
  cout << "newEdge: (" << newEdge.x << ", " << newEdge.y << ")" << endl;
  return newEdge;
}

GLint clipPolygon( GLint in, const Vertex inv[], Vertex outv[],
		  Vertex ll, Vertex ur ) {
  int outLength = 0;
  Vertex p = inv[in - 1];

  for (int i = 0; i < in; ++i) {
    Vertex s = inv[i];

    if (inside(s, ll, ur)) {
      if (inside(p, ll, ur)) {
        outv[outLength] = s;
        ++outLength;
      } else {
        Vertex i = intersect(s, p, ll, ur);
        outv[outLength] = i;
        ++outLength;
        outv[outLength] = s;
        ++outLength;
      }
    } else {
      if (inside(p, ll, ur)) {
        Vertex i = intersect(s, p, ll, ur);
        outv[outLength] = i;
        ++outLength;
      } else {
        if (p.x <= ll.x) {
          outv[outLength].x = ll.x;
        } else if (p.x >= ur.x) {
          outv[outLength].x = ur.x;
        } else {
          outv[outLength].x = p.x;
        }
        if (p.y <= ll.y) {
          outv[outLength].y = ll.y;
        } else if (p.y >= ur.y) {
          outv[outLength].y = ur.y;
        } else {
          outv[outLength].y = p.y;
        }
        ++outLength;
        if (s.x <= ll.x) {
          outv[outLength].x = ll.x;
        } else if (s.x >= ur.x) {
          outv[outLength].x = ur.x;
        } else {
          outv[outLength].x = s.x;
        }
        if (s.y <= ll.y) {
          outv[outLength].y = ll.y;
        } else if (s.y >= ur.y) {
          outv[outLength].y = ur.y;
        } else {
          outv[outLength].y = s.y;
        }
        ++outLength;
      }
    }

    p = s;
  }

  for (int i = 0; i < outLength; ++i) {
    cout << "Vertex " << i << ": ("
         << outv[i].x << ", " << outv[i].y << ")" << endl;
  }
  return outLength;
}

