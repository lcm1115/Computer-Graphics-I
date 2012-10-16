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

  cury = -0.5;
  curz = 0.5;
  // Axis 1
  for (int i = 0; i < subdivisions; ++i) {
    curx = -0.5;
    for (int j = 0; j < subdivisions; ++j) {
      // Front
      Point3 p1(curx, cury, curz);
      Point3 p2(curx, cury + 1.0 / subdivisions, curz);
      Point3 p3(curx + 1.0 / subdivisions, cury, curz);
      addTriangle(p1, p2, p3);

      p1 = p2;
      p2.x = curx + 1.0 / subdivisions; p2.y = cury + 1.0 / subdivisions;
      addTriangle(p1, p2, p3);

      // Back
      p1.x = curx; p1.y = cury; p1.z = -curz;
      p2.x = curx; p2.y = cury + 1.0 / subdivisions; p2.z = -curz;
      p3.x = curx + 1.0 / subdivisions; p3.y = cury; p3.z = -curz;
      addTriangle(p3, p2, p1);

      p1 = p2; p1.z = -curz;
      p2.x = curx + 1.0 / subdivisions; p2.y = cury + 1.0 / subdivisions; p2.z = -curz;
      p3.z = -curz;
      addTriangle(p3, p2, p1);
      curx += 1.0 / subdivisions;
    }
    cury += 1.0 / subdivisions;
  }

  // Axis 2
  cury = -0.5;
  curz = 0.5;
  for (int i = 0; i < subdivisions; ++i) {
    curx = -0.5;
    for (int j = 0; j < subdivisions; ++j) {
      // Front
      Point3 p1(curx, curz, cury);
      Point3 p2(curx, curz, cury + 1.0 / subdivisions);
      Point3 p3(curx + 1.0 / subdivisions, curz, cury);
      addTriangle(p3, p2, p1);

      p1 = p2;
      p2.x = curx + 1.0 / subdivisions; p2.z = cury + 1.0 / subdivisions;
      addTriangle(p3, p2, p1);

      // Back
      p1.x = curx; p1.y = -curz; p1.z = cury;
      p2.x = curx; p2.y = -curz; p2.z = cury + 1.0 / subdivisions;
      p3.x = curx + 1.0 / subdivisions; p3.y = -curz; p3.z = cury;
      addTriangle(p1, p2, p3);

      p1 = p2; p1.y = -curz;
      p2.x = curx + 1.0 / subdivisions; p2.z = cury + 1.0 / subdivisions; p2.y = -curz;
      p3.y = -curz;
      addTriangle(p1, p2, p3);
      curx += 1.0 / subdivisions;
    }
    cury += 1.0 / subdivisions;
  }

  // Axis 3
  cury = -0.5;
  curz = 0.5;
  for (int i = 0; i < subdivisions; ++i) {
    curx = -0.5;
    for (int j = 0; j < subdivisions; ++j) {
      // Front
      Point3 p1(curz, cury, curx);
      Point3 p2(curz, cury + 1.0 / subdivisions, curx);
      Point3 p3(curz, cury, curx + 1.0 / subdivisions);
      addTriangle(p3, p2, p1);

      p1 = p2;
      p2.z = curx + 1.0 / subdivisions; p2.y = cury + 1.0 / subdivisions;
      addTriangle(p3, p2, p1);

      // Back
      p1.z = curx; p1.y = cury; p1.x = -curz;
      p2.z = curx; p2.y = cury + 1.0 / subdivisions; p2.x = -curz;
      p3.z = curx + 1.0 / subdivisions; p3.y = cury; p3.x = -curz;
      addTriangle(p1, p2, p3);

      p1 = p2; p1.x = -curz;
      p2.z = curx + 1.0 / subdivisions; p2.y = cury + 1.0 / subdivisions; p2.x = -curz;
      p3.x = -curz;
      addTriangle(p1, p2, p3);
      curx += 1.0 / subdivisions;
    }
    cury += 1.0 / subdivisions;
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
  if (radialDivisions < 3) {
    radialDivisions = 3;
  }

  vector<Point3> circbot;
  vector<Point3> circtop;

  Point3 base(0, 0, -0.5);
  Point3 top(0, 0, 0.5);
  double angle = 360 / radialDivisions;
  
  for (double i = 0; i < 360; i += angle) {
    double curx = radius * cos(i * DEGREE_RADIAN_FACTOR);
    double cury = radius * sin(i * DEGREE_RADIAN_FACTOR);
    circbot.push_back(Point3(curx, cury, -0.5));
    circtop.push_back(Point3(curx, cury, 0.5));
  }

  // Base circles
  for (int i = 0; i < circbot.size(); ++i) {
    Point3 p1 = circbot.at(i);
    Point3 p2 = circbot.at((i + 1) % circbot.size());
    addTriangle(p1, p2, base);
    
    p1 = circtop.at(i);
    p2 = circtop.at((i + 1) % circtop.size());
    addTriangle(p2, p1, top);
    // Sides
    double zstep = 1.0 / heightDivisions;
    for (int j = 0; j < heightDivisions; ++j) {
      Point3 p3 = p1;
      p3.z -= zstep;

      addTriangle(p1, p2, p3);

      Point3 p4 = p2;
      p4.z -= zstep;
      
      addTriangle(p3, p2, p4);

      p1.z -= zstep;
      p2.z -= zstep;
    }
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
  if (radialDivisions < 3) {
    radialDivisions = 3;
  }

  vector<Point3> circbot;

  Point3 base(0, 0, -0.5);
  Point3 top(0, 0, 0.5);
  double angle = 360 / radialDivisions;
  
  for (double i = 0; i < 360; i += angle) {
    double curx = radius * cos(i * DEGREE_RADIAN_FACTOR);
    double cury = radius * sin(i * DEGREE_RADIAN_FACTOR);
    circbot.push_back(Point3(curx, cury, -0.5));
  }

  // Base circles
  for (int i = 0; i < circbot.size(); ++i) {
    Point3 p1 = circbot.at(i);
    Point3 p2 = circbot.at((i + 1) % circbot.size());
    addTriangle(p2, p1, base);
    
    // Sides
    double zstep = 1.0 / heightDivisions;
    double rstep = radius / heightDivisions;
    double rad = radius;
    Point3 p1old(p1);
    Point3 p2old(p2);
    for (int j = 0; j < heightDivisions; ++j) {
      rad -= rstep;

      Point3 p3;
      p3.x = rad / radius * p1old.x;
      p3.y = rad / radius * p1old.y;
      p3.z = p1.z + zstep;

      addTriangle(p1, p2, p3);

      Point3 p4;
      p4.x = rad / radius * p2old.x;
      p4.y = rad / radius * p2old.y;
      p4.z = p2.z + zstep;
      
      addTriangle(p3, p2, p4);

      p1 = p3;
      p2 = p4;
    }
    addTriangle(p1, p2, top);
  }
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
  if (subdivisions > 5) {
    subdivisions = 5;
  }

  double a = 2.0 / (1.0 + sqrt(5.0))

  // Base icosahedron
  Point3 origin(0, 0, 0);
  Point3 p0(0, a, -1);
  Point3 p1(-a, 1, 0);
  Point3 p2(a, 1, 0);
  Point3 p3(0, a, 1);
  Point3 p4(-1, 0, a);
  Point3 p5(0, -a, 1);
  Point3 p6(1, 0, a);
  Point3 p7(1, 0, -a);
  Point3 p8(0, -a, -1);
  Point3 p9(-1, 0, -a);
  Point3 p10(-a, -1, 0);
  Point3 p11(a, -1, 0);

  
}
