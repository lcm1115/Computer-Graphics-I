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

typedef struct edge {
  int ymax, x, dx, dy, sum;
} Edge;

bool compareEdge(Edge* a, Edge* b) {
  if (a->x == b->x) {
    if (a->dy == 0) {
      return -1;
    } else if (b->dy == 0) {
      return 1;
    }
    return (a->dx / a->dy) < (b->dx / b->dy);
  }
  return a->x < b->x;
}

void updateEdge(Edge* edge) {
  edge->sum += edge->dx;
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
  for (int i = 0; i < n ; ++i) {
    int var1 = i;
    int var2 = (i + 1) % n;
    if (var1 > var2) {
      swap(var1, var2);
    }
    Edge* newEdge = new Edge;
    newEdge->sum = 0;
    if (v[var1].y > v[var2].y) {
      ET[v[var2].y].push_back(newEdge);
      newEdge->ymax = v[var1].y;
      newEdge->x = v[var2].x;
    } else if (v[var1].y < v[var2].y) {
      ET[v[var1].y].push_back(newEdge);
      newEdge->ymax = v[var2].y;
      newEdge->x = v[var1].x;
    } else {
      ET[v[var1].y].push_back(newEdge);
      newEdge->ymax = v[var2].y;
      newEdge->x = min(v[var1].x, v[var2].x);
    }
    if (v[var1].x > v[var2].x) {
      newEdge->dx = v[var1].x - v[var2].x;
      newEdge->dy = v[var1].y - v[var2].y;
    } else {
      newEdge->dx = v[var2].x - v[var1].x;
      newEdge->dy = v[var2].y - v[var1].y;
    }
    ymax = max(ymax, newEdge->ymax);
  }
  vector<Edge*> AET;
  map<int, vector<Edge*> >::iterator it = ET.begin();
  int y = it->first;
  while (!ET.empty() || y <= ymax) {
    for (vector<Edge*>::iterator it2 = AET.begin(); it2 != AET.end(); ) {
      if ((*it2)->ymax == y) {
        delete *it2;
        it2 = AET.erase(it2);
      } else {
        ++it2;
      }
    }
    if (it != ET.end() && it->first == y) {
      AET.insert(AET.end(), it->second.begin(), it->second.end());
      ET.erase(it);
      ++it;
    }
    sort(AET.begin(), AET.end(), compareEdge);
    for (int i = 0; i < AET.size(); i += 2) {
      Edge* e1 = AET.at(i);
      Edge* e2;
      if (i < AET.size() - 1) {
        e2 = AET.at(i + 1);
      }
      if (e1->dy == 0) {
        for (int j = 0; j <= e1->dx; ++j) {
          setPixel(e1->x + j, y);
        }
        AET.erase(AET.begin() + i);
        i -= 2;
        continue;
      }
      if (e2->dy == 0) {
        for (int j = 0; j <= e2->dx; ++j) {
          setPixel(e2->x + j, y);
        }
        AET.erase(AET.begin() + i + 1);
        i -= 2;
        continue;
      }
      for (int x = e1->x; x <= e2->x; ++x) {
        setPixel(x, y);
      }
      updateEdge(e1);
      updateEdge(e2);
    }
    ++y;
  }
}
