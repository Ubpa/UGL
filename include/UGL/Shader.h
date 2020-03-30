#pragma once

#include "gl.h"

#include <UDP/Basic/Read.h>

#include <string>

namespace Ubpa::gl {
	class Shader {
	public:
		enum class Type : GLenum {
			//COMPUTE = GL_COMPUTE_SHADER,
			VERTEX = GL_VERTEX_SHADER,
			//TESS_CONTROL = GL_TESS_CONTROL_SHADER,
			//TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
			GEOMETRY = GL_GEOMETRY_SHADER,
			FRAGMENT = GL_FRAGMENT_SHADER,
			EMPTY = 0,
		};

		Read<Shader, std::string> path;
		Read<Shader, GLuint> ID{ static_cast<GLuint>(0) }; // 0 is invalid
		Read<Shader, Type> type{ Type::EMPTY };

		Shader() = default;
		Shader(Type type, const GLchar* src);
		Shader(Shader&& shader) noexcept;
		Shader& operator=(Shader&& shader) noexcept;
		~Shader();

		bool IsValid() const noexcept { return ID != 0; }

		void Clear();

	private:
		bool CheckCompileError() const;
	};
}
