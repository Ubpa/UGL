#pragma once

#include "gl.h"
#include "Obj.h"

#include <UDP/Basic/Read.h>

#include <map>

namespace Ubpa::gl {
	class Texture2D;

	class RenderBuffer : public Obj {
	public:
		static constexpr RenderbufferType type = RenderbufferType::Renderbuffer;

		Read<RenderBuffer, FramebufferInternalFormat> internalformat;
		Read<RenderBuffer, GLsizei> width{ 0 };
		Read<RenderBuffer, GLsizei> height{ 0 };

		RenderBuffer();
		~RenderBuffer();
		RenderBuffer(RenderBuffer&& fb) noexcept;
		RenderBuffer& operator=(RenderBuffer&& fb) noexcept;

		void Clear();

		void Bind() const;
		static void BindReset();

		void SetStorage(FramebufferInternalFormat internalformat, GLsizei width, GLsizei height);

	private:
		friend class FrameBuffer;
		const ID& GetID() const noexcept { return id; }
	};
}
