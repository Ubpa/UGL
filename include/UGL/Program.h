#pragma once

#include "Shader.h"

namespace Ubpa::gl {
	class Program : public Obj {
	public:
		Program(const Shader* vs, const Shader* fs, const Shader* gs = nullptr);
		~Program();

		Program(Program&& p) noexcept : Obj{ p.id } {}
		Program& operator=(Program&& p) noexcept;

		void Clear();

		void Use() const;
		void Param(ProgramParam pname, GLint* params) const;

	private:
		bool CheckLinkError() const;
	};
}
