#include <UGL/ElementBuffer.h>

#include <iostream>

using namespace Ubpa;
using namespace Ubpa::gl;
using namespace std;

ElementBuffer::ElementBuffer(BasicPrimitiveType primitive, GLuint num, const GLuint* data, BufferUsage usage)
	: primitive{ primitive },
	numPnts{ num * traits<BasicPrimitiveType>::point_num(primitive) },
	Buffer{ BufferType::ElementArrayBuffer, num * traits<BasicPrimitiveType>::point_num(primitive) * sizeof(GLuint), data, usage} {}

void ElementBuffer::BindReset() {
	gl::BindBuffer(BufferType::ElementArrayBuffer, 0);
}
