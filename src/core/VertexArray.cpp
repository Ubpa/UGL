#include <UGL/VertexArray.h>

using namespace Ubpa;
using namespace Ubpa::gl;
using namespace std;

VertexArray::VertexArray() {
	gl::GenVertexArrays(1, id.init_ptr());
}

VertexArray::~VertexArray() {
	Clear();
}

void VertexArray::Bind() const {
	gl::BindVertexArray(id);
}

void VertexArray::BindReset() {
	gl::BindVertexArray(0);
}

VertexArray::VertexArray(VertexArray&& va) noexcept
	: id{ move(va.id) } {}

VertexArray& VertexArray::operator=(VertexArray&& va) noexcept {
	id = move(va.id);
	return *this;
}

void VertexArray::Clear() {
	gl::DeleteVertexArrays(1, id.del_ptr());
	id.Clear();
}

void VertexArray::Attach(GLuint idx, const VertexBuffer::AttribPointer& ptr) const {
	Bind();
	ptr.vbo->Bind();
	gl::VertexAttribPointer(idx, ptr.size, ptr.type, ptr.normalized, ptr.stride, (void*)0);
	gl::EnableVertexAttribArray(idx);
	BindReset();
	ptr.vbo->BindReset();
}
