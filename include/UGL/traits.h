#pragma once

#include "enums.h"

#include <cassert>

namespace Ubpa::gl {
	template<typename Enum>
	struct traits;

	template<>
	struct traits<BasicPrimitiveType> {
		inline static constexpr size_t point_num(BasicPrimitiveType primitive) noexcept {
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
		inline static constexpr bool have_mipmap(MinFilter min) noexcept {
			if (min == MinFilter::Linear || min == MinFilter::Nearest)
				return false;
			else
				return true;
		}
	};

	template<>
	struct traits<DataType> {
		inline static constexpr size_t size(DataType type) noexcept {
			switch (type)
			{
			case Ubpa::gl::DataType::Byte:
				return sizeof(GLbyte);
			case Ubpa::gl::DataType::Short:
				return sizeof(GLshort);
			case Ubpa::gl::DataType::Int:
				return sizeof(GLint);
			case Ubpa::gl::DataType::Float:
				return sizeof(GLfloat);
			case Ubpa::gl::DataType::HalfFloat:
				return sizeof(GLhalf);
			case Ubpa::gl::DataType::Double:
				return sizeof(GLdouble);
			case Ubpa::gl::DataType::UnsignedByte:
				return sizeof(GLubyte);
			case Ubpa::gl::DataType::UnsignedShort:
				return sizeof(GLshort);
			case Ubpa::gl::DataType::UnsignedInt:
				return sizeof(GLuint);
			default:
				assert(true);
				return 0;
			}
		}
	};
}
