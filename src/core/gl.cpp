#include <UGL/gl.h>

using namespace Ubpa;

void gl::ClearColor(rgba<GLfloat> c) {
	glClearColor(c[0], c[1], c[2], c[3]);
}

void gl::Clear(Clear_Mask mask) {
	glClear(static_cast<GLbitfield>(mask));
}

void gl::Viewport(point<GLint, 2> xy, GLsizei width, GLsizei height) {
	glViewport(xy[0], xy[1], width, height);
}
