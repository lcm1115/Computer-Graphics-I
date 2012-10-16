/**
 * shapes.cpp
 *
 * Routines for tessellating a number of basic shapes
 *
 * Students are to supply their implementations for the
 * functions in this file using the function "addTriangle()" to do the
 * tessellation.
 *
 */

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/glew.h>
#include <GL/gl.h>
#endif

#include "simpleShape.h"
#include "cg1Shape.h"
#include <math.h>
#include <vector>

using namespace std;

#define DEGREE_RADIAN_FACTOR .0174532925


/**
 * makeCube - Create a unit cube, centered at the origin, with a given number
 * of subdivisions in each direction on each face.
 *
 * @param subdivision - number of equal subdivisons to be made in each
 *        direction along each face
 *
 * Can only use calls to addTriangle()
 */
void makeCube (int subdivisions) {
  double curx, cury, curz;

  cury = -.25;
  curz = .25;
  // Axis 1
  for (int i = 0; i < subdivisions; ++i) {
    curx = -.25;
    for (int j = 0; j < subdivisions; ++j) {
      // Front
      Point3 p1(curx, cury, curz);
      Point3 p2(curx, cury + .5 / subdivisions, curz);
      Point3 p3(curx + .5 / subdivisions, cury, curz);
      addTriangle(p1, p2, p3);

      p1 = p2;
      p2.x = curx + .5 / subdivisions; p2.y = cury + .5 / subdivisions;
      addTriangle(p1, p2, p3);

      // Back
      p1.x = curx; p1.y = cury; p1.z = -curz;
      p2.x = curx; p2.y = cury + .5 / subdivisions; p2.z = -curz;
      p3.x = curx + .5 / subdivisions; p3.y = cury; p3.z = -curz;
      addTriangle(p3, p2, p1);

      p1 = p2; p1.z = -curz;
      p2.x = curx + .5 / subdivisions; p2.y = cury + .5 / subdivisions; p2.z = -curz;
      p3.z = -curz;
      addTriangle(p3, p2, p1);
      curx += .5 / subdivisions;
    }
    cury += .5 / subdivisions;
  }

  // Axis 2
  cury = -.25;
  curz = .25;
  for (int i = 0; i < subdivisions; ++i) {
    curx = -.25;
    for (int j = 0; j < subdivisions; ++j) {
      // Front
      Point3 p1(curx, curz, cury);
      Point3 p2(curx, curz, cury + .5 / subdivisions);
      Point3 p3(curx + .5 / subdivisions, curz, cury);
      addTriangle(p3, p2, p1);

      p1 = p2;
      p2.x = curx + .5 / subdivisions; p2.z = cury + .5 / subdivisions;
      addTriangle(p3, p2, p1);

      // Back
      p1.x = curx; p1.y = -curz; p1.z = cury;
      p2.x = curx; p2.y = -curz; p2.z = cury + .5 / subdivisions;
      p3.x = curx + .5 / subdivisions; p3.y = -curz; p3.z = cury;
      addTriangle(p1, p2, p3);

      p1 = p2; p1.y = -curz;
      p2.x = curx + .5 / subdivisions; p2.z = cury + .5 / subdivisions; p2.y = -curz;
      p3.y = -curz;
      addTriangle(p1, p2, p3);
      curx += .5 / subdivisions;
    }
    cury += .5 / subdivisions;
  }

  // Axis 3
  cury = -.25;
  curz = .25;
  for (int i = 0; i < subdivisions; ++i) {
    curx = -.25;
    for (int j = 0; j < subdivisions; ++j) {
      // Front
      Point3 p1(curz, cury, curx);
      Point3 p2(curz, cury + .5 / subdivisions, curx);
      Point3 p3(curz, cury, curx + .5 / subdivisions);
      addTriangle(p3, p2, p1);

      p1 = p2;
      p2.z = curx + .5 / subdivisions; p2.y = cury + .5 / subdivisions;
      addTriangle(p3, p2, p1);

      // Back
      p1.z = curx; p1.y = cury; p1.x = -curz;
      p2.z = curx; p2.y = cury + .5 / subdivisions; p2.x = -curz;
      p3.z = curx + .5 / subdivisions; p3.y = cury; p3.x = -curz;
      addTriangle(p1, p2, p3);

      p1 = p2; p1.x = -curz;
      p2.z = curx + .5 / subdivisions; p2.y = cury + .5 / subdivisions; p2.x = -curz;
      p3.x = -curz;
      addTriangle(p1, p2, p3);
      curx += .5 / subdivisions;
    }
    cury += .5 / subdivisions;
  }
}


/**
 * makeCylinder - Create polygons for a cylinder with unit height, centered at
 * the origin, with separate number of radial subdivisions and height
 * subdivisions.
 *
 * @param radius - Radius of the base of the cylinder
 * @param radialDivision - number of subdivisions on the radial base
 * @param heightDivisions - number of subdivisions along the height
 *
 * Can only use calls to addTriangle()
 */
void makeCylinder (float radius, int radialDivisions, int heightDivisions) {
  vector<Point3> circumference;

  double angle = 360 / radialDivisions;

  for (double i = 0; i < 360; i += angle) {
    double curx, cury, curz;
    curz = -.25;
    

  }
}


/**
 * makeCone - Create polygons for a cone with unit height, centered at the
 * origin, with separate number of radial subdivisions and height
 * subdivisions.
 *
 * @param radius - Radius of the base of the cone
 * @param radialDivision - number of subdivisions on the radial base
 * @param heightDivisions - number of subdivisions along the height
 *
 * Can only use calls to addTriangle()
 */
void makeCone (float radius, int radialDivisions, int heightDivisions) {
}


/**
 * makeSphere - Create sphere of a given radius, centered at the origin,
 * with the specified number of subdivisions.
 *
 * @param radius - Radius of the sphere
 * @param subdivisions - number of subdivisions
 *
 * Can only use calls to addTriangle()
 */
void makeSphere (float radius, int subdivisions) {
}
