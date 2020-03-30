#pragma once

#include "gl.h"
#include "Obj.h"

#include <UDP/Basic/Read.h>

namespace Ubpa::gl {
	class Texture : public Obj {
	public:
		Read<Texture, TextureType> type;

		Texture(TextureType type);

		void Bind() const;
		void BindReset() const;

		void SetImage(GLint level, PixelDataInternalFormat internalformat, GLsizei width, GLsizei height, PixelDataFormat format, PixelDataType type, const void* pixels);

		void SetWrapFilter(WrapMode s, WrapMode t, MinFilter min, MagFilter mag);

		void GenerateMipmap();

		void Use(size_t i);

		static size_t MaxUnit();
	};
}
