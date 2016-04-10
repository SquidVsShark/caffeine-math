#ifndef COMMON_INCLUDED_57928899_C288_49E0_8694_6E85E36592EA
#define COMMON_INCLUDED_57928899_C288_49E0_8694_6E85E36592EA


#include <ostream>
#ifdef WIN32
#include <GL/glew.h>
#else
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#endif

#include <iostream> // kill!
#include <utilities/logging.hpp>


#define LOG_GL_ERROR(msg)


namespace Ogl {


/*!
  Resets the gl states to the applications default.
*/
inline void
default_state()
{
  glDisable(GL_BLEND);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_STENCIL_TEST);
  glFrontFace(GL_CCW);
}


/*!
  Sugar function to for clear color
*/
inline void
clear_color(const float r = 0,
            const float g = 0,
            const float b = 0,
            const float a = 0)
{
  glClearColor(r, g, b, a);
}


/*!
  Sugar function to clear attached buffer
  \param color If true clears the attached color buffer.
  \param depth If true clears the attached depth buffer.
*/
inline void
clear(const bool color, const bool depth)
{
  GLint clear = 0;
  
  if(color) { clear |= GL_COLOR_BUFFER_BIT; }
  if(depth) { clear |= GL_DEPTH_BUFFER_BIT; }

  glClear(clear);
}


/*!
  Initialize vao
*/
inline void
vao_init()
{
  static GLuint vao(0);
  
  if(!vao)
  {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
  }
}


/*!
  Checks glGetError, if an error is found it will push it out
  in the stream that was provided.
*/
void
error_check(const char* msg, std::ostream *stream);


void
error_output(const char *msg);

/*!
  Clears any pending error.
*/
void
error_clear();


} // ns


#endif // inc guard