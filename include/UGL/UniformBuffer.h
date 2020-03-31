#pragma once

#include "gl.h"
#include "Buffer.h"

#include <UDP/Basic/Read.h>

#include <map>
#include <string>

namespace Ubpa::gl {
	class UniformBuffer : public Buffer {
	public:
		// std140
		class Packer {
		public:
			Read<Packer, size_t> size;
			Read<Packer, std::map<std::string, std::tuple<size_t, size_t>>> n2os; // name to offset and size
			
			enum class Type {
				Bool, Int, UInt, Float,
				Vec2, Vec3, Vec4,
				Mat3x3, Mat4x4,
			};
			void Push(const std::string& name, Type type);
			void PushArray(const std::string& name, Type type, size_t n);
		};
	public:
		Read<UniformBuffer, size_t> bindingPoint;

		UniformBuffer(Packer&& packer, BufferUsage usage = BufferUsage::StaticDraw);

		void Set(const std::string& name, const void* data);

		static void BindReset();

	private:
		Packer packer;
		inline static size_t nextBindingPoint = 0;
	};
}
