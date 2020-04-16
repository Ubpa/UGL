#pragma once

#include "gl.h"
#include "Obj.h"

#include <UDP/Basic/Read.h>

namespace Ubpa::gl {
	class Buffer : public Obj {
	public:
		Read<Buffer, BufferUsage> usage;

		Buffer(BufferType target, size_t size, const void* data, BufferUsage usage = BufferUsage::StaticDraw);

		Buffer(Buffer&& buf) noexcept;
		Buffer& operator=(Buffer&& buf) noexcept;
		~Buffer();

		void Clear();

		void Bind() const;
		static void BindReset(BufferType target);

		void SubData(GLintptr offset, GLsizeiptr size, const void* data);

	protected:
		BufferType target;
	};
}
