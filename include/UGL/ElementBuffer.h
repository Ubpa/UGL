#pragma once

#include "gl.h"
#include "Buffer.h"

#include <UDP/Basic/Read.h>

namespace Ubpa::gl {
	class ElementBuffer : public Buffer {
	public:
		ElementBuffer(GLsizeiptr size, const void* data, BufferUsage usage = BufferUsage::StaticDraw);

		static void BindReset();
	};
}
