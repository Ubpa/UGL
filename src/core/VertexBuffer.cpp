#include <UGL/VertexBuffer.h>

#include <iostream>

using namespace Ubpa;
using namespace Ubpa::gl;
using namespace std;

VertexBuffer::VertexBuffer(GLsizeiptr size, const void* data, BufferUsage usage) : usage{ usage } {
	gl::GenBuffers(1, id.val);
	Bind(BufferType::ArrayBuffer);
	gl::BufferData(BufferType::ArrayBuffer, size, data, usage);
}

VertexBuffer::~VertexBuffer() {
	Clear();
}

VertexBuffer::VertexBuffer(VertexBuffer&& vbo) noexcept
	: id{ std::move(vbo.id) }, usage{vbo.usage} {}

void VertexBuffer::Clear() {
	if (IsValid()) {
		gl::DeleteBuffers(1, id.get());
		id->Clear();
	}
}

void VertexBuffer::Bind(BufferType target) const {
	assert(IsValid());
	gl::BindBuffer(target, id.get());
}

void VertexBuffer::BindReset(BufferType target) {
	gl::BindBuffer(target, 0);
}
