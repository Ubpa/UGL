#pragma once

#include "gl.h"
#include "ID.h"
#include "VertexBuffer.h"

namespace Ubpa::gl {
	class VertexArray {
	public:
		VertexArray();
		~VertexArray();

		VertexArray(VertexArray&& va) noexcept;
		VertexArray& operator=(VertexArray&& va) noexcept;

		void Attach(GLuint idx, const VertexBuffer::AttribPointer& ptr) const;

		void Clear();

		void Bind() const;
		static void BindReset();

	private:
		ID id{ static_cast<GLuint>(0) }; // 0 is invalid
	};
}
