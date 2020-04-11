#include <UGL/FrameBuffer.h>

#include <UGL/Texture2D.h>
#include <UGL/RenderBuffer.h>

using namespace Ubpa;
using namespace Ubpa::gl;
using namespace std;

FrameBuffer::FrameBuffer(FramebufferType type)
	: type{ type }
{
	gl::GenFramebuffers(1, id.init_ptr());
}

FrameBuffer::~FrameBuffer() {
	Clear();
}

FrameBuffer::FrameBuffer(FrameBuffer&& fb) noexcept
	: Obj{ move(fb.id) }, type{ fb.type }, attach2tex{ move(fb.attach2tex) } {}

FrameBuffer& FrameBuffer::operator=(FrameBuffer&& fb) noexcept {
	Clear();
	id = move(fb.id);
	type = fb.type;
	attach2tex = move(fb.attach2tex);
	return *this;
}

void FrameBuffer::Clear() {
	if (IsValid()) {
		gl::DeleteFramebuffers(1, id.del_ptr());
		id.Clear();
	}
	attach2tex.clear();
}

void FrameBuffer::Bind() const {
	gl::BindFramebuffer(type, id);
}

void FrameBuffer::BindReset(FramebufferType type) {
	gl::BindFramebuffer(type, static_cast<GLuint>(0));
}

void FrameBuffer::Attach(FramebufferAttachment attachment, Texture2D* tex, GLint level) {
	Bind();
	FramebufferTexture2D(type, attachment, static_cast<GLenum>(tex->type.get()), tex->GetID(), level);
	BindReset(type);

	attach2tex[attachment] = tex;
}

void FrameBuffer::Attach(FramebufferAttachment attachment, RenderBuffer* rb) {
	Bind();
	gl::FramebufferRenderbuffer(type, attachment, rb->GetID());
	BindReset(type);
}

Texture2D* FrameBuffer::GetTex2D(FramebufferAttachment attachment) const {
	auto target = attach2tex.find(attachment);
	if (target == attach2tex.end())
		return nullptr;
	return target->second;
}

bool FrameBuffer::IsComplete() const {
	Bind();
	auto status = gl::CheckFramebufferStatus(type);
	BindReset();
	return status == FramebufferStatus::FramebufferComplete;
}

void FrameBuffer::DrawBuffers(std::vector<ColorBuffer> attachments) {
	Bind();
	gl::DrawBuffers(static_cast<GLuint>(attachments.size()), reinterpret_cast<GLenum*>(attachments.data()));
	BindReset();
}
