#pragma once

#include "gl.h"
#include "ID.h"

#include <UDP/Basic/Read.h>

namespace Ubpa::gl {
	class VertexBuffer {
	public:
		Read<VertexBuffer, ID> id{ static_cast<GLuint>(0) }; // 0 is invalid
		Read<VertexBuffer, BufferUsage> usage; // 0 is invalid

		VertexBuffer(GLsizeiptr size, const void* data, BufferUsage usage = BufferUsage::StaticDraw);

		VertexBuffer(VertexBuffer&& vbo) noexcept;
		~VertexBuffer();

		bool IsValid() const noexcept { return id->IsValid(); }

		void Clear();

		void Bind(BufferType target) const;
		static void BindReset(BufferType target);
	};
}
