#include <UGL/VertexArray.h>

#include <UGL/Program.h>
#include <UGL/ElementBuffer.h>

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

VertexArray::VertexArray(const std::vector<size_t>& indices, const Format& format) noexcept
	: VertexArray{}
{
	Attach(indices, format);
}

VertexArray::VertexArray(VertexArray&& va) noexcept
	: Obj{ move(va.id) } {}

VertexArray& VertexArray::operator=(VertexArray&& va) noexcept {
	Clear();
	id = move(va.id);
	return *this;
}

void VertexArray::Clear() {
	gl::DeleteVertexArrays(1, id.del_ptr());
	id.Clear();
}

void VertexArray::Attach(size_t idx, const VertexBuffer::AttribPointer& ptr) const {
	Bind();
	ptr.vbo->Bind();
	gl::VertexAttribPointer(idx, ptr.size, ptr.type, ptr.normalized, ptr.stride, ptr.offset);
	gl::EnableVertexAttribArray(idx);
	BindReset();
	ptr.vbo->BindReset();
}

void VertexArray::Attach(const std::vector<size_t>& indices, const Format& format) {
	assert(indices.size() == format.attrptrs.size());
	assert(format.eb != nullptr);
	Bind();
	for (size_t i = 0; i < indices.size(); i++) {
		const auto& attrptr = format.attrptrs[i];
		attrptr.vbo->Bind();
		gl::VertexAttribPointer(indices[i], attrptr.size, attrptr.type, attrptr.normalized, attrptr.stride, attrptr.offset);
		gl::EnableVertexAttribArray(indices[i]);
	}
	BindReset();
	VertexBuffer::BindReset();
	ElementBuffer::BindReset();
}

void VertexArray::Attach(const ElementBuffer& eb) {
	Bind();
	eb.Bind();
	BindReset();
	ElementBuffer::BindReset();
}
