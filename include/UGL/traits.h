#pragma once

#include "enums.h"

namespace Ubpa::gl {
	template<typename Enum>
	struct traits;

	template<>
	struct traits<BasicPrimitiveType> {
		static constexpr GLuint point_num(BasicPrimitiveType primitive) noexcept {
			if (primitive == BasicPrimitiveType::Points)
				return static_cast<GLuint>(1);
			else if (primitive == BasicPrimitiveType::Lines)
				return static_cast<GLuint>(2);
			else // primitive == BasicPrimitiveType::Triagles
				return static_cast<GLuint>(3);
		}
	};
}
