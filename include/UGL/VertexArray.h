#pragma once

#include "gl.h"
#include "ID.h"
#include "VertexBuffer.h"

#include <vector>

namespace Ubpa::gl {
	class ElementBuffer;
	class Program;

	class VertexArray {
	public:
		struct Format {
			std::vector<VertexBuffer::AttribPointer> attrptrs;
			ElementBuffer* eb;
		};

	public:
		VertexArray();
		~VertexArray();

		VertexArray(const std::vector<GLuint>& indices, const Format& format) noexcept;
		VertexArray(VertexArray&& va) noexcept;
		VertexArray& operator=(VertexArray&& va) noexcept;

		bool IsValid() const noexcept { return id.IsValid(); }

		void Attach(GLuint idx, const VertexBuffer::AttribPointer& ptr) const;
		void Attach(const ElementBuffer* eb);
		void Attach(const std::vector<GLuint>& indices, const Format& format);
		// attach Format or ElementBuffer first
		void Draw(const Program* program) const;

		void Clear();

		void Bind() const;
		static void BindReset();

	private:
		const ElementBuffer* eb{ nullptr };
		ID id{ static_cast<GLuint>(0) }; // 0 is invalid
	};
}
