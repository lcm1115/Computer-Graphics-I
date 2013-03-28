/*
** File:        vshader.glsl
** Author:      Liam Morris
** Description: Implements transformations for shading routine.
*/

attribute vec4 vPosition;
attribute vec3 vNormal;

uniform vec3 theta;
uniform vec3 trans;
uniform vec3 scale;

uniform vec3 cPosition;
uniform vec3 cLookAt;
uniform vec3 cUp;

// Uniform variable for frustum
uniform float left;
uniform float right;
uniform float top;
uniform float bottom;
uniform float near;
uniform float far;

// Position of light in scene
uniform vec4 LightPosition;

// Vectors for use in fshader
varying vec3 A;
varying vec3 B;
varying vec3 C;


void main()
{
    // Compute the sines and cosines of each rotation
    // about each axis
    vec3 angles = radians (theta);
    vec3 c = cos (angles);
    vec3 s = sin (angles);
    
    // rotation matricies
    mat4 rx = mat4 (1.0,  0.0,  0.0,  0.0, 
                    0.0,  c.x,  s.x,  0.0,
                    0.0, -s.x,  c.x,  0.0,
                    0.0,  0.0,  0.0,  1.0);
                    
    mat4 ry = mat4 (c.y,  0.0, -s.y,  0.0, 
                    0.0,  1.0,  0.0,  0.0,
                    s.y,  0.0,  c.y,  0.0,
                    0.0,  0.0,  0.0,  1.0);

    mat4 rz = mat4 (c.z, -s.z,  0.0,  0.0, 
                    s.z,  c.z,  0.0,  0.0,
                    0.0,  0.0,  1.0,  0.0,
                    0.0,  0.0,  0.0,  1.0);

    mat4 transMat = mat4 (1.0, 0.0, 0.0, 0.0,
			  0.0, 1.0, 0.0, 0.0,
			  0.0, 0.0, 1.0, 0.0,
			  trans.x, trans.y, trans.z, 1.0);
            
    mat4 scaleMat = mat4 (scale.x,  0.0,     0.0,     0.0,
                          0.0,      scale.y, 0.0,     0.0, 
                          0.0,      0.0,     scale.z, 0.0,
                          0.0,      0.0,     0.0,     1.0);
   
    // New matrix after applying transformations.
    mat4 modelMat = transMat * rz * ry * rx * scaleMat;

    // Calculate fshader vectors
    vec3 norm = normalize(cPosition - cLookAt);
    vec3 U = cross(normalize(cUp), norm);
    vec3 V = cross(norm, U);

    // Calculate viewing matrix.
    mat4 viewMat = mat4 (U.x,  V.x, norm.x, 0,
                         U.y,  V.y, norm.y, 0,
                         U.z,  V.z, norm.z, 0,
                         -dot(U, cPosition),
                         -dot(V, cPosition),
                         -dot(norm, cPosition),
                         1);
    
    // Projection matrix (orthographic)
    mat4 projMat = mat4 ((2.0 / (right - left)), 0, 0, 0,
                         0, (2.0 / (top - bottom)), 0, 0,
                         0, 0,   (2.0 / (near - far)), 0,
                         (right + left) / (left - right),
                         (top + bottom) / (bottom - top),
                         (far + near) / (near - far),
                         1);
                             
    A = normalize((viewMat * (LightPosition - modelMat * vPosition)).xyz);
    B = normalize(viewMat * modelMat * vec4(vNormal, 0.0)).xyz;
    C = normalize((-(viewMat * modelMat * vPosition)).xyz);
          
    gl_Position =  projMat * viewMat * modelMat * vPosition;
}
