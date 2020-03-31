#include <UGL/UniformBuffer.h>

#include <iostream>

using namespace Ubpa;
using namespace Ubpa::gl;
using namespace std;

int main() {
	using Type = gl::UniformBuffer::Packer::Type;
	gl::UniformBuffer::Packer packer("ExampleBlock");
	packer.Push("value", Type::Float);
	packer.Push("vector", Type::Vec3);
	packer.Push("matrix", Type::Mat4x4);
	packer.PushArray("values", Type::Float, 3);
	packer.Push("boolean", Type::Bool);
	packer.Push("integer", Type::Int);

	map<size_t, tuple<string, size_t>> o2ns;
	for (const auto& [name, os] : packer.n2os.get()) {
		auto [offset, size] = os;
		o2ns[offset] = make_tuple(name, size);
	}

	cout << "layout (std140) uniform " << packer.name.get() << " {" << endl;
	cout << "\t\t// size\t//offset" << endl;
	for (const auto& [offset, ns] : o2ns) {
		auto [name, size] = ns;
		cout << "\t" << name << "\t// " << size << "\t// " << offset << endl;
	}
	cout << "}" << endl;

	return 0;
}
