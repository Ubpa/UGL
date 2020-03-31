#pragma once

#include "Texture.h"

namespace Ubpa::gl {
	class FrameBuffer;

	class TextureCubeMap : public Texture {
	public:
		TextureCubeMap();

		void SetImage(TextureCubeTarget target, GLint level, PixelDataInternalFormat internalformat, GLsizei width, GLsizei height, PixelDataFormat format, PixelDataType type, const void* pixels);

		void SetWrapFilter(WrapMode s, WrapMode t, WrapMode r, MinFilter min, MagFilter mag);

	private:
		friend class FrameBuffer;
		const ID& GetID() const noexcept { return id; }
	};
}
