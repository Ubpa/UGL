#pragma once

#include "gl.h"
#include "Buffer.h"

#include <UDP/Basic/Read.h>

namespace Ubpa::gl {
	class VertexBuffer : public Buffer {
	public:
		struct AttribPointer {
			const VertexBuffer* vbo;
			size_t size;
			DataType type;
			GLboolean normalized;
			size_t stride;
			size_t offset;
		};

	public:
		VertexBuffer(size_t size, const void* data, BufferUsage usage = BufferUsage::StaticDraw);

		AttribPointer AttrPtr(
			size_t size,
			DataType type,
			GLboolean normalized,
			size_t stride,
			size_t offset = 0) const noexcept
		{
			return { this, size, type, normalized, stride, offset };
		}

		static GLint MaxVertexAttribs();

		static void BindReset();
	};
}
