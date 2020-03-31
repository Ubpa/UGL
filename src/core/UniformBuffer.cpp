#include <UGL/UniformBuffer.h>

using namespace Ubpa;
using namespace Ubpa::gl;
using namespace std;

UniformBuffer::UniformBuffer(Packer&& packer, BufferUsage usage)
	: Buffer{ BufferType::UniformBuffer, packer.size, nullptr, usage }, packer{ move(packer) }, bindingPoint{nextBindingPoint++}
{
}

void UniformBuffer::BindReset() {
	Buffer::BindReset(BufferType::UniformBuffer);
}

void UniformBuffer::Set(const std::string& name, const void* data) {
	auto target = packer.n2os->find(name);
	assert(target != packer.n2os->end());
	auto [offset, size] = target->second;
	SubData(offset, size, data);
}

void UniformBuffer::Packer::Push(const string& name, Type type) {
	switch (type)
	{
    case Ubpa::gl::UniformBuffer::Packer::Type::Bool:
    case Ubpa::gl::UniformBuffer::Packer::Type::Int:
    case Ubpa::gl::UniformBuffer::Packer::Type::UInt:
    case Ubpa::gl::UniformBuffer::Packer::Type::Float:
        n2os->insert({ name, make_tuple(size, 4) });
        size.val += 4;
        break;
    case Ubpa::gl::UniformBuffer::Packer::Type::Vec2:
        size = ((size + 4) >> 3) << 3;
        n2os->insert({ name, make_tuple(size, 8) });
        size.val += 8;
        break;
    case Ubpa::gl::UniformBuffer::Packer::Type::Vec3:
    case Ubpa::gl::UniformBuffer::Packer::Type::Vec4:
        size = ((size + 12) >> 4) << 4;
        n2os->insert({ name, make_tuple(size, 16) });
        size.val += 16;
        break;
    case Ubpa::gl::UniformBuffer::Packer::Type::Mat3x3:
        size = ((size + 12) >> 4) << 4;
        n2os->insert({ name, make_tuple(size, 48) });
        size.val += 48;
        break;
    case Ubpa::gl::UniformBuffer::Packer::Type::Mat4x4:
        size = ((size + 12) >> 4) << 4;
        n2os->insert({ name, make_tuple(size, 64) });
        size.val += 64;
        break;
    default:
        break;
	}
}

void UniformBuffer::Packer::PushArray(const std::string& name, Type type, size_t n) {
    switch (type)
    {
    case Ubpa::gl::UniformBuffer::Packer::Type::Bool:
    case Ubpa::gl::UniformBuffer::Packer::Type::Int:
    case Ubpa::gl::UniformBuffer::Packer::Type::UInt:
    case Ubpa::gl::UniformBuffer::Packer::Type::Float:
    case Ubpa::gl::UniformBuffer::Packer::Type::Vec2:
    case Ubpa::gl::UniformBuffer::Packer::Type::Vec3:
    case Ubpa::gl::UniformBuffer::Packer::Type::Vec4:
        size = ((size + 12) >> 4) << 4;
        n2os->insert({ name, make_tuple(size, 16 * n) });
        size.val += 16 * n;
        break;
    case Ubpa::gl::UniformBuffer::Packer::Type::Mat3x3:
        size = ((size + 12) >> 4) << 4;
        n2os->insert({ name, make_tuple(size, 48 * n) });
        size.val += 48 * n;
        break;
    case Ubpa::gl::UniformBuffer::Packer::Type::Mat4x4:
        size = ((size + 12) >> 4) << 4;
        n2os->insert({ name, make_tuple(size, 64 * n) });
        size.val += 64 * n;
        break;
    default:
        break;
    }
}
//
//void UniformBuffer::Packer::Print() const {
//    map<size_t, tuple<string, size_t>> o2ns;
//    for (const auto& [name, os] : n2os.get()) {
//        auto [offset, size] = os;
//        o2ns[offset] = make_tuple(name, size);
//    }
//
//    cout << "layout (std140) uniform " << name.get() << " {" << endl;
//    cout << "\t\t// size\t//offset" << endl;
//    for (const auto& [offset, ns] : o2ns) {
//        auto [name, size] = ns;
//        cout << "\t" << name << "\t// " << size << "\t// " << offset << endl;
//    }
//    cout << "}" << endl;
//}
