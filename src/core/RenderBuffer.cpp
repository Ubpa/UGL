#include <UGL/RenderBuffer.h>

#include <UGL/Texture2D.h>

using namespace Ubpa;
using namespace Ubpa::gl;
using namespace std;

RenderBuffer::RenderBuffer() {
	gl::GenRenderbuffers(1, id.init_ptr());
}

RenderBuffer::~RenderBuffer() {
	Clear();
}

RenderBuffer::RenderBuffer(RenderBuffer&& fb) noexcept
	: Obj{ move(fb.id) } {}

RenderBuffer& RenderBuffer::operator=(RenderBuffer&& fb) noexcept {
	Clear();
	id = move(fb.id);
	return *this;
}

void RenderBuffer::Clear() {
	if (IsValid()) {
		gl::DeleteRenderbuffers(1, id.del_ptr());
		id.Clear();
	}
}

void RenderBuffer::Bind() const {
	gl::BindRenderbuffer(id);
}

void RenderBuffer::BindReset() {
	gl::BindRenderbuffer(static_cast<GLuint>(0));
}

void RenderBuffer::SetStorage(FramebufferInternalFormat internalformat, GLsizei width, GLsizei height) {
	Bind();
	gl::RenderbufferStorage(internalformat, width, height);
	BindReset();
}
