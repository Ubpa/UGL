#pragma once

#include "Shader.h"

namespace Ubpa::gl {
	class Program {
	public:
		Program(Shader&& vs, Shader&& fs);
		Program(const GLchar* vs_src, const GLchar* fs_src);

		Read<Program, Shader> vs;
		Read<Program, Shader> fs;
		Read<Program, Shader> gs;

		bool IsValid() const noexcept { return id.IsValid(); }
		void Use() const;
		void Param(ProgramParam pname, GLint* params) const;

	private:
		bool CheckLinkError() const;
		ID id{ static_cast<GLuint>(0) }; // 0 is invalid
	};
}
