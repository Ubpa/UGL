#pragma once

#include "Texture.h"

namespace Ubpa::gl {
	class FrameBuffer;

	class Texture2D : public Texture {
	public:
		Texture2D();

	private:
		friend class FrameBuffer;
		const ID& GetID() const noexcept { return id; }
	};
}