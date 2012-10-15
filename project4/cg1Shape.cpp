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
