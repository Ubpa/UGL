#include <UGL/ElementBuffer.h>

#include <iostream>

using namespace Ubpa;
using namespace Ubpa::gl;
using namespace std;

ElementBuffer::ElementBuffer(GLsizeiptr size, const void* data, BufferUsage usage) : Buffer{ BufferType::ElementArrayBuffer, size, data, usage} {}

void ElementBuffer::BindReset() {
	gl::BindBuffer(BufferType::ElementArrayBuffer, 0);
}
