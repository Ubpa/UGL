#pragma once

#include "gl.h"
#include "Buffer.h"

#include <UDP/Basic/Read.h>

namespace Ubpa::gl {
	class VertexBuffer : public Buffer {
	public:
		VertexBuffer(GLsizeiptr size, const void* data, BufferUsage usage = BufferUsage::StaticDraw);

		static GLint MaxVertexAttribs();

		static void BindReset();
	};
}
