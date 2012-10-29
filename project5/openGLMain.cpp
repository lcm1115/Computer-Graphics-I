//
//  openGLMain.cpp
//
//  Author:        Joe Geigel
//  Contributors:  Warren R. Carithers,
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
int NumElements = 0;
int NumVertices1 = 0;
int NumVertices2 = 0;

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

// vertex and element array IDs
// one for each object to be drawn
GLuint buffer[2], ebuffer[2];

// program IDs...for program and parameters
GLuint program, theta, trans, scale;

// values for uniform shader variables,
GLfloat angles[3] = {-30.0, 30.0, -30.0};
GLfloat transData[3] = { 0.35, -0.35, 0.0 };
GLfloat scaleData[3] = {0.75, 0.75, 0.75 };

GLfloat angles2[3] = {60.0, 60.0, 60.0};
GLfloat transData2[3] = { -0.5, 0.5, 0.0 };
GLfloat scaleData2[3] = {.25, 0.25, 0.25};

void 
createShapes()
{
    // define the triangles for your shapes here and send the vertex data
    // to OpenGL
    makeCube(3);
    
    // get the points for your shape
    NumElements = nVerticies() / 3;
    NumVertices1 = nVerticies();
    float *points = getVerticies();
    int dataSize = nVerticies() * 4 * sizeof (float);
    GLushort *elements = getElements();
    int edataSize = nVerticies() * sizeof (GLushort);
    
    // setup the vertex buffer
    if (bufferInit) glDeleteBuffers (1, &buffer[0]);
    glGenBuffers( 1, &buffer[0]);
    glBindBuffer( GL_ARRAY_BUFFER, buffer[0] );
    glBufferData( GL_ARRAY_BUFFER, dataSize, points, GL_STATIC_DRAW );
    bufferInit = true;
    
    // setup the element buffer
    if (bufferInit) glDeleteBuffers (1, &ebuffer[0]);
    glGenBuffers( 1, &ebuffer[0] );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebuffer[0] );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, edataSize, elements, GL_STATIC_DRAW );
    
    glUseProgram( program );
    
    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0,
                          BUFFER_OFFSET(0) );

    makeCone(1, 10, 5);

    // get the points for your shape
    NumElements = nVerticies() / 3;
    NumVertices2 = nVerticies() - NumVertices1;
    points = getVerticies();
    dataSize = nVerticies() * 4 * sizeof (float);
    elements = getElements();
    edataSize = nVerticies() * sizeof (GLushort);
    
    // setup the vertex buffer
    if (bufferInit) glDeleteBuffers (1, &buffer[1]);
    glGenBuffers( 1, &buffer[1]);
    glBindBuffer( GL_ARRAY_BUFFER, buffer[1] );
    glBufferData( GL_ARRAY_BUFFER, dataSize, points, GL_STATIC_DRAW );
    bufferInit = true;
    
    // setup the element buffer
    if (bufferInit) glDeleteBuffers (1, &ebuffer[1]);
    glGenBuffers( 1, &ebuffer[1] );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebuffer[1] );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, edataSize, elements, GL_STATIC_DRAW );
    
    glUseProgram( program );
    
    // set up vertex arrays
    vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0,
                          BUFFER_OFFSET(0) );
    
    // uniform variables
    theta = glGetUniformLocation(program, "theta");
    scale = glGetUniformLocation(program, "scale");
    trans = glGetUniformLocation(program, "trans");
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
    glCullFace( GL_BACK );
    glClearColor( 1.0, 1.0, 1.0, 1.0 );
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    
    // create the geometry for your shapes.
    createShapes();
}


void
display( void )
{
    // clear and draw params..keep these
    // for this assignment, we will continue to use wireframe
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glCullFace(GL_BACK);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glUniform3fv(theta, 1, angles);
    glUniform3fv(scale, 1, scaleData);
    glUniform3fv(trans, 1, transData);

    // draw your shapes here
    glDrawElements(GL_TRIANGLES, NumVertices1, GL_UNSIGNED_SHORT, (void *)0);

    glUniform3fv(theta, 1, angles2);
    glUniform3fv(scale, 1, scaleData2);
    glUniform3fv(trans, 1, transData2);
    glDrawElements(GL_TRIANGLES, NumVertices2, GL_UNSIGNED_SHORT, (void *)(NumVertices1 * sizeof(GLushort)));
    
    // swap the buffers
    glutSwapBuffers();
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
    
    glutMainLoop();
    return 0;
}

