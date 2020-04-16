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
		Read<RenderBuffer, size_t> width{ static_cast<size_t>(0) };
		Read<RenderBuffer, size_t> height{ static_cast<size_t>(0) };

		RenderBuffer();
		~RenderBuffer();
		RenderBuffer(RenderBuffer&& fb) noexcept;
		RenderBuffer& operator=(RenderBuffer&& fb) noexcept;

		void Clear();

		void Bind() const;
		static void BindReset();

		void SetStorage(FramebufferInternalFormat internalformat, size_t width, size_t height);

	private:
		friend class FrameBuffer;
		const ID& GetID() const noexcept { return id; }
	};
}
