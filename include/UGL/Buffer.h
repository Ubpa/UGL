#pragma once

#include "gl.h"
#include "ID.h"

#include <UDP/Basic/Read.h>

namespace Ubpa::gl {
	class Buffer {
	public:
		Buffer(BufferType target, GLsizeiptr size, const void* data, BufferUsage usage = BufferUsage::StaticDraw);

		Buffer(Buffer&& buf) noexcept;
		Buffer& operator=(Buffer&& buf) noexcept;
		~Buffer();

		bool IsValid() const noexcept { return id.IsValid(); }

		void Clear();

		void Bind() const;
		static void BindReset(BufferType target);

	protected:
		ID id{ static_cast<GLuint>(0) }; // 0 is invalid
		BufferType target;
		BufferUsage usage; // 0 is invalid
	};
}