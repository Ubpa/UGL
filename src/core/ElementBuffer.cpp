#include <UGL/ElementBuffer.h>

#include <iostream>

using namespace Ubpa;
using namespace Ubpa::gl;
using namespace std;

ElementBuffer::ElementBuffer(BasicPrimitiveType primitive, size_t num, const GLuint* data, BufferUsage usage)
	: primitive{ primitive },
	numPnts{ static_cast<GLuint>(num * traits<BasicPrimitiveType>::point_num(primitive)) },
	Buffer{ BufferType::ElementArrayBuffer,
	static_cast<GLsizeiptr>(num * traits<BasicPrimitiveType>::point_num(primitive) * sizeof(GLuint)),
	data, usage } {}

void ElementBuffer::BindReset() {
	gl::BindBuffer(BufferType::ElementArrayBuffer, 0);
}
