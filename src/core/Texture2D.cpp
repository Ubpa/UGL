#include <UGL/Texture2D.h>

using namespace Ubpa;
using namespace Ubpa::gl;
using namespace std;

Texture2D::Texture2D()
	: Texture{ TextureType::Texture2D }
{

}

void Texture2D::SetWrapFilter(WrapMode s, WrapMode t, MinFilter min, MagFilter mag) {
	Bind();
	gl::TexParameteri(type, TextureParam::TextureWrapS, static_cast<GLint>(s));
	gl::TexParameteri(type, TextureParam::TextureWrapT, static_cast<GLint>(t));
	gl::TexParameteri(type, TextureParam::TextureMinFilter, static_cast<GLint>(min));
	gl::TexParameteri(type, TextureParam::TextureMagFilter, static_cast<GLint>(mag));
	BindReset();
}

void Texture2D::SetImage(GLint level, PixelDataInternalFormat internalformat, GLsizei width, GLsizei height, PixelDataFormat format, PixelDataType type, const void* pixels) {
	Texture::SetImage(TextureTarget::Texture2D, level, internalformat, width, height, format, type, pixels);
}
