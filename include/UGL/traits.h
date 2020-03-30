#pragma once

#include "enums.h"

namespace Ubpa::gl {
	template<typename Enum>
	struct traits;

	template<>
	struct traits<BasicPrimitiveType> {
		static constexpr size_t point_num(BasicPrimitiveType primitive) noexcept {
			if (primitive == BasicPrimitiveType::Points)
				return static_cast<size_t>(1);
			else if (primitive == BasicPrimitiveType::Lines)
				return static_cast<size_t>(2);
			else // primitive == BasicPrimitiveType::Triagles
				return static_cast<size_t>(3);
		}
	};

	template<>
	struct traits<MinFilter> {
		static constexpr bool have_mipmap(MinFilter min) noexcept {
			if (min == MinFilter::Linear || min == MinFilter::Nearest)
				return false;
			else
				return true;
		}
	};
}
