#pragma once

#include "Shader.h"

namespace Ubpa::gl {
	class Texture;
	class UniformBuffer;

	class Program : public Obj {
	public:
		Program(const Shader* vs, const Shader* fs, const Shader* gs = nullptr);
		~Program();

		Program(Program&& p) noexcept;
		Program& operator=(Program&& p) noexcept;

		void Clear();

		void Use() const;
		void Param(ProgramParam pname, GLint* params) const;
		GLint GetUniformLocation(const GLchar* name) const;

		void Active(size_t idx, Texture* tex);

		void SetTex(const GLchar* name, size_t v) const;

		void SetBool(const GLchar* name, GLboolean v) const;
		void SetInt(const GLchar* name, GLint v) const;
		void SetUInt(const GLchar* name, GLuint v) const;
		void SetFloat(const GLchar* name, GLfloat v) const;
		void SetVecf2(const GLchar* name, const val<GLfloat, 2>& v) const;
		void SetVecf3(const GLchar* name, const val<GLfloat, 3>& v) const;
		void SetVecf4(const GLchar* name, const val<GLfloat, 4>& v) const;

		void SetInts(const GLchar* name, GLuint n, const GLint* data) const;
		void SetUInts(const GLchar* name, GLuint n, const GLuint* data) const;
		void SetFloats(const GLchar* name, GLuint n, const GLfloat* data) const;
		void SetVecf2s(const GLchar* name, GLuint n, const GLfloat* data) const;
		void SetVecf3s(const GLchar* name, GLuint n, const GLfloat* data) const;
		void SetVecf4s(const GLchar* name, GLuint n, const GLfloat* data) const;

		void SetMatf4(const GLchar* name, const matf4& mat) const;
		void SetMatf4(const GLchar* name, const transformf& tsfm) const;

		void BindUB(const UniformBuffer* ub);
	private:
		bool CheckLinkError() const;
	};
}
