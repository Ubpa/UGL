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
		Read<Shader, const ShaderType> type;

		Shader(ShaderType type);
		Shader(ShaderType type, const std::string& path);
		Shader(Shader&& shader) noexcept;
		Shader& operator=(Shader&& shader) noexcept;
		~Shader();

		bool InitPath(const std::string& path);
		bool InitSrc(const std::string& src);

		void Clear();

		void Param(ShaderParam pname, GLint* params) const;

	private:
		bool CheckCompileError() const;
	};
}
