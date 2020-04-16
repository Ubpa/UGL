#pragma once

#include "Texture.h"

namespace Ubpa::gl {
	class FrameBuffer;

	class Texture2D : public Texture {
	public:
		Texture2D();

		void SetImage(GLint level, PixelDataInternalFormat internalformat, size_t width, size_t height, PixelDataFormat format, PixelDataType type, const void* pixels);

		void SetWrapFilter(WrapMode s, WrapMode t, MinFilter min, MagFilter mag);

	private:
		friend class FrameBuffer;
		const ID& GetID() const noexcept { return id; }
	};
}