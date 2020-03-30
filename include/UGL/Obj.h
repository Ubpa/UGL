#pragma once

#include "ID.h"

namespace Ubpa::gl {
	class Obj {
	public:
		Obj() = default;
		virtual ~Obj() {};
		Obj(ID&& id) noexcept : id{ std::move(id) } {}
		Obj& operator=(Obj&& obj) noexcept {
			id = std::move(obj.id);
			return *this;
		}
		Obj(GLuint data) noexcept : id{ data } {}

		bool IsValid() const noexcept { return id.IsValid(); }
	protected:
		ID id{ static_cast<GLuint>(0) };
	};
}