#include <UGL/Buffer.h>

#include <iostream>

using namespace Ubpa;
using namespace Ubpa::gl;
using namespace std;

Buffer::Buffer(BufferType target, GLsizeiptr size, const void* data, BufferUsage usage)
	: target{ target }, usage { usage }
{
	gl::GenBuffers(1, id.init_ptr());
	Bind();
	gl::BufferData(target, size, data, usage);
}

Buffer::~Buffer() {
	Clear();
}

Buffer::Buffer(Buffer&& buf) noexcept
	: target{ buf.target },
	id{ std::move(buf.id) },
	usage{ buf.usage } {}

Buffer& Buffer::operator=(Buffer&& buf) noexcept {
	Clear();

	target = move(buf.target);
	id = move(buf.id);
	usage = move(buf.usage);
	return *this;
}

void Buffer::Clear() {
	if (IsValid()) {
		gl::DeleteBuffers(1, id.del_ptr());
		id.Clear();
	}
}

void Buffer::Bind() const {
	assert(IsValid());
	gl::BindBuffer(target, id);
}

void Buffer::BindReset(BufferType target) {
	gl::BindBuffer(target, 0);
}
