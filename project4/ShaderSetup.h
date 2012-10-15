/*
** ShaderSetup
**
** Set up a GLSL shader based on supplied source files.
*/

#ifndef _SHADERSETUP_H_
#define _SHADERSETUP_H_

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

/*
** read_text_file(name)
**
** Read the text file given as 'name'.
**
** Returns the contents of the file in a dynamically-allocated
** string buffer, or NULL if an error occurs.
*/

GLchar *read_text_file( const char *name );

/*
** print_shader_info_log(shader)
**
** Print the information log from a shader compilation attempt
*/

void print_shader_info_log( GLuint shader );

/*
** print_program_info_log(shader)
**
** Print a program information log
**
** This is identical to print_shader_info_log(), except that it uses
** glGetProgramiv() and glGetProgramInfoLog() instead of the *Shader*()
** versions.
*/

void print_program_info_log( GLuint shader );

/*
** ShaderSetup(vertex,fragment)
**
** Set up a GLSL shader program.
**
** Requires the name of a vertex program and a fragment
** program.  Returns a handle to the created GLSL program
**
** Arguments:
**      vert   - vertex shader program source file
**      frag   - fragment shader program source file
**	errors - pointer to variable to be incremented in case of error
**
** On success:
**	returns the GLSL shader program handle, and *errors == 0
**
** On failure:
**	returns 0, and *errors contains an error code
*/

GLuint ShaderSetup( const char *vert, const char *frag, GLuint *errors );

#endif
