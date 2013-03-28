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
      // Add triangle 1
      Point3 p1(curx, cury, curz);
      Point3 p2(curx, cury + 1.0 / subdivisions, curz);
      Point3 p3(curx + 1.0 / subdivisions, cury, curz);
      addTriangle(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, p3.x, p3.y, p3.z);

      // Add triangle 2
      p1 = p2;
      p2.x = curx + 1.0 / subdivisions; p2.y = cury + 1.0 / subdivisions;
      addTriangle(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, p3.x, p3.y, p3.z);

      // Back
      // Add triangle 1
      p1.x = curx; p1.y = cury; p1.z = -curz;
      p2.x = curx; p2.y = cury + 1.0 / subdivisions; p2.z = -curz;
      p3.x = curx + 1.0 / subdivisions; p3.y = cury; p3.z = -curz;
      addTriangle(p3.x, p3.y, p3.z, p2.x, p2.y, p2.z, p1.x, p1.y, p1.z);

      // Add triangle 2
      p1 = p2; p1.z = -curz;
      p2.x = curx + 1.0 / subdivisions; p2.y = cury + 1.0 / subdivisions; p2.z = -curz;
      p3.z = -curz;
      addTriangle(p3.x, p3.y, p3.z, p2.x, p2.y, p2.z, p1.x, p1.y, p1.z);
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
      // Add triangle 1
      Point3 p1(curx, curz, cury);
      Point3 p2(curx, curz, cury + 1.0 / subdivisions);
      Point3 p3(curx + 1.0 / subdivisions, curz, cury);
      addTriangle(p3.x, p3.y, p3.z, p2.x, p2.y, p2.z, p1.x, p1.y, p1.z);

      // Add triangle 2
      p1 = p2;
      p2.x = curx + 1.0 / subdivisions; p2.z = cury + 1.0 / subdivisions;
      addTriangle(p3.x, p3.y, p3.z, p2.x, p2.y, p2.z, p1.x, p1.y, p1.z);

      // Back
      // Add triangle 1
      p1.x = curx; p1.y = -curz; p1.z = cury;
      p2.x = curx; p2.y = -curz; p2.z = cury + 1.0 / subdivisions;
      p3.x = curx + 1.0 / subdivisions; p3.y = -curz; p3.z = cury;
      addTriangle(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, p3.x, p3.y, p3.z);

      // Add triangle 2
      p1 = p2; p1.y = -curz;
      p2.x = curx + 1.0 / subdivisions; p2.z = cury + 1.0 / subdivisions; p2.y = -curz;
      p3.y = -curz;
      addTriangle(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, p3.x, p3.y, p3.z);
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
      // Add triangle 1
      Point3 p1(curz, cury, curx);
      Point3 p2(curz, cury + 1.0 / subdivisions, curx);
      Point3 p3(curz, cury, curx + 1.0 / subdivisions);
      addTriangle(p3.x, p3.y, p3.z, p2.x, p2.y, p2.z, p1.x, p1.y, p1.z);

      // Add triangle 2
      p1 = p2;
      p2.z = curx + 1.0 / subdivisions; p2.y = cury + 1.0 / subdivisions;
      addTriangle(p3.x, p3.y, p3.z, p2.x, p2.y, p2.z, p1.x, p1.y, p1.z);

      // Back
      // Add triangle 1
      p1.z = curx; p1.y = cury; p1.x = -curz;
      p2.z = curx; p2.y = cury + 1.0 / subdivisions; p2.x = -curz;
      p3.z = curx + 1.0 / subdivisions; p3.y = cury; p3.x = -curz;
      addTriangle(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, p3.x, p3.y, p3.z);

      // Add triangle 2
      p1 = p2; p1.x = -curz;
      p2.z = curx + 1.0 / subdivisions; p2.y = cury + 1.0 / subdivisions; p2.x = -curz;
      p3.x = -curz;
      addTriangle(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, p3.x, p3.y, p3.z);
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

  Point3 base(0, -0.5, 0);
  Point3 top(0, 0.5, 0);

  // Calculate angle for each division
  double angle = 360.0 / radialDivisions;
  
  // Create points for each point in the bottom circle and top circle
  for (double i = 0; i < 360; i += angle) {
    double curx = radius * cos(i * DEGREE_RADIAN_FACTOR);
    double curz = radius * sin(i * DEGREE_RADIAN_FACTOR);
    circbot.push_back(Point3(curx, -0.5, curz));
    circtop.push_back(Point3(curx, 0.5, curz));
  }

  // Base circles
  for (int i = 0; i < circbot.size(); ++i) {
    // Create triangle at bottom
    Point3 p1 = circbot.at(i);
    Point3 p2 = circbot.at((i + 1) % circbot.size());
    addTriangle(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, base.x, base.y, base.z);
    
    // Create triangle at top
    p1 = circtop.at(i);
    p2 = circtop.at((i + 1) % circtop.size());
    addTriangle(p2.x, p2.y, p2.z, p1.x, p1.y, p1.z, top.x, top.y, top.z);

    // Create side between top and bottom points
    // Calculate height of each division
    double ystep = 1.0 / heightDivisions;
    for (int j = 0; j < heightDivisions; ++j) {
      Point3 p3 = p1;
      p3.y -= ystep;

      // Add triangle 1
      addTriangle(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, p3.x, p3.y, p3.z);

      Point3 p4 = p2;
      p4.y -= ystep;
      
      // Add triangle 2
      addTriangle(p3.x, p3.y, p3.z, p2.x, p2.y, p2.z, p4.x, p4.y, p4.z);

      p1.y -= ystep;
      p2.y -= ystep;
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

  Point3 base(0, -.5, 0);
  Point3 top(0, .5, 0);

  // Compute angle of each point in the base
  double angle = 360.0 / radialDivisions;
  
  // Create points for each point in the base
  for (double i = 0; i < 360; i += angle) {
    double curx = radius * cos(i * DEGREE_RADIAN_FACTOR);
    double curz = radius * sin(i * DEGREE_RADIAN_FACTOR);
    circbot.push_back(Point3(curx, -0.5, curz));
  }

  // Base circles
  for (int i = 0; i < circbot.size(); ++i) {
    // Create triangle at base
    Point3 p1 = circbot.at(i);
    Point3 p2 = circbot.at((i + 1) % circbot.size());
    addTriangle(p2.x, p2.y, p2.z, p1.x, p1.y, p1.z, base.x, base.y, base.z);
    
    // Create each side from base of cone up to top
    double ystep = 1.0 / heightDivisions;
    double rstep = radius / heightDivisions;
    double rad = radius;
    Point3 p1old(p1);
    Point3 p2old(p2);
    for (int j = 0; j < heightDivisions; ++j) {
      rad -= rstep;

      // Calculate point for division, angle needs to be correct
      Point3 p3;
      p3.x = rad / radius * p1old.x;
      p3.z = rad / radius * p1old.z;
      p3.y = p1.y + ystep;

      addTriangle(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, p3.x, p3.y, p3.z);

      // Calculate point for division, angle needs to be correct.
      Point3 p4;
      p4.x = rad / radius * p2old.x;
      p4.z = rad / radius * p2old.z;
      p4.y = p2.y + ystep;
      
      addTriangle(p3.x, p3.y, p3.z, p2.x, p2.y, p2.z, p4.x, p4.y, p4.z);

      p1 = p3;
      p2 = p4;
    }
    // Add last division (not rectangular)
    addTriangle(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, top.x, top.y, top.z);
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

  double a = 2.0 / (1.0 + sqrt(5.0));

  // Base icosahedron points
  Vector3 p0(0, a, -1);
  Vector3 p1(-a, 1, 0);
  Vector3 p2(a, 1, 0);
  Vector3 p3(0, a, 1);
  Vector3 p4(-1, 0, a);
  Vector3 p5(0, -a, 1);
  Vector3 p6(1, 0, a);
  Vector3 p7(1, 0, -a);
  Vector3 p8(0, -a, -1);
  Vector3 p9(-1, 0, -a);
  Vector3 p10(-a, -1, 0);
  Vector3 p11(a, -1, 0);

  vector<vector<Vector3> > triangles;

  // Base icosahedron triangles
  vector<Vector3> triangle(3);
  triangle.at(0) = p0; triangle.at(1) = p1; triangle.at(2) = p2;
  triangles.push_back(triangle);
  triangle.at(0) = p3; triangle.at(1) = p2; triangle.at(2) = p1;
  triangles.push_back(triangle);
  triangle.at(0) = p3; triangle.at(1) = p4; triangle.at(2) = p5;
  triangles.push_back(triangle);
  triangle.at(0) = p3; triangle.at(1) = p5; triangle.at(2) = p6;
  triangles.push_back(triangle);
  triangle.at(0) = p0; triangle.at(1) = p7; triangle.at(2) = p8;
  triangles.push_back(triangle);
  triangle.at(0) = p0; triangle.at(1) = p8; triangle.at(2) = p9;
  triangles.push_back(triangle);
  triangle.at(0) = p5; triangle.at(1) = p10; triangle.at(2) = p11;
  triangles.push_back(triangle);
  triangle.at(0) = p8; triangle.at(1) = p11; triangle.at(2) = p10;
  triangles.push_back(triangle);
  triangle.at(0) = p1; triangle.at(1) = p9; triangle.at(2) = p4;
  triangles.push_back(triangle);
  triangle.at(0) = p10; triangle.at(1) = p4; triangle.at(2) = p9;
  triangles.push_back(triangle);
  triangle.at(0) = p2; triangle.at(1) = p6; triangle.at(2) = p7;
  triangles.push_back(triangle);
  triangle.at(0) = p11; triangle.at(1) = p7; triangle.at(2) = p6;
  triangles.push_back(triangle);
  triangle.at(0) = p3; triangle.at(1) = p1; triangle.at(2) = p4;
  triangles.push_back(triangle);
  triangle.at(0) = p3; triangle.at(1) = p6; triangle.at(2) = p2;
  triangles.push_back(triangle);
  triangle.at(0) = p0; triangle.at(1) = p9; triangle.at(2) = p1;
  triangles.push_back(triangle);
  triangle.at(0) = p0; triangle.at(1) = p2; triangle.at(2) = p7;
  triangles.push_back(triangle);
  triangle.at(0) = p8; triangle.at(1) = p10; triangle.at(2) = p9;
  triangles.push_back(triangle);
  triangle.at(0) = p8; triangle.at(1) = p7; triangle.at(2) = p11;
  triangles.push_back(triangle);
  triangle.at(0) = p5; triangle.at(1) = p4; triangle.at(2) = p10;
  triangles.push_back(triangle);
  triangle.at(0) = p5; triangle.at(1) = p11; triangle.at(2) = p6;
  triangles.push_back(triangle);

  // Begin subdividing
  for (int i = 0; i < subdivisions; ++i) {
    // Make new vector of triangles
    vector<vector<Vector3> > temp;
    for (int j = 0; j < triangles.size(); ++j) {
      vector<Vector3> triangle = triangles.at(j);
      Vector3 p0 = triangle.at(0);
      Vector3 p1 = triangle.at(1);
      Vector3 p2 = triangle.at(2);

      // Compute intermediate points
      Vector3 x((p0 + p1) * .5);
      Vector3 y((p0 + p2) * .5);
      Vector3 z((p1 + p2) * .5);

      // Create new triangles based on old points and intermediate points
      vector<Vector3> newTriangle(3);
      newTriangle.at(0) = y; newTriangle.at(1) = x; newTriangle.at(2) = p0;
      temp.push_back(newTriangle);
      newTriangle.at(0) = x; newTriangle.at(1) = z; newTriangle.at(2) = p1;
      temp.push_back(newTriangle);
      newTriangle.at(0) = z; newTriangle.at(1) = y; newTriangle.at(2) = p2;
      temp.push_back(newTriangle);

      // Make base triangle use intermediate points
      triangle.at(0) = x;
      triangle.at(1) = y;
      triangle.at(2) = z;
      temp.push_back(triangle);
    }

    // Set triangle vector equal to new vector
    triangles = temp;
  }

  // Add triangles!
  for (vector<vector<Vector3> >::iterator it = triangles.begin();
       it != triangles.end(); ++it) {

       // Normalize each point
       it->at(0).normalize();
       it->at(1).normalize();
       it->at(2).normalize();
       it->at(0) *= .5;
       it->at(1) *= .5;
       it->at(2) *= .5;
       addTriangle(it->at(0).x, it->at(0).y, it->at(0).z,
                   it->at(1).x, it->at(1).y, it->at(1).z,
                   it->at(2).x, it->at(2).y, it->at(2).z);
  }
}
