/**
 *
 * simpleShape.cpp
 *
 * routines for adding triangles to create a new mesh
 *
 * Students are not to modify this file.
 *
 */

#ifdef __APPLE__
#include <OPENGL/gl.h>
#else
#include <GL/glew.h>
#include <GL/gl.h>
#endif

#include <vector>
#include <iostream>
#include "simpleShape.h"

using namespace std;

/**
 * common variables...should probably make this a class and make these
 * data members
 */
vector<Point3> vertices;
float *pointArray = 0;
GLushort *elemArray = 0;


/**
 * clear the current shape
 */
void clearShape ()
{
    if (pointArray) {
        delete pointArray;
        delete elemArray;
        pointArray = 0;
        elemArray = 0;
    }
    vertices.clear();
}


/**
 * adds a triangle to the current shape
 */
void addTriangle (const Point3& p1, const Point3& p2, const Point3& p3)
{
    vertices.push_back (p1);
    vertices.push_back (p2);
    vertices.push_back (p3);
}


/**
 * gets the vertex points for the current shape
 */
float *getVertices ()
{
    // delete the old point array of we have one
    if (pointArray) {
        delete pointArray;
    }
    
    // create and fill a new point array
    pointArray = new float[vertices.size()*4];
    for (int i=0; i < vertices.size(); i++) {
        pointArray[i*4] = vertices[i].x;
        pointArray[i*4+1] = vertices[i].y;
        pointArray[i*4+2] = vertices[i].z;
        pointArray[i*4+3] = 1.0;
    }
        
    return pointArray;
}

/**
 * gets the  array of elements for the  current shape
 */
GLushort *getElements ()
{
    // delete the old point array of we have one
    if (elemArray) {
        delete elemArray;
    }
    
    // create and fill a new point array
    elemArray = new GLushort[vertices.size()*4];
    for (int i=0; i < vertices.size(); i++) {
        elemArray[i] = i;
    }
    
    return elemArray;
}



/**
 * returns number of verticies in current shape
 */
int nVertices ()
{
    return vertices.size();
}
