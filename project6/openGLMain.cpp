//
//  openGLMain.cpp
//
//  Author:        Joe Geigel
//  Contributors:  Warren R. Carithers,
//                 Liam Morris
//  
//  Main program for OpenGL assignments.
//

#include <stdlib.h>
#include <iostream>

#ifdef __APPLE__ 
#include <GLUT/GLUT.h>
#include <OpenGL/gl.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#endif

#include "cg1Shape.h"
#include "ShaderSetup.h"
#include "simpleShape.h"

using namespace std;

bool bufferInit = false;
int NumElements;
float dRStep = .01;
float dGStep = .02;
float dBStep = .03;

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

// vertex and element array IDs
// one for each object to be drawn
GLuint buffer, ebuffer;

// program IDs...for program and parameters
GLuint program, theta, trans, scale, glLeft, glRight, glTop, glBottom, glNear,
       glFar, cPosition, cLookAt, cUp, lPos, ambient, diffuse, specular,
       specexp;

// values for uniform shader variables,

// Transformation 1
GLfloat angles[3] = {0.0, 0.0, 0.0};
GLfloat transData[3] = {0.0, 0.0, 0.0};
GLfloat scaleData[3] = {1.0, 1.0, 1.0};

GLfloat cPosData[] = {0.0, 0.0, 1.0};
GLfloat lookatData[] = {0.0, 0.0, 0.0};
GLfloat upData[] = {0.0, 1.0, 0.0};

GLfloat lPosData[] = {0.0, 0.0, 2.0, 1.0};
GLfloat ambientData[] = {0.1, 0.1, 0.1, 1.0};
GLfloat diffuseData[] = {0.0, 0.0, 0.0, 1.0};
GLfloat specularData[] = {1.0, 1.0, 1.0, 1.0};
GLfloat spec_exponent = 2.5;

void 
createShapes()
{
    clearShape();

    // define the triangles for your shapes here and send the vertex data
    // to OpenGL
    makeSphere(1, 3);
    NumElements = nVerticies() / 3;
    float *points = getVerticies();
    vector<float> n = getNormals();
    float normals[n.size()];
    copy(n.begin(), n.end(), normals);
    int nDataSize = n.size() * sizeof(float);
    int dataSize = nVerticies() * 4 * sizeof (float);
    GLushort *elements = getElements();
    int edataSize = nVerticies() * sizeof (GLushort);
    
    // setup the vertex buffer
    if (bufferInit) glDeleteBuffers (1, &buffer);
    glGenBuffers( 1, &buffer);
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, dataSize + nDataSize, 0, GL_STATIC_DRAW );
    glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, points);
    glBufferSubData(GL_ARRAY_BUFFER, dataSize, nDataSize, normals);
    bufferInit = true;
    
    // setup the element buffer
    if (bufferInit) glDeleteBuffers (1, &ebuffer);
    glGenBuffers( 1, &ebuffer );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebuffer );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, edataSize, elements, GL_STATIC_DRAW );
    
    glUseProgram( program );
    
    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0,
                          BUFFER_OFFSET(0) );
    
}


// OpenGL initialization 
void init() {
    GLuint errors;
    
    // Load shaders and use the resulting shader program
    program = ShaderSetup( "vshader.glsl", "fshader.glsl", &errors );
    if (errors > 0) {
        cerr << "Error setting up shaders, code " << errors << endl;
        exit(1);
    }
    
    // Some openGL initialization...probably best to keep
    glEnable( GL_DEPTH_TEST ); 
    glEnable( GL_CULL_FACE );
    glClearColor( 1.0, 1.0, 1.0, 1.0 );
    
    // create the geometry for your shapes.
    createShapes();
}


void
display( void )
{
    // uniform variables
    theta = glGetUniformLocation(program, "theta");
    scale = glGetUniformLocation(program, "scale");
    trans = glGetUniformLocation(program, "trans");

    cPosition = glGetUniformLocation(program, "cPosition");
    cLookAt = glGetUniformLocation(program, "cLookAt");
    cUp = glGetUniformLocation(program, "cUp");

    lPos = glGetUniformLocation(program, "LightPosition");
    ambient = glGetUniformLocation(program, "ambient");
    diffuse = glGetUniformLocation(program, "diffuse");
    specular = glGetUniformLocation(program, "specular");
    specexp = glGetUniformLocation(program, "specexp");

    glLeft = glGetUniformLocation(program, "left");
    glRight = glGetUniformLocation(program, "right");
    glTop = glGetUniformLocation(program, "top");
    glBottom = glGetUniformLocation(program, "bottom");
    glNear = glGetUniformLocation(program, "near");
    glFar = glGetUniformLocation(program, "far");

    int dataSize = nVerticies() * 4 * sizeof(float);
    GLuint vNormal = glGetAttribLocation(program, "vNormal");
    glEnableVertexAttribArray(vNormal);
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE,
                          0, BUFFER_OFFSET(dataSize));
    

    glUniform3fv(theta, 1, angles);
    glUniform3fv(scale, 1, scaleData);
    glUniform3fv(trans, 1, transData);

    glUniform3fv(cPosition, 1, cPosData);
    glUniform3fv(cLookAt, 1, lookatData);
    glUniform3fv(cUp, 1, upData);

    glUniform1f(glLeft, -2);
    glUniform1f(glRight, 2);
    glUniform1f(glTop, 2);
    glUniform1f(glBottom, -2);
    glUniform1f(glNear, 2);
    glUniform1f(glFar, -2);

    glUniform4fv(lPos, 1, lPosData);
    glUniform4fv(ambient, 1, ambientData);
    glUniform4fv(diffuse, 1, diffuseData);
    glUniform4fv(specular, 1, specularData);
    glUniform1f(specexp, spec_exponent);

    // clear and draw params..keep these
    // for this assignment, we will continue to use wireframe
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glCullFace(GL_BACK);

    // draw your shapes here
    glDrawElements(GL_TRIANGLES, nVerticies(), GL_UNSIGNED_SHORT, (void *)0);
    
    // swap the buffers
    glutSwapBuffers();
}

void animate(int i) {
  angles[0] -= .5;
  angles[1] -= 1;
  angles[2] -= .125;
  diffuseData[0] += dRStep;
  diffuseData[1] += dGStep;
  diffuseData[2] += dBStep;
  if (diffuseData[0] <= 0) {
    diffuseData[0] = 0;
    dRStep *= -1;
  }
  if (diffuseData[0] >= 1) {
    diffuseData[0] = 1;
    dRStep *= -1;
  }
  if (diffuseData[1] <= 0) {
    diffuseData[1] = 0;
    dGStep *= -1;
  }
  if (diffuseData[1] >= 1) {
    diffuseData[1] = 1;
    dGStep *= -1;
  }
  if (diffuseData[2] <= 0) {
    diffuseData[2] = 0;
    dBStep *= -1;
  }
  if (diffuseData[2] >= 1) {
    diffuseData[2] = 1;
    dBStep *= -1;
  }
  glutTimerFunc(25, animate, i);
  glutPostRedisplay();
}


void
keyboard( unsigned char key, int x, int y )
{
    switch( key ) {
	case 033:  // Escape key
	case 'q': case 'Q':
	    exit( 0 );
        break;
    } 
    
    glutPostRedisplay();
}

int main (int argc, char **argv)
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize( 512, 512 );
    glutCreateWindow( "CG1 - OpenGL Scene" );
    
#ifndef __APPLE__
    glewInit();
#endif
    
    init();
    
    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );
    glutTimerFunc(25, animate, 1);
    glutMainLoop();
    return 0;
}

