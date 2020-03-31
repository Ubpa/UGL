#include <UGL/Texture.h>

using namespace Ubpa;
using namespace Ubpa::gl;
using namespace std;

Texture::Texture(TextureType type)
	: type{ type }
{
	gl::GenTextures(1, id.init_ptr());
}

Texture::~Texture() {
	Clear();
}

void Texture::Clear() {
	if (IsValid()) {
		gl::DeleteTextures(1, id.del_ptr());
		id.Clear();
	}
}

Texture::Texture(Texture&& tex) noexcept
	: Obj{ tex.id }, type{ move(tex.type) }
{
}

Texture& Texture::operator=(Texture&& tex) noexcept {
	Clear();
	id = move(tex.id);
	type = move(tex.type);
	return *this;
}

void Texture::Bind() const {
	gl::BindTexture(type, id);
}

void Texture::BindReset() const {
	gl::BindTexture(type, 0);
}

void Texture::SetImage(GLint level, PixelDataInternalFormat internalformat, GLsizei width, GLsizei height, PixelDataFormat format, PixelDataType type, const void* pixels) {
	Bind();
	gl::TexImage2D(this->type, level, internalformat, width, height, format, type, pixels);
	BindReset();
}

void Texture::SetWrapFilter(WrapMode s, WrapMode t, MinFilter min, MagFilter mag) {
	Bind();
	gl::TexParameteri(type, TextureParam::TextureWrapS, static_cast<GLint>(s));
	gl::TexParameteri(type, TextureParam::TextureWrapT, static_cast<GLint>(t));
	gl::TexParameteri(type, TextureParam::TextureMinFilter, static_cast<GLint>(min));
	gl::TexParameteri(type, TextureParam::TextureMagFilter, static_cast<GLint>(mag));
	BindReset();
}

void Texture::GenerateMipmap() {
	gl::GenerateMipmap(type);
}

size_t Texture::MaxUnit() {
	static GLint rst;
	static bool init = (glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &rst), true);
	return static_cast<size_t>(rst);
}
