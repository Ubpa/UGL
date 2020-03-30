#pragma once

#include "config.h"

#include <UGM/UGM>

namespace Ubpa::gl {
	enum class Clear_Mask : GLbitfield {
		COLOR_BUFFER = GL_COLOR_BUFFER_BIT,
		DEPTH_BUFFER = GL_DEPTH_BUFFER_BIT,
		STENCIL_BUFFER = GL_STENCIL_BUFFER_BIT
	};
	void Clear(Clear_Mask mask);

	void ClearColor(rgba<GLfloat> c);

	void Viewport(point<GLint, 2> xy, GLsizei width, GLsizei height);
}
