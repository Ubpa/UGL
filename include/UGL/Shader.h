#pragma once

#include "gl.h"
#include "ID.h"

#include <UDP/Basic/Read.h>

#include <string>

namespace Ubpa::gl {
	class Shader {
	public:
		Read<Shader, std::string> path;
		Read<Shader, ID> id{ static_cast<GLuint>(0) }; // 0 is invalid
		Read<Shader, ShaderType> type;

		Shader(ShaderType type);
		Shader(ShaderType type, const GLchar* src);
		Shader(Shader&& shader) noexcept;
		Shader& operator=(Shader&& shader) noexcept;
		~Shader();

		bool IsValid() const noexcept { return id->IsValid(); }

		void Clear();

		void Param(ShaderParam pname, GLint* params) const;

	private:
		bool CheckCompileError() const;
	};
}
