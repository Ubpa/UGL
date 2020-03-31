#pragma once

#include "gl.h"
#include "Obj.h"

#include <UDP/Basic/Read.h>

#include <vector>
#include <map>

namespace Ubpa::gl {
	class Texture2D;
	class RenderBuffer;

	class FrameBuffer : public Obj {
	public:
		Read<FrameBuffer, FramebufferType> type;

		FrameBuffer(FramebufferType type = FramebufferType::Framebuffer);
		~FrameBuffer();
		FrameBuffer(FrameBuffer&& fb) noexcept;
		FrameBuffer& operator=(FrameBuffer&& fb) noexcept;

		void Clear();

		void Bind() const;
		static void BindReset(FramebufferType type = FramebufferType::Framebuffer);

		void Attach(FramebufferAttachment attachment, Texture2D* tex, GLint level = 0);
		void Attach(FramebufferAttachment attachment, RenderBuffer* rb);
		Texture2D* GetTex2D(FramebufferAttachment attachment) const;

		bool IsComplete() const;
		void DrawBuffers(std::vector<ColorBuffer> attachments);

	private:
		std::map<FramebufferAttachment, Texture2D*> attach2tex;
	};
}
