#pragma once

#include "gl.h"
#include "Buffer.h"

#include <UDP/Basic/Read.h>

namespace Ubpa::gl {
	class VertexBuffer : public Buffer {
	public:
		struct AttribPointer {
			const VertexBuffer* vbo;
			GLint size;
			DataType type;
			GLboolean normalized;
			GLsizei stride;
			const void* pointer;
		};

	public:
		VertexBuffer(GLsizeiptr size, const void* data, BufferUsage usage = BufferUsage::StaticDraw);

		AttribPointer AttrPtr(
			GLint size,
			DataType type,
			GLboolean normalized,
			GLsizei stride,
			const void* pointer = (void*)(0)) const noexcept
		{
			return { this, size, type, normalized, stride, pointer };
		}

		static GLint MaxVertexAttribs();

		static void BindReset();
	};
}
