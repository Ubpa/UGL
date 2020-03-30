#pragma once

#include "config.h"
#include <cassert>

namespace Ubpa::gl {
	class ID {
	public:
		ID(GLuint data = static_cast<GLuint>(0)) noexcept : data{ data } {}

		ID(ID&& id) noexcept : data{ id.data }
		{ id.Clear(); }

		ID& operator=(ID&& id) noexcept {
			data = id.data;
			id.Clear();
			return *this;
		}

		void Clear() noexcept {
			data = static_cast<GLuint>(0);
		}

		operator GLuint() const noexcept {
			assert(IsValid());
			return data;
		}

		bool IsValid() const noexcept {
			return data != static_cast<GLuint>(0);
		}

		GLuint* init_ptr() noexcept {
			assert(!IsValid());
			return &data;
		}

		const GLuint* del_ptr() const noexcept {
			assert(IsValid());
			return &data;
		}

	private:
		GLuint data;
	};
}
