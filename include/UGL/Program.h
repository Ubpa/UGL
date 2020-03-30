#pragma once

#include "Shader.h"

namespace Ubpa::gl {
	class Program {
	public:
		Program(const Shader& vs, const Shader& fs);

		Read<Program, GLuint> ID{ static_cast<GLuint>(0) }; // 0 is invalid
		Read<Program, std::string> vsPath;
		Read<Program, std::string> fsPath;
		Read<Program, std::string> gsPath;

		bool IsValid() const noexcept { return ID != 0; }
		void Use() const;

	private:
		bool CheckLinkError() const;
	};
}
