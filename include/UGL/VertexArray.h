#pragma once

#include "gl.h"
#include "Obj.h"
#include "VertexBuffer.h"

#include <vector>

namespace Ubpa::gl {
	class ElementBuffer;
	class Program;

	class VertexArray : public Obj {
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

		void Attach(GLuint idx, const VertexBuffer::AttribPointer& ptr) const;
		void Attach(const ElementBuffer* eb);
		void Attach(const std::vector<GLuint>& indices, const Format& format);
		// attach Format or ElementBuffer first
		void Draw(const Program* program) const;

		bool IsValid() const noexcept;

		void Clear();

		void Bind() const;
		static void BindReset();

	private:
		const ElementBuffer* eb{ nullptr };
	};
}
