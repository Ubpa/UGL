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

		void GenerateMipmap();

		static size_t MaxUnit();

	protected:
		void SetImage(TextureTarget target, GLint level, PixelDataInternalFormat internalformat, size_t width, size_t height, PixelDataFormat format, PixelDataType type, const void* pixels);
	};
}
