#pragma once

#include "gl.h"

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ElementBuffer.h"

#include "Program.h"

namespace Ubpa::gl {
	class Mesh {
	public:
		Read<Mesh, BasicPrimitiveType> primitiveType;
		Read<Mesh, size_t> primitiveNum;

		Mesh(BasicPrimitiveType primitiveType, size_t primitiveNum, size_t vertexNum, const GLuint* indices, 
			// pointer to data, value type, attr size : 1,2,3,4
			std::vector<std::tuple<const void*, DataType, size_t>> vertexattrs);

		Mesh(BasicPrimitiveType primitiveType, size_t primitiveNum, size_t vertexNum, const GLuint* indices,
			// pointer to data, attr size : 1,2,3,4
			std::vector<std::tuple<const float*, size_t>> vertexattrs);

		Mesh(BasicPrimitiveType primitiveType, size_t primitiveNum, size_t vertexNum, const GLuint* indices,
			const void* data, DataType dataType, const std::vector<size_t>& attrsizes);

		Mesh(BasicPrimitiveType primitiveType, size_t primitiveNum, size_t vertexNum, const GLuint* indices,
			const float* data, const std::vector<size_t>& attrsizes);

		Mesh(BasicPrimitiveType primitiveType, size_t primitiveNum,
			// pointer to data, value type, attr size : 1,2,3,4
			std::vector<std::tuple<const void*, DataType, size_t>> vertexattrs);

		Mesh(BasicPrimitiveType primitiveType, size_t primitiveNum,
			// pointer to data, attr size : 1,2,3,4
			std::vector<std::tuple<const float*, size_t>> vertexattrs);

		Mesh(BasicPrimitiveType primitiveType, size_t primitiveNum,
			const void* data, DataType dataType, const std::vector<size_t>& attrsizes);

		Mesh(BasicPrimitiveType primitiveType, size_t primitiveNum,
			const float* data, const std::vector<size_t>& attrsizes);

		void Draw(const Program& program);

	private:
		static std::vector<std::tuple<const void*, DataType, size_t>> ConvertPack(const std::vector<std::tuple<const float*, size_t>>& vertexattrs);

	private:
		std::vector<VertexBuffer> vbs;
		ElementBuffer* eb{ nullptr };
		VertexArray va;
	};
}
