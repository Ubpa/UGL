#pragma once

#include "gl.h"
#include "Buffer.h"

#include <UDP/Basic/Read.h>

namespace Ubpa::gl {
	class ElementBuffer : public Buffer {
	public:
		Read<ElementBuffer, BasicPrimitiveType> primitive;
		Read<ElementBuffer, GLuint> numPnts;

		ElementBuffer(BasicPrimitiveType primitive, size_t num, const GLuint* data, BufferUsage usage = BufferUsage::StaticDraw);

		static void BindReset();
	};
}
