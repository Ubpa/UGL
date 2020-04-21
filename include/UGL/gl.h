#pragma once

#include "config.h"
#include "enums.h"
#include "traits.h"

#include <UGM/UGM.h>

namespace Ubpa::gl {
	// ================================ optimize ================================

	inline void BlendColor(rgbaf c) {
		glBlendColor(static_cast<GLfloat>(c[0]), static_cast<GLfloat>(c[1]), static_cast<GLfloat>(c[2]), static_cast<GLfloat>(c[3]));
	}

	inline void BlendFunc(BlendFactor sfactor, BlendFactor dfactor) {
		glBlendFunc(static_cast<GLenum>(sfactor), static_cast<GLenum>(dfactor));
	}

	inline void BlendEquation(BlendEqMode mode) {
		glBlendEquation(static_cast<GLenum>(mode));
	}

	inline void BlendFuncSeparate(BlendFactor sfactorRGB, BlendFactor dfactorRGB, BlendFactor sfactorAlpha, BlendFactor dfactorAlpha) {
		glBlendFuncSeparate(static_cast<GLenum>(sfactorRGB),
			static_cast<GLenum>(dfactorRGB),
			static_cast<GLenum>(sfactorAlpha),
			static_cast<GLenum>(dfactorAlpha));
	}

	inline void BindBuffer(BufferType target, GLuint buffer) {
		glBindBuffer(static_cast<GLenum>(target), buffer);
	}

	inline void BindFramebuffer(FramebufferType target, GLuint framebuffer) {
		glBindFramebuffer(static_cast<GLenum>(target), framebuffer);
	}

	inline void BindRenderbuffer(GLuint renderbuffer) {
		glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
	}

	inline void BindTexture(TextureType target, GLuint texture) {
		glBindTexture(static_cast<GLenum>(target), texture);
	}

	inline void BufferData(BufferType target, size_t size, const void* data, BufferUsage usage) {
		glBufferData(static_cast<GLenum>(target), static_cast<GLsizeiptr>(size), data, static_cast<GLenum>(usage));
	}

	inline void BufferSubData(BufferType target, size_t offset, size_t size, const void* data) {
		glBufferSubData(static_cast<GLenum>(target), static_cast<GLintptr>(offset), static_cast<GLsizeiptr>(size), data);
	}

	inline FramebufferStatus CheckFramebufferStatus(FramebufferType target) {
		return static_cast<FramebufferStatus>(glCheckFramebufferStatus(static_cast<GLenum>(target)));
	}

	inline void Clear(gl::BufferSelectBit mask) {
		glClear(static_cast<GLbitfield>(mask));
	}

	inline void ClearColor(rgbaf c) {
		glClearColor(static_cast<GLfloat>(c[0]), static_cast<GLfloat>(c[1]), static_cast<GLfloat>(c[2]), static_cast<GLfloat>(c[3]));
	}

	inline GLuint CreateShader(ShaderType type) {
		return glCreateShader(static_cast<GLenum>(type));
	}

	inline void CullFace(CullMode mode) {
		glCullFace(static_cast<GLenum>(mode));
	}

	inline void DepthFunc(CompareFunc func) {
		glDepthFunc(static_cast<GLenum>(func));
	}

	inline void Disable(Capability cap) {
		glDisable(static_cast<GLenum>(cap));
	}

	inline void DrawArrays(BasicPrimitiveType mode, size_t first, size_t count) {
		glDrawArrays(static_cast<GLenum>(mode), static_cast<GLint>(first), static_cast<GLsizei>(count));
	}

	inline void DrawElements(BasicPrimitiveType mode, size_t count, IndexType type = IndexType::UnsignedInt, const void* indices = nullptr) {
		glDrawElements(static_cast<GLenum>(mode), static_cast<GLint>(count), static_cast<GLenum>(type), indices);
	}

	inline void Enable(Capability cap) {
		glEnable(static_cast<GLenum>(cap));
	}

	inline void FramebufferRenderbuffer(FramebufferType target, FramebufferAttachment attachment, GLuint renderbuffer) {
		glFramebufferRenderbuffer(static_cast<GLenum>(target), static_cast<GLenum>(attachment), GL_RENDERBUFFER, renderbuffer);
	}

	inline void FramebufferTexture2D(FramebufferType target, FramebufferAttachment attachment, GLenum textarget, GLuint texture, GLint level) {
		glFramebufferTexture2D(static_cast<GLenum>(target), static_cast<GLenum>(attachment), textarget, texture, level);
	}

	inline void FrontFace(FaceOrientation mode) {
		glFrontFace(static_cast<GLenum>(mode));
	}

	inline void GenerateMipmap(TextureType target) {
		glGenerateMipmap(static_cast<GLenum>(target));
	}

	inline void GetProgramiv(GLuint program, ProgramParam pname, GLint* params) {
		glGetProgramiv(program, static_cast<GLenum>(pname), params);
	}

	inline void GetShaderiv(GLuint shader, ShaderParam pname, GLint* params) {
		glGetShaderiv(shader, static_cast<GLenum>(pname), params);
	}

	inline void ReadPixels(GLint x, GLint y, size_t width, size_t height, PixelDataFormat format, PixelDataType type, void* pixels) {
		glReadPixels(x, y, static_cast<GLsizei>(width), static_cast<GLsizei>(height), static_cast<GLenum>(format), static_cast<GLenum>(type), pixels);
	}

	inline void RenderbufferStorage(FramebufferInternalFormat internalformat, size_t width, size_t height) {
		glRenderbufferStorage(GL_RENDERBUFFER, static_cast<GLenum>(internalformat), static_cast<GLsizei>(width), static_cast<GLsizei>(height));
	}

	inline void StencilFunc(CompareFunc func, GLint ref, GLuint mask) {
		glStencilFunc(static_cast<GLenum>(func), ref, mask);
	}

	inline void StencilOp(StencilOperation fail, StencilOperation zfail, StencilOperation zpass) {
		glStencilOp(static_cast<GLenum>(fail), static_cast<GLenum>(zfail), static_cast<GLenum>(zpass));
	}

	// border must be 0
	inline void TexImage2D(TextureTarget target, GLint level, PixelDataInternalFormat internalformat, size_t width, size_t height, PixelDataFormat format, PixelDataType type, const void* pixels) {
		glTexImage2D(static_cast<GLenum>(target), level, static_cast<GLint>(internalformat), static_cast<GLsizei>(width), static_cast<GLsizei>(height), 0, static_cast<GLenum>(format), static_cast<GLenum>(type), pixels);
	}

	inline void TexParameteri(TextureType target, TextureParam pname, GLint param) {
		glTexParameteri(static_cast<GLenum>(target), static_cast<GLenum>(pname), param);
	}

	inline void VertexAttribPointer(size_t index, size_t size, DataType type, GLboolean normalized, size_t stride, size_t offset = 0) {
		assert(size > 0 && size <= 4);
		glVertexAttribPointer(static_cast<GLuint>(index), static_cast<GLint>(size), static_cast<GLenum>(type), normalized, static_cast<GLsizei>(stride), reinterpret_cast<void*>(offset));
	}

	inline void Viewport(pointi2 xy, size_t width, size_t height) {
		glViewport(static_cast<GLint>(xy[0]), static_cast<GLint>(xy[1]), static_cast<GLsizei>(width), static_cast<GLsizei>(height));
	}

	// ================================ original ================================

	/*inline void CullFace(GLenum mode) {
		glCullFace(mode);
	}*/
	/*inline void FrontFace(GLenum mode) {
		glFrontFace(mode);
	}*/
	inline void Hint(GLenum target, GLenum mode) {
		glHint(target, mode);
	}
	inline void LineWidth(GLfloat width) {
		glLineWidth(width);
	}
	inline void PointSize(GLfloat size) {
		glPointSize(size);
	}
	inline void PolygonMode(GLenum face, GLenum mode) {
		glPolygonMode(face, mode);
	}
	inline void Scissor(GLint x, GLint y, GLsizei width, GLsizei height) {
		glScissor(x, y, width, height);
	}
	inline void TexParameterf(GLenum target, GLenum pname, GLfloat param) {
		glTexParameterf(target, pname, param);
	}
	inline void TexParameterfv(GLenum target, GLenum pname, const GLfloat* params) {
		glTexParameterfv(target, pname, params);
	}
	/*inline void TexParameteri(GLenum target, GLenum pname, GLint param) {
		glTexParameteri(target, pname, param);
	}*/
	inline void TexParameteriv(GLenum target, GLenum pname, const GLint* params) {
		glTexParameteriv(target, pname, params);
	}
	inline void TexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void* pixels) {
		glTexImage1D(target, level, internalformat, width, border, format, type, pixels);
	}
	/*inline void TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels) {
		glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
	}*/
	inline void DrawBuffer(GLenum buf) {
		glDrawBuffer(buf);
	}
	/*inline void Clear(GLbitfield mask) {
		glClear(mask);
	}*/
	/*inline void ClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
		glClearColor(red, green, blue, alpha);
	}*/
	inline void ClearStencil(GLint s) {
		glClearStencil(s);
	}
	inline void ClearDepth(GLdouble depth) {
		glClearDepth(depth);
	}
	inline void StencilMask(GLuint mask) {
		glStencilMask(mask);
	}
	inline void ColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) {
		glColorMask(red, green, blue, alpha);
	}
	inline void DepthMask(GLboolean flag) {
		glDepthMask(flag);
	}
	/*inline void Disable(GLenum cap) {
		glDisable(cap);
	}
	inline void Enable(GLenum cap) {
		glEnable(cap);
	}*/
	inline void Finish(void) {
		glFinish();
	}
	inline void Flush(void) {
		glFlush();
	}
	/*inline void BlendFunc(GLenum sfactor, GLenum dfactor) {
		glBlendFunc(sfactor, dfactor);
	}*/
	inline void LogicOp(GLenum opcode) {
		glLogicOp(opcode);
	}
	/*inline void StencilFunc(GLenum func, GLint ref, GLuint mask) {
		glStencilFunc(func, ref, mask);
	}*/
	/*inline void StencilOp(GLenum fail, GLenum zfail, GLenum zpass) {
		glStencilOp(fail, zfail, zpass);
	}*/
	/*inline void DepthFunc(GLenum func) {
		glDepthFunc(func);
	}*/
	inline void PixelStoref(GLenum pname, GLfloat param) {
		glPixelStoref(pname, param);
	}
	inline void PixelStorei(GLenum pname, GLint param) {
		glPixelStorei(pname, param);
	}
	inline void ReadBuffer(GLenum src) {
		glReadBuffer(src);
	}
	/*inline void ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels) {
		glReadPixels(x, y, width, height, format, type, pixels);
	}*/
	inline void GetBooleanv(GLenum pname, GLboolean* data) {
		glGetBooleanv(pname, data);
	}
	inline void GetDoublev(GLenum pname, GLdouble* data) {
		glGetDoublev(pname, data);
	}
	inline GLenum GetError(void) {
		return glGetError();
	}
	inline void GetFloatv(GLenum pname, GLfloat* data) {
		glGetFloatv(pname, data);
	}
	inline void GetIntegerv(GLenum pname, GLint* data) {
		glGetIntegerv(pname, data);
	}
	inline const GLubyte* GetString(GLenum name) {
		return glGetString(name);
	}
	inline void GetTexImage(GLenum target, GLint level, GLenum format, GLenum type, void* pixels) {
		glGetTexImage(target, level, format, type, pixels);
	}
	inline void GetTexParameterfv(GLenum target, GLenum pname, GLfloat* params) {
		glGetTexParameterfv(target, pname, params);
	}
	inline void GetTexParameteriv(GLenum target, GLenum pname, GLint* params) {
		glGetTexParameteriv(target, pname, params);
	}
	inline void GetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat* params) {
		glGetTexLevelParameterfv(target, level, pname, params);
	}
	inline void GetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint* params) {
		glGetTexLevelParameteriv(target, level, pname, params);
	}
	inline GLboolean IsEnabled(GLenum cap) {
		return glIsEnabled(cap);
	}
	inline void DepthRange(GLdouble n, GLdouble f) {
		glDepthRange(n, f);
	}
	/*inline void Viewport(GLint x, GLint y, GLsizei width, GLsizei height) {
		glViewport(x, y, width, height);
	}*/

#ifdef GL_VERSION_1_1
	/*inline void DrawArrays(GLenum mode, GLint first, GLsizei count) {
		glDrawArrays(mode, first, count);
	}*/
	/*inline void DrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices) {
		glDrawElements(mode, count, type, indices);
	}*/
	inline void PolygonOffset(GLfloat factor, GLfloat units) {
		glPolygonOffset(factor, units);
	}
	inline void CopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border) {
		glCopyTexImage1D(target, level, internalformat, x, y, width, border);
	}
	inline void CopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) {
		glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
	}
	inline void CopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) {
		glCopyTexSubImage1D(target, level, xoffset, x, y, width);
	}
	inline void CopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
		glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
	}
	inline void TexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels) {
		glTexSubImage1D(target, level, xoffset, width, format, type, pixels);
	}
	inline void TexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels) {
		glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
	}
	/*inline void BindTexture(GLenum target, GLuint texture) {
		glBindTexture(target, texture);
	}*/
	inline void DeleteTextures(GLsizei n, const GLuint* textures) {
		glDeleteTextures(n, textures);
	}
	inline void GenTextures(GLsizei n, GLuint* textures) {
		glGenTextures(n, textures);
	}
	inline GLboolean IsTexture(GLuint texture) {
		return glIsTexture(texture);
	}
#endif

#ifdef GL_VERSION_1_2
	inline void DrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void* indices) {
		glDrawRangeElements(mode, start, end, count, type, indices);
	}
	inline void TexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void* pixels) {
		glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
	}
	inline void TexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels) {
		glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
	}

	inline void CopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
		glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
	}
#endif

#ifdef GL_VERSION_1_3
	inline void ActiveTexture(GLenum texture) {
		glActiveTexture(texture);
	}
	inline void SampleCoverage(GLfloat value, GLboolean invert) {
		glSampleCoverage(value, invert);
	}
	inline void CompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void* data) {
		glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
	}
	inline void CompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data) {
		glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
	}
	inline void CompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void* data) {
		glCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data);
	}
	inline void CompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data) {
		glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
	}
	inline void CompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data) {
		glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
	}
	inline void CompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data) {
		glCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data);
	}
	inline void GetCompressedTexImage(GLenum target, GLint level, void* img) {
		glGetCompressedTexImage(target, level, img);
	}
#endif

#ifdef GL_VERSION_1_4
	/*inline void BlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha) {
		glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
	}*/
	inline void MultiDrawArrays(GLenum mode, const GLint* first, const GLsizei* count, GLsizei drawcount) {
		glMultiDrawArrays(mode, first, count, drawcount);
	}
	inline void MultiDrawElements(GLenum mode, const GLsizei* count, GLenum type, const void* const* indices, GLsizei drawcount) {
		glMultiDrawElements(mode, count, type, indices, drawcount);
	}
	inline void PointParameterf(GLenum pname, GLfloat param) {
		glPointParameterf(pname, param);
	}
	inline void PointParameterfv(GLenum pname, const GLfloat* params) {
		glPointParameterfv(pname, params);
	}
	inline void PointParameteri(GLenum pname, GLint param) {
		glPointParameteri(pname, param);
	}
	inline void PointParameteriv(GLenum pname, const GLint* params) {
		glPointParameteriv(pname, params);
	}
	/*inline void BlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
		glBlendColor(red, green, blue, alpha);
	}*/
	/*inline void BlendEquation(GLenum mode) {
		glBlendEquation(mode);
	}*/
#endif

#ifdef GL_VERSION_1_5
	inline void GenQueries(GLsizei n, GLuint* ids) {
		glGenQueries(n, ids);
	}
	inline void DeleteQueries(GLsizei n, const GLuint* ids) {
		glDeleteQueries(n, ids);
	}
	inline GLboolean IsQuery(GLuint id) {
		return glIsQuery(id);
	}
	inline void BeginQuery(GLenum target, GLuint id) {
		glBeginQuery(target, id);
	}
	inline void EndQuery(GLenum target) {
		glEndQuery(target);
	}
	inline void GetQueryiv(GLenum target, GLenum pname, GLint* params) {
		glGetQueryiv(target, pname, params);
	}
	inline void GetQueryObjectiv(GLuint id, GLenum pname, GLint* params) {
		glGetQueryObjectiv(id, pname, params);
	}
	inline void GetQueryObjectuiv(GLuint id, GLenum pname, GLuint* params) {
		glGetQueryObjectuiv(id, pname, params);
	}
	/*inline void BindBuffer(GLenum target, GLuint buffer) {
		glBindBuffer(target, buffer);
	}*/
	inline void DeleteBuffers(GLsizei n, const GLuint* buffers) {
		glDeleteBuffers(n, buffers);
	}
	inline void GenBuffers(GLsizei n, GLuint* buffers) {
		glGenBuffers(n, buffers);
	}
	inline GLboolean IsBuffer(GLuint buffer) {
		return glIsBuffer(buffer);
	}
	//inline void BufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage) {
	//	glBufferData(target, size, data, usage);
	//}
	/*inline void BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void* data) {
		glBufferSubData(target, offset, size, data);
	}*/
	inline void GetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, void* data) {
		glGetBufferSubData(target, offset, size, data);
	}
	inline void* MapBuffer(GLenum target, GLenum access) {
		glMapBuffer(target, access);
	}
	inline GLboolean UnmapBuffer(GLenum target) {
		return glUnmapBuffer(target);
	}
	inline void GetBufferParameteriv(GLenum target, GLenum pname, GLint* params) {
		glGetBufferParameteriv(target, pname, params);
	}
	inline void GetBufferPointerv(GLenum target, GLenum pname, void** params) {
		glGetBufferPointerv(target, pname, params);
	}
#endif

#ifdef GL_VERSION_2_0
	inline void BlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha) {
		glBlendEquationSeparate(modeRGB, modeAlpha);
	}
	inline void DrawBuffers(GLsizei n, const GLenum* bufs) {
		glDrawBuffers(n, bufs);
	}
	inline void StencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass) {
		glStencilOpSeparate(face, sfail, dpfail, dppass);
	}
	inline void StencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask) {
		glStencilFuncSeparate(face, func, ref, mask);
	}
	inline void StencilMaskSeparate(GLenum face, GLuint mask) {
		glStencilMaskSeparate(face, mask);
	}
	inline void AttachShader(GLuint program, GLuint shader) {
		glAttachShader(program, shader);
	}
	inline void BindAttribLocation(GLuint program, GLuint index, const GLchar* name) {
		glBindAttribLocation(program, index, name);
	}
	inline void CompileShader(GLuint shader) {
		glCompileShader(shader);
	}
	inline GLuint CreateProgram(void) {
		return glCreateProgram();
	}
	/*inline GLuint CreateShader(GLenum type) {
		return glCreateShader(type);
	}*/
	inline void DeleteProgram(GLuint program) {
		glDeleteProgram(program);
	}
	inline void DeleteShader(GLuint shader) {
		glDeleteShader(shader);
	}
	inline void DetachShader(GLuint program, GLuint shader) {
		glDetachShader(program, shader);
	}
	inline void DisableVertexAttribArray(GLuint index) {
		glDisableVertexAttribArray(index);
	}
	inline void EnableVertexAttribArray(size_t index) {
		glEnableVertexAttribArray(static_cast<GLuint>(index));
	}
	inline void GetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name) {
		glGetActiveAttrib(program, index, bufSize, length, size, type, name);
	}
	inline void GetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name) {
		glGetActiveUniform(program, index, bufSize, length, size, type, name);
	}
	inline void GetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei* count, GLuint* shaders) {
		glGetAttachedShaders(program, maxCount, count, shaders);
	}
	inline GLint GetAttribLocation(GLuint program, const GLchar* name) {
		return glGetAttribLocation(program, name);
	}
	/*inline void GetProgramiv(GLuint program, GLenum pname, GLint* params) {
		glGetProgramiv(program, pname, params);
	}*/
	inline void GetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog) {
		glGetProgramInfoLog(program, bufSize, length, infoLog);
	}
	/*inline void GetShaderiv(GLuint shader, GLenum pname, GLint* params) {
		glGetShaderiv(shader, pname, params);
	}*/
	inline void GetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog) {
		glGetShaderInfoLog(shader, bufSize, length, infoLog);
	}
	inline void GetShaderSource(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* source) {
		glGetShaderSource(shader, bufSize, length, source);
	}
	inline GLint GetUniformLocation(GLuint program, const GLchar* name) {
		return glGetUniformLocation(program, name);
	}
	inline void GetUniformfv(GLuint program, GLint location, GLfloat* params) {
		glGetUniformfv(program, location, params);
	}
	inline void GetUniformiv(GLuint program, GLint location, GLint* params) {
		glGetUniformiv(program, location, params);
	}
	inline void GetVertexAttribdv(GLuint index, GLenum pname, GLdouble* params) {
		glGetVertexAttribdv(index, pname, params);
	}
	inline void GetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params) {
		glGetVertexAttribfv(index, pname, params);
	}
	inline void GetVertexAttribiv(GLuint index, GLenum pname, GLint* params) {
		glGetVertexAttribiv(index, pname, params);
	}
	inline void GetVertexAttribPointerv(GLuint index, GLenum pname, void** pointer) {
		glGetVertexAttribPointerv(index, pname, pointer);
	}
	inline GLboolean IsProgram(GLuint program) {
		return glIsProgram(program);
	}
	inline GLboolean IsShader(GLuint shader) {
		return glIsShader(shader);
	}
	inline void LinkProgram(GLuint program) {
		glLinkProgram(program);
	}
	inline void ShaderSource(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length) {
		glShaderSource(shader, count, string, length);
	}
	inline void UseProgram(GLuint program) {
		glUseProgram(program);
	}
	inline void Uniform1f(GLint location, GLfloat v0) {
		glUniform1f(location, v0);
	}
	inline void Uniform2f(GLint location, GLfloat v0, GLfloat v1) {
		glUniform2f(location, v0, v1);
	}
	inline void Uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) {
		glUniform3f(location, v0, v1, v2);
	}
	inline void Uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
		glUniform4f(location, v0, v1, v2, v3);
	}
	inline void Uniform1i(GLint location, GLint v0) {
		glUniform1i(location, v0);
	}
	inline void Uniform2i(GLint location, GLint v0, GLint v1) {
		glUniform2i(location, v0, v1);
	}
	inline void Uniform3i(GLint location, GLint v0, GLint v1, GLint v2) {
		glUniform3i(location, v0, v1, v2);
	}
	inline void Uniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) {
		glUniform4i(location, v0, v1, v2, v3);
	}
	inline void Uniform1fv(GLint location, GLsizei count, const GLfloat* value) {
		glUniform1fv(location, count, value);
	}
	inline void Uniform2fv(GLint location, GLsizei count, const GLfloat* value) {
		glUniform2fv(location, count, value);
	}
	inline void Uniform3fv(GLint location, GLsizei count, const GLfloat* value) {
		glUniform3fv(location, count, value);
	}
	inline void Uniform4fv(GLint location, GLsizei count, const GLfloat* value) {
		glUniform4fv(location, count, value);
	}
	inline void Uniform1iv(GLint location, GLsizei count, const GLint* value) {
		glUniform1iv(location, count, value);
	}
	inline void Uniform2iv(GLint location, GLsizei count, const GLint* value) {
		glUniform2iv(location, count, value);
	}
	inline void Uniform3iv(GLint location, GLsizei count, const GLint* value) {
		glUniform3iv(location, count, value);
	}
	inline void Uniform4iv(GLint location, GLsizei count, const GLint* value) {
		glUniform4iv(location, count, value);
	}
	inline void UniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
		glUniformMatrix2fv(location, count, transpose, value);
	}
	inline void UniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
		glUniformMatrix3fv(location, count, transpose, value);
	}
	inline void UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
		glUniformMatrix4fv(location, count, transpose, value);
	}
	inline void ValidateProgram(GLuint program) {
		glValidateProgram(program);
	}
	inline void VertexAttrib1d(GLuint index, GLdouble x) {
		glVertexAttrib1d(index, x);
	}
	inline void VertexAttrib1dv(GLuint index, const GLdouble* v) {
		glVertexAttrib1dv(index, v);
	}
	inline void VertexAttrib1f(GLuint index, GLfloat x) {
		glVertexAttrib1f(index, x);
	}
	inline void VertexAttrib1fv(GLuint index, const GLfloat* v) {
		glVertexAttrib1fv(index, v);
	}
	inline void VertexAttrib1s(GLuint index, GLshort x) {
		glVertexAttrib1s(index, x);
	}
	inline void VertexAttrib1sv(GLuint index, const GLshort* v) {
		glVertexAttrib1sv(index, v);
	}
	inline void VertexAttrib2d(GLuint index, GLdouble x, GLdouble y) {
		glVertexAttrib2d(index, x, y);
	}
	inline void VertexAttrib2dv(GLuint index, const GLdouble* v) {
		glVertexAttrib2dv(index, v);
	}
	inline void VertexAttrib2f(GLuint index, GLfloat x, GLfloat y) {
		glVertexAttrib2f(index, x, y);
	}
	inline void VertexAttrib2fv(GLuint index, const GLfloat* v) {
		glVertexAttrib2fv(index, v);
	}
	inline void VertexAttrib2s(GLuint index, GLshort x, GLshort y) {
		glVertexAttrib2s(index, x, y);
	}
	inline void VertexAttrib2sv(GLuint index, const GLshort* v) {
		glVertexAttrib2sv(index, v);
	}
	inline void VertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z) {
		glVertexAttrib3d(index, x, y, z);
	}
	inline void VertexAttrib3dv(GLuint index, const GLdouble* v) {
		glVertexAttrib3dv(index, v);
	}
	inline void VertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z) {
		glVertexAttrib3f(index, x, y, z);
	}
	inline void VertexAttrib3fv(GLuint index, const GLfloat* v) {
		glVertexAttrib3fv(index, v);
	}
	inline void VertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z) {
		glVertexAttrib3s(index, x, y, z);
	}
	inline void VertexAttrib3sv(GLuint index, const GLshort* v) {
		glVertexAttrib3sv(index, v);
	}
	inline void VertexAttrib4Nbv(GLuint index, const GLbyte* v) {
		glVertexAttrib4Nbv(index, v);
	}
	inline void VertexAttrib4Niv(GLuint index, const GLint* v) {
		glVertexAttrib4Niv(index, v);
	}
	inline void VertexAttrib4Nsv(GLuint index, const GLshort* v) {
		glVertexAttrib4Nsv(index, v);
	}
	inline void VertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w) {
		glVertexAttrib4Nub(index, x, y, z, w);
	}
	inline void VertexAttrib4Nubv(GLuint index, const GLubyte* v) {
		glVertexAttrib4Nubv(index, v);
	}
	inline void VertexAttrib4Nuiv(GLuint index, const GLuint* v) {
		glVertexAttrib4Nuiv(index, v);
	}
	inline void VertexAttrib4Nusv(GLuint index, const GLushort* v) {
		glVertexAttrib4Nusv(index, v);
	}
	inline void VertexAttrib4bv(GLuint index, const GLbyte* v) {
		glVertexAttrib4bv(index, v);
	}
	inline void VertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
		glVertexAttrib4d(index, x, y, z, w);
	}
	inline void VertexAttrib4dv(GLuint index, const GLdouble* v) {
		glVertexAttrib4dv(index, v);
	}
	inline void VertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
		glVertexAttrib4f(index, x, y, z, w);
	}
	inline void VertexAttrib4fv(GLuint index, const GLfloat* v) {
		glVertexAttrib4fv(index, v);
	}
	inline void VertexAttrib4iv(GLuint index, const GLint* v) {
		glVertexAttrib4iv(index, v);
	}
	inline void VertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w) {
		glVertexAttrib4s(index, x, y, z, w);
	}
	inline void VertexAttrib4sv(GLuint index, const GLshort* v) {
		glVertexAttrib4sv(index, v);
	}
	inline void VertexAttrib4ubv(GLuint index, const GLubyte* v) {
		glVertexAttrib4ubv(index, v);
	}
	inline void VertexAttrib4uiv(GLuint index, const GLuint* v) {
		glVertexAttrib4uiv(index, v);
	}
	inline void VertexAttrib4usv(GLuint index, const GLushort* v) {
		glVertexAttrib4usv(index, v);
	}
	/*inline void VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) {
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	}*/
#endif

#ifdef GL_VERSION_2_1
	inline void UniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
		glUniformMatrix2x3fv(location, count, transpose, value);
	}
	inline void UniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
		glUniformMatrix3x2fv(location, count, transpose, value);
	}
	inline void UniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
		glUniformMatrix2x4fv(location, count, transpose, value);
	}
	inline void UniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
		glUniformMatrix4x2fv(location, count, transpose, value);
	}
	inline void UniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
		glUniformMatrix3x4fv(location, count, transpose, value);
	}
	inline void UniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
		glUniformMatrix4x3fv(location, count, transpose, value);
	}
#endif

#ifdef GL_VERSION_3_0
	inline void ColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a) {
		glColorMaski(index, r, g, b, a);
	}
	inline void GetBooleani_v(GLenum target, GLuint index, GLboolean* data) {
		glGetBooleani_v(target, index, data);
	}
	inline void GetIntegeri_v(GLenum target, GLuint index, GLint* data) {
		glGetIntegeri_v(target, index, data);
	}
	inline void Enablei(GLenum target, GLuint index) {
		glEnablei(target, index);
	}
	inline void Disablei(GLenum target, GLuint index) {
		glDisablei(target, index);
	}
	inline GLboolean IsEnabledi(GLenum target, GLuint index) {
		return glIsEnabledi(target, index);
	}
	inline void BeginTransformFeedback(GLenum primitiveMode) {
		glBeginTransformFeedback(primitiveMode);
	}
	inline void EndTransformFeedback(void) {
		glEndTransformFeedback();
	}
	inline void BindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) {
		glBindBufferRange(target, index, buffer, offset, size);
	}
	inline void BindBufferBase(GLenum target, GLuint index, GLuint buffer) {
		glBindBufferBase(target, index, buffer);
	}
	inline void TransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar* const* varyings, GLenum bufferMode) {
		glTransformFeedbackVaryings(program, count, varyings, bufferMode);
	}
	inline void GetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, GLchar* name) {
		glGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
	}
	inline void ClampColor(GLenum target, GLenum clamp) {
		glClampColor(target, clamp);
	}
	inline void BeginConditionalRender(GLuint id, GLenum mode) {
		glBeginConditionalRender(id, mode);
	}
	inline void EndConditionalRender(void) {
		glEndConditionalRender();
	}
	inline void VertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer) {
		glVertexAttribIPointer(index, size, type, stride, pointer);
	}
	inline void GetVertexAttribIiv(GLuint index, GLenum pname, GLint* params) {
		glGetVertexAttribIiv(index, pname, params);
	}
	inline void GetVertexAttribIuiv(GLuint index, GLenum pname, GLuint* params) {
		glGetVertexAttribIuiv(index, pname, params);
	}
	inline void VertexAttribI1i(GLuint index, GLint x) {
		glVertexAttribI1i(index, x);
	}
	inline void VertexAttribI2i(GLuint index, GLint x, GLint y) {
		glVertexAttribI2i(index, x, y);
	}
	inline void VertexAttribI3i(GLuint index, GLint x, GLint y, GLint z) {
		glVertexAttribI3i(index, x, y, z);
	}
	inline void VertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w) {
		glVertexAttribI4i(index, x, y, z, w);
	}
	inline void VertexAttribI1ui(GLuint index, GLuint x) {
		glVertexAttribI1ui(index, x);
	}
	inline void VertexAttribI2ui(GLuint index, GLuint x, GLuint y) {
		glVertexAttribI2ui(index, x, y);
	}
	inline void VertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z) {
		glVertexAttribI3ui(index, x, y, z);
	}
	inline void VertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) {
		glVertexAttribI4ui(index, x, y, z, w);
	}
	inline void VertexAttribI1iv(GLuint index, const GLint* v) {
		glVertexAttribI1iv(index, v);
	}
	inline void VertexAttribI2iv(GLuint index, const GLint* v) {
		glVertexAttribI2iv(index, v);
	}
	inline void VertexAttribI3iv(GLuint index, const GLint* v) {
		glVertexAttribI3iv(index, v);
	}
	inline void VertexAttribI4iv(GLuint index, const GLint* v) {
		glVertexAttribI4iv(index, v);
	}
	inline void VertexAttribI1uiv(GLuint index, const GLuint* v) {
		glVertexAttribI1uiv(index, v);
	}
	inline void VertexAttribI2uiv(GLuint index, const GLuint* v) {
		glVertexAttribI2uiv(index, v);
	}
	inline void VertexAttribI3uiv(GLuint index, const GLuint* v) {
		glVertexAttribI3uiv(index, v);
	}
	inline void VertexAttribI4uiv(GLuint index, const GLuint* v) {
		glVertexAttribI4uiv(index, v);
	}
	inline void VertexAttribI4bv(GLuint index, const GLbyte* v) {
		glVertexAttribI4bv(index, v);
	}
	inline void VertexAttribI4sv(GLuint index, const GLshort* v) {
		glVertexAttribI4sv(index, v);
	}
	inline void VertexAttribI4ubv(GLuint index, const GLubyte* v) {
		glVertexAttribI4ubv(index, v);
	}
	inline void VertexAttribI4usv(GLuint index, const GLushort* v) {
		glVertexAttribI4usv(index, v);
	}
	inline void GetUniformuiv(GLuint program, GLint location, GLuint* params) {
		glGetUniformuiv(program, location, params);
	}
	inline void BindFragDataLocation(GLuint program, GLuint color, const GLchar* name) {
		glBindFragDataLocation(program, color, name);
	}
	inline GLint GetFragDataLocation(GLuint program, const GLchar* name) {
		return glGetFragDataLocation(program, name);
	}
	inline void Uniform1ui(GLint location, GLuint v0) {
		glUniform1ui(location, v0);
	}
	inline void Uniform2ui(GLint location, GLuint v0, GLuint v1) {
		glUniform2ui(location, v0, v1);
	}
	inline void Uniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2) {
		glUniform3ui(location, v0, v1, v2);
	}
	inline void Uniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) {
		glUniform4ui(location, v0, v1, v2, v3);
	}
	inline void Uniform1uiv(GLint location, GLsizei count, const GLuint* value) {
		glUniform1uiv(location, count, value);
	}
	inline void Uniform2uiv(GLint location, GLsizei count, const GLuint* value) {
		glUniform2uiv(location, count, value);
	}
	inline void Uniform3uiv(GLint location, GLsizei count, const GLuint* value) {
		glUniform3uiv(location, count, value);
	}
	inline void Uniform4uiv(GLint location, GLsizei count, const GLuint* value) {
		glUniform4uiv(location, count, value);
	}
	inline void TexParameterIiv(GLenum target, GLenum pname, const GLint* params) {
		glTexParameterIiv(target, pname, params);
	}
	inline void TexParameterIuiv(GLenum target, GLenum pname, const GLuint* params) {
		glTexParameterIuiv(target, pname, params);
	}
	inline void GetTexParameterIiv(GLenum target, GLenum pname, GLint* params) {
		glGetTexParameterIiv(target, pname, params);
	}
	inline void GetTexParameterIuiv(GLenum target, GLenum pname, GLuint* params) {
		glGetTexParameterIuiv(target, pname, params);
	}
	inline void ClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint* value) {
		glClearBufferiv(buffer, drawbuffer, value);
	}
	inline void ClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint* value) {
		glClearBufferuiv(buffer, drawbuffer, value);
	}
	inline void ClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat* value) {
		glClearBufferfv(buffer, drawbuffer, value);
	}
	inline void ClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil) {
		glClearBufferfi(buffer, drawbuffer, depth, stencil);
	}
	inline const GLubyte* GetStringi(GLenum name, GLuint index) {
		return glGetStringi(name, index);
	}
	inline GLboolean IsRenderbuffer(GLuint renderbuffer) {
		return glIsRenderbuffer(renderbuffer);
	}
	/*inline void BindRenderbuffer(GLenum target, GLuint renderbuffer) {
		glBindRenderbuffer(target, renderbuffer);
	}*/
	inline void DeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers) {
		glDeleteRenderbuffers(n, renderbuffers);
	}
	inline void GenRenderbuffers(GLsizei n, GLuint* renderbuffers) {
		glGenRenderbuffers(n, renderbuffers);
	}
	/*inline void RenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height) {
		glRenderbufferStorage(target, internalformat, width, height);
	}*/
	inline void GetRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params) {
		glGetRenderbufferParameteriv(target, pname, params);
	}
	inline GLboolean IsFramebuffer(GLuint framebuffer) {
		return glIsFramebuffer(framebuffer);
	}
	/*inline void BindFramebuffer(GLenum target, GLuint framebuffer) {
		glBindFramebuffer(target, framebuffer);
	}*/
	inline void DeleteFramebuffers(GLsizei n, const GLuint* framebuffers) {
		glDeleteFramebuffers(n, framebuffers);
	}
	inline void GenFramebuffers(GLsizei n, GLuint* framebuffers) {
		glGenFramebuffers(n, framebuffers);
	}
	/*inline GLenum CheckFramebufferStatus(GLenum target) {
		return glCheckFramebufferStatus(target);
	}*/
	inline void FramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
		glFramebufferTexture1D(target, attachment, textarget, texture, level);
	}
	/*inline void FramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
		glFramebufferTexture2D(target, attachment, textarget, texture, level);
	}*/
	inline void FramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset) {
		glFramebufferTexture3D(target, attachment, textarget, texture, level, zoffset);
	}
	/*inline void FramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) {
		glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
	}*/
	inline void GetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params) {
		glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
	}
	/*inline void GenerateMipmap(GLenum target) {
		glGenerateMipmap(target);
	}*/
	inline void BlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) {
		glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
	}
	inline void RenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) {
		glRenderbufferStorageMultisample(target, samples, internalformat, width, height);
	}
	inline void FramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer) {
		glFramebufferTextureLayer(target, attachment, texture, level, layer);
	}
	inline void* MapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access) {
		glMapBufferRange(target, offset, length, access);
	}
	inline void FlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length) {
		glFlushMappedBufferRange(target, offset, length);
	}
	inline void BindVertexArray(GLuint array) {
		glBindVertexArray(array);
	}
	inline void DeleteVertexArrays(GLsizei n, const GLuint* arrays) {
		glDeleteVertexArrays(n, arrays);
	}
	inline void GenVertexArrays(GLsizei n, GLuint* arrays) {
		glGenVertexArrays(n, arrays);
	}
	inline GLboolean IsVertexArray(GLuint array) {
		return glIsVertexArray(array);
	}
#endif

#ifdef GL_VERSION_3_1
	inline void DrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount) {
		glDrawArraysInstanced(mode, first, count, instancecount);
	}
	inline void DrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount) {
		glDrawElementsInstanced(mode, count, type, indices, instancecount);
	}
	inline void TexBuffer(GLenum target, GLenum internalformat, GLuint buffer) {
		glTexBuffer(target, internalformat, buffer);
	}
	inline void PrimitiveRestartIndex(GLuint index) {
		glPrimitiveRestartIndex(index);
	}
	inline void CopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) {
		glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
	}
	inline void GetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar* const* uniformNames, GLuint* uniformIndices) {
		glGetUniformIndices(program, uniformCount, uniformNames, uniformIndices);
	}
	inline void GetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint* uniformIndices, GLenum pname, GLint* params) {
		glGetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params);
	}
	inline void GetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformName) {
		glGetActiveUniformName(program, uniformIndex, bufSize, length, uniformName);
	}
	inline GLuint GetUniformBlockIndex(GLuint program, const GLchar* uniformBlockName) {
		return glGetUniformBlockIndex(program, uniformBlockName);
	}
	inline void GetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params) {
		glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);
	}
	inline void GetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName) {
		glGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName);
	}
	inline void UniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding) {
		glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
	}
#endif

#ifdef GL_VERSION_3_2
	inline void DrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, const void* indices, GLint basevertex) {
		glDrawElementsBaseVertex(mode, count, type, indices, basevertex);
	}
	inline void DrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void* indices, GLint basevertex) {
		glDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);
	}
	inline void DrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount, GLint basevertex) {
		glDrawElementsInstancedBaseVertex(mode, count, type, indices, instancecount, basevertex);
	}
	inline void MultiDrawElementsBaseVertex(GLenum mode, const GLsizei* count, GLenum type, const void* const* indices, GLsizei drawcount, const GLint* basevertex) {
		glMultiDrawElementsBaseVertex(mode, count, type, indices, drawcount, basevertex);
	}
	inline void ProvokingVertex(GLenum mode) {
		glProvokingVertex(mode);
	}
	inline GLsync FenceSync(GLenum condition, GLbitfield flags) {
		return glFenceSync(condition, flags);
	}
	inline GLboolean IsSync(GLsync sync) {
		return glIsSync(sync);
	}
	inline void DeleteSync(GLsync sync) {
		glDeleteSync(sync);
	}
	inline GLenum ClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout) {
		return glClientWaitSync(sync, flags, timeout);
	}
	inline void WaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout) {
		glWaitSync(sync, flags, timeout);
	}
	inline void GetInteger64v(GLenum pname, GLint64* data) {
		glGetInteger64v(pname, data);
	}
	inline void GetSynciv(GLsync sync, GLenum pname, GLsizei count, GLsizei* length, GLint* values) {
		glGetSynciv(sync, pname, count, length, values);
	}
	inline void GetInteger64i_v(GLenum target, GLuint index, GLint64* data) {
		glGetInteger64i_v(target, index, data);
	}
	inline void GetBufferParameteri64v(GLenum target, GLenum pname, GLint64* params) {
		glGetBufferParameteri64v(target, pname, params);
	}
	inline void FramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level) {
		glFramebufferTexture(target, attachment, texture, level);
	}
	inline void TexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) {
		glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
	}
	inline void TexImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) {
		glTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
	}
	inline void GetMultisamplefv(GLenum pname, GLuint index, GLfloat* val) {
		glGetMultisamplefv(pname, index, val);
	}
	inline void SampleMaski(GLuint maskNumber, GLbitfield mask) {
		glSampleMaski(maskNumber, mask);
	}
#endif

#ifdef GL_VERSION_3_3
	inline void BindFragDataLocationIndexed(GLuint program, GLuint colorNumber, GLuint index, const GLchar* name) {
		glBindFragDataLocationIndexed(program, colorNumber, index, name);
	}
	inline GLint GetFragDataIndex(GLuint program, const GLchar* name) {
		return glGetFragDataIndex(program, name);
	}
	inline void GenSamplers(GLsizei count, GLuint* samplers) {
		glGenSamplers(count, samplers);
	}
	inline void DeleteSamplers(GLsizei count, const GLuint* samplers) {
		glDeleteSamplers(count, samplers);
	}
	inline GLboolean IsSampler(GLuint sampler) {
		return glIsSampler(sampler);
	}
	inline void BindSampler(GLuint unit, GLuint sampler) {
		glBindSampler(unit, sampler);
	}
	inline void SamplerParameteri(GLuint sampler, GLenum pname, GLint param) {
		glSamplerParameteri(sampler, pname, param);
	}
	inline void SamplerParameteriv(GLuint sampler, GLenum pname, const GLint* param) {
		glSamplerParameteriv(sampler, pname, param);
	}
	inline void SamplerParameterf(GLuint sampler, GLenum pname, GLfloat param) {
		glSamplerParameterf(sampler, pname, param);
	}
	inline void SamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat* param) {
		glSamplerParameterfv(sampler, pname, param);
	}
	inline void SamplerParameterIiv(GLuint sampler, GLenum pname, const GLint* param) {
		glSamplerParameterIiv(sampler, pname, param);
	}
	inline void SamplerParameterIuiv(GLuint sampler, GLenum pname, const GLuint* param) {
		glSamplerParameterIuiv(sampler, pname, param);
	}
	inline void GetSamplerParameteriv(GLuint sampler, GLenum pname, GLint* params) {
		glGetSamplerParameteriv(sampler, pname, params);
	}
	inline void GetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint* params) {
		glGetSamplerParameterIiv(sampler, pname, params);
	}
	inline void GetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat* params) {
		glGetSamplerParameterfv(sampler, pname, params);
	}
	inline void GetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint* params) {
		glGetSamplerParameterIuiv(sampler, pname, params);
	}
	inline void QueryCounter(GLuint id, GLenum target) {
		glQueryCounter(id, target);
	}
	inline void GetQueryObjecti64v(GLuint id, GLenum pname, GLint64* params) {
		glGetQueryObjecti64v(id, pname, params);
	}
	inline void GetQueryObjectui64v(GLuint id, GLenum pname, GLuint64* params) {
		glGetQueryObjectui64v(id, pname, params);
	}
	inline void VertexAttribDivisor(GLuint index, GLuint divisor) {
		glVertexAttribDivisor(index, divisor);
	}
	inline void VertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) {
		glVertexAttribP1ui(index, type, normalized, value);
	}
	inline void VertexAttribP1uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint* value) {
		glVertexAttribP1uiv(index, type, normalized, value);
	}
	inline void VertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) {
		glVertexAttribP2ui(index, type, normalized, value);
	}
	inline void VertexAttribP2uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint* value) {
		glVertexAttribP2uiv(index, type, normalized, value);
	}
	inline void VertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) {
		glVertexAttribP3ui(index, type, normalized, value);
	}
	inline void VertexAttribP3uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint* value) {
		glVertexAttribP3uiv(index, type, normalized, value);
	}
	inline void VertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) {
		glVertexAttribP4ui(index, type, normalized, value);
	}
	inline void VertexAttribP4uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint* value) {
		glVertexAttribP4uiv(index, type, normalized, value);
	}
	inline void VertexP2ui(GLenum type, GLuint value) {
		glVertexP2ui(type, value);
	}
	inline void VertexP2uiv(GLenum type, const GLuint* value) {
		glVertexP2uiv(type, value);
	}
	inline void VertexP3ui(GLenum type, GLuint value) {
		glVertexP3ui(type, value);
	}
	inline void VertexP3uiv(GLenum type, const GLuint* value) {
		glVertexP3uiv(type, value);
	}
	inline void VertexP4ui(GLenum type, GLuint value) {
		glVertexP4ui(type, value);
	}
	inline void VertexP4uiv(GLenum type, const GLuint* value) {
		glVertexP4uiv(type, value);
	}
	inline void TexCoordP1ui(GLenum type, GLuint coords) {
		glTexCoordP1ui(type, coords);
	}
	inline void TexCoordP1uiv(GLenum type, const GLuint* coords) {
		glTexCoordP1uiv(type, coords);
	}
	inline void TexCoordP2ui(GLenum type, GLuint coords) {
		glTexCoordP2ui(type, coords);
	}
	inline void TexCoordP2uiv(GLenum type, const GLuint* coords) {
		glTexCoordP2uiv(type, coords);
	}
	inline void TexCoordP3ui(GLenum type, GLuint coords) {
		glTexCoordP3ui(type, coords);
	}
	inline void TexCoordP3uiv(GLenum type, const GLuint* coords) {
		glTexCoordP3uiv(type, coords);
	}
	inline void TexCoordP4ui(GLenum type, GLuint coords) {
		glTexCoordP4ui(type, coords);
	}
	inline void TexCoordP4uiv(GLenum type, const GLuint* coords) {
		glTexCoordP4uiv(type, coords);
	}
	inline void MultiTexCoordP1ui(GLenum texture, GLenum type, GLuint coords) {
		glMultiTexCoordP1ui(texture, type, coords);
	}
	inline void MultiTexCoordP1uiv(GLenum texture, GLenum type, const GLuint* coords) {
		glMultiTexCoordP1uiv(texture, type, coords);
	}
	inline void MultiTexCoordP2ui(GLenum texture, GLenum type, GLuint coords) {
		glMultiTexCoordP2ui(texture, type, coords);
	}
	inline void MultiTexCoordP2uiv(GLenum texture, GLenum type, const GLuint* coords) {
		glMultiTexCoordP2uiv(texture, type, coords);
	}
	inline void MultiTexCoordP3ui(GLenum texture, GLenum type, GLuint coords) {
		glMultiTexCoordP3ui(texture, type, coords);
	}
	inline void MultiTexCoordP3uiv(GLenum texture, GLenum type, const GLuint* coords) {
		glMultiTexCoordP3uiv(texture, type, coords);
	}
	inline void MultiTexCoordP4ui(GLenum texture, GLenum type, GLuint coords) {
		glMultiTexCoordP4ui(texture, type, coords);
	}
	inline void MultiTexCoordP4uiv(GLenum texture, GLenum type, const GLuint* coords) {
		glMultiTexCoordP4uiv(texture, type, coords);
	}
	inline void NormalP3ui(GLenum type, GLuint coords) {
		glNormalP3ui(type, coords);
	}
	inline void NormalP3uiv(GLenum type, const GLuint* coords) {
		glNormalP3uiv(type, coords);
	}
	inline void ColorP3ui(GLenum type, GLuint color) {
		glColorP3ui(type, color);
	}
	inline void ColorP3uiv(GLenum type, const GLuint* color) {
		glColorP3uiv(type, color);
	}
	inline void ColorP4ui(GLenum type, GLuint color) {
		glColorP4ui(type, color);
	}
	inline void ColorP4uiv(GLenum type, const GLuint* color) {
		glColorP4uiv(type, color);
	}
	inline void SecondaryColorP3ui(GLenum type, GLuint color) {
		glSecondaryColorP3ui(type, color);
	}
	inline void SecondaryColorP3uiv(GLenum type, const GLuint* color) {
		glSecondaryColorP3uiv(type, color);
	}
#endif
}
