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
	: Obj{ move(tex.id) }, type{ tex.type }
{
}

Texture& Texture::operator=(Texture&& tex) noexcept {
	Clear();
	id = move(tex.id);
	type = tex.type;
	return *this;
}

void Texture::Bind() const {
	gl::BindTexture(type, id);
}

void Texture::BindReset() const {
	gl::BindTexture(type, 0);
}

void Texture::SetImage(TextureTarget target, GLint level, PixelDataInternalFormat internalformat, GLsizei width, GLsizei height, PixelDataFormat format, PixelDataType type, const void* pixels) {
	Bind();
	gl::TexImage2D(target, level, internalformat, width, height, format, type, pixels);
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
