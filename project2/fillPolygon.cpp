/*
** File:	fillPolygon.cpp
** Author:	Liam Morris - lcm1115
** Template by:	Warren R. Carithers
*/

#include <algorithm>
#include <fillPolygon.h>
#include <iostream>
#include <map>
#include <math.h>
#include <string.h>
#include <vector>

/*
** fillPolygon
**
** Draw a filled polygon using the scan-line-based polygon fill algorithm
** discussed in class. The polygon has n distinct vertices.
*/

using namespace std;

// Representation of an edge.
typedef struct edge {
  int ymax, x, dx, dy, sum;
} Edge;

// Compares two edges for equality.
// Return:
//  -1 if a < b
//   0 if a == b
//   1 if a > b
bool compareEdge(Edge* a, Edge* b) {
  // If the edges share a common x value, special considerations need to be
  // made.
  if (a->x == b->x) {
    return (a->dx / a->dy) < (b->dx / b->dy);
  }
  return a->x < b->x;
}

// Updates edges as needed after each scan line.
void updateEdge(Edge* edge) {
  // Increment sum.
  edge->sum += edge->dx;

  // If sum exceeds dy, adjust x accordingly.
  while (edge->dy != 0 && edge->sum >= abs(edge->dy)) {
    edge->sum -= abs(edge->dy);
    if (edge->dy < 0) {
      edge->x--;
    } else {
      edge->x++;
    }
  }
}

void fillPolygon( GLint n, Vertex v[] ) {
  map<int, vector<Edge*> > ET;
  int ymax = 0;
  // Generate edge table.
  for (int i = 0; i < n ; ++i) {
    // Collect two points from Vertex list.
    int var1 = i;
    int var2 = (i + 1) % n;
    // Swap indices if wrapping around the end of the table.
    if (var1 > var2) {
      swap(var1, var2);
    }
    Edge* newEdge = new Edge;
    newEdge->sum = 0;
    // Generate edge according to (y, x) points.

    // ymax should be the greater of the y values.
    // If y values are equal, make the lesser of the x values the x value.
    if (v[var1].y > v[var2].y) {
      ET[v[var2].y].push_back(newEdge);
      newEdge->ymax = v[var1].y;
      newEdge->x = v[var2].x;
    } else if (v[var1].y < v[var2].y) {
      ET[v[var1].y].push_back(newEdge);
      newEdge->ymax = v[var2].y;
      newEdge->x = v[var1].x;
    } else {
      delete newEdge;
      continue;
    }

    // Assign dx and dy values.
    if (v[var1].x > v[var2].x) {
      newEdge->dx = v[var1].x - v[var2].x;
      newEdge->dy = v[var1].y - v[var2].y;
    } else {
      newEdge->dx = v[var2].x - v[var1].x;
      newEdge->dy = v[var2].y - v[var1].y;
    }
    ymax = max(ymax, newEdge->ymax);
  }

  // Begin grabbing edges and drawing pixels.
  vector<Edge*> AET;
  map<int, vector<Edge*> >::iterator it = ET.begin();
  int y = it->first;
  // Iterate while edges exist or y is less than ymax
  while (!ET.empty() || y <= ymax) {
    // Remove all edges whose ymax is equal to the current scanline.
    for (vector<Edge*>::iterator it2 = AET.begin(); it2 != AET.end(); ) {
      if ((*it2)->ymax == y) {
        delete *it2;
        it2 = AET.erase(it2);
      } else {
        ++it2;
      }
    }
    // If edges exist and they start at the current scanline, add them to the
    // active edge table.
    if (it != ET.end() && it->first == y) {
      AET.insert(AET.end(), it->second.begin(), it->second.end());
      ET.erase(it);
      ++it;
    }
    // Sort the active edge table.
    sort(AET.begin(), AET.end(), compareEdge);

    // For all edges in the active edge table, draw the pixels.
    for (int i = 0; i < AET.size(); i += 2) {
      Edge* e1 = AET.at(i);
      Edge* e2 = AET.at(i + 1);
      // Draw all pixels between the edges.
      for (int x = e1->x; x <= e2->x; ++x) {
        setPixel(x, y);
      }
      updateEdge(e1);
      updateEdge(e2);
    }
    ++y;
  }
}
