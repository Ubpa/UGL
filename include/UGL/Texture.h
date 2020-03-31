#pragma once

#include "gl.h"
#include "Obj.h"

#include <UDP/Basic/Read.h>

namespace Ubpa::gl {
	class Texture : public Obj {
	public:
		Read<Texture, TextureType> type;

		Texture(TextureType type);
		~Texture();
		void Clear();
		Texture(Texture&& tex) noexcept;
		Texture& operator=(Texture&& tex) noexcept;

		void Bind() const;
		void BindReset() const;

		void SetImage(GLint level, PixelDataInternalFormat internalformat, GLsizei width, GLsizei height, PixelDataFormat format, PixelDataType type, const void* pixels);

		void SetWrapFilter(WrapMode s, WrapMode t, MinFilter min, MagFilter mag);

		void GenerateMipmap();

		static size_t MaxUnit();
	};
}
