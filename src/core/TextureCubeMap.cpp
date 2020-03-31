#include <UGL/TextureCubeMap.h>

using namespace Ubpa;
using namespace Ubpa::gl;
using namespace std;

TextureCubeMap::TextureCubeMap()
	: Texture{ TextureType::TextureCubeMap }
{

}

void TextureCubeMap::SetWrapFilter(WrapMode s, WrapMode t, WrapMode r, MinFilter min, MagFilter mag) {
	Bind();
	gl::TexParameteri(type, TextureParam::TextureWrapS, static_cast<GLint>(s));
	gl::TexParameteri(type, TextureParam::TextureWrapT, static_cast<GLint>(t));
	gl::TexParameteri(type, TextureParam::TextureWrapR, static_cast<GLint>(r));
	gl::TexParameteri(type, TextureParam::TextureMinFilter, static_cast<GLint>(min));
	gl::TexParameteri(type, TextureParam::TextureMagFilter, static_cast<GLint>(mag));
	BindReset();
}

void TextureCubeMap::SetImage(TextureCubeTarget target, GLint level, PixelDataInternalFormat internalformat, GLsizei width, GLsizei height, PixelDataFormat format, PixelDataType type, const void* pixels) {
	Texture::SetImage(static_cast<TextureTarget>(target), level, internalformat, width, height, format, type, pixels);
}
