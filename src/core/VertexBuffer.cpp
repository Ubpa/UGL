#include <UGL/VertexBuffer.h>

#include <iostream>

using namespace Ubpa;
using namespace Ubpa::gl;
using namespace std;

VertexBuffer::VertexBuffer(GLsizeiptr size, const void* data, BufferUsage usage)
	: Buffer(BufferType::ArrayBuffer, size, data, usage) {}

void VertexBuffer::BindReset() {
	Buffer::BindReset(BufferType::ArrayBuffer);
}

GLint VertexBuffer::MaxVertexAttribs() {
	GLint rst;
	gl::GetIntegerv(GL_MAX_VERTEX_ATTRIBS, &rst);
	return rst;
}
