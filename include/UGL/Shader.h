#pragma once

#include "gl.h"
#include "Obj.h"

#include <UDP/Basic/Read.h>

#include <string>

namespace Ubpa::gl {
	class Program;

	class Shader : public Obj {
		friend class Program;

	public:
		Read<Shader, std::string> path;
		Read<Shader, ShaderType> type;

		Shader(ShaderType type);
		Shader(ShaderType type, const GLchar* src);
		Shader(Shader&& shader) noexcept;
		Shader& operator=(Shader&& shader) noexcept;
		~Shader();

		void Clear();

		void Param(ShaderParam pname, GLint* params) const;

	private:
		bool CheckCompileError() const;
	};
}
