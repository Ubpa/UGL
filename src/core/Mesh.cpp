#include <UGL/Mesh.h>

using namespace Ubpa;
using namespace gl;
using namespace std;

Mesh::Mesh(BasicPrimitiveType primitiveType, size_t primitiveNum, size_t vertexNum, const GLuint* indices,
	// pointer to data, value type, attr size : 1,2,3,4
	vector<tuple<const void*, DataType, size_t>> vertexattrs)
	: primitiveType{ primitiveType },
	primitiveNum{ primitiveNum },
	eb{ new ElementBuffer(primitiveType, primitiveNum, indices) }
{
	assert(indices != nullptr);

	for (size_t i = 0; i < vertexattrs.size(); i++) {
		auto [data, type, attr_size] = vertexattrs[i];
		assert(data != nullptr);
		assert(attr_size > 0 && attr_size <= 4); // 0, 1, 2, 3
		vbs.emplace_back(vertexNum * traits<DataType>::size(type) * attr_size, data);
		va.Attach(i, vbs.back().AttrPtr(attr_size, type, false, traits<DataType>::size(type) * attr_size));
	}

	va.Attach(*eb);
}

Mesh::Mesh(BasicPrimitiveType primitiveType, size_t primitiveNum, size_t vertexNum, const GLuint* indices,
	// pointer to data, attr size : 1,2,3,4
	vector<tuple<const float*, size_t>> vertexattrs)
	: Mesh{ primitiveType,primitiveNum,vertexNum,indices,ConvertPack(vertexattrs) }
{
}

Mesh::Mesh(BasicPrimitiveType primitiveType, size_t primitiveNum, size_t vertexNum, const GLuint* indices,
	const void* data, DataType dataType, const std::vector<size_t>& attrsizes)
	: primitiveType{ primitiveType },
	primitiveNum{ primitiveNum },
	eb{ new ElementBuffer(primitiveType, primitiveNum, indices) }
{
	assert(data != nullptr && indices != nullptr);
	size_t sumAttrSize = 0;
	for (size_t size : attrsizes) {
		assert(size > 0 && size <= 4);
		sumAttrSize += size;
	}

	vbs.emplace_back(vertexNum* sumAttrSize* traits<DataType>::size(dataType), data);
	const auto& vb = vbs.back();

	size_t offset = 0;
	for (size_t i = 0; i < attrsizes.size(); i++) {
		va.Attach(i, vb.AttrPtr(attrsizes[i], dataType, false,
			sumAttrSize * traits<DataType>::size(dataType),
			offset * traits<DataType>::size(dataType)));
		offset += attrsizes[i];
	}

	va.Attach(*eb);
}


Mesh::Mesh(BasicPrimitiveType primitiveType, size_t primitiveNum, size_t vertexNum, const GLuint* indices,
	const float* data, const std::vector<size_t>& attrsizes)
	: Mesh{ primitiveType,primitiveNum,vertexNum, indices, data, DataType::Float, attrsizes }
{
}


Mesh::Mesh(BasicPrimitiveType primitiveType, size_t primitiveNum,
	// pointer to data, value type, attr size : 1,2,3,4
	vector<tuple<const void*, DataType, size_t>> vertexattrs)
	: primitiveType{ primitiveType },
	primitiveNum{ primitiveNum }
{
	size_t vertexNum = traits<BasicPrimitiveType>::point_num(primitiveType);
	for (size_t i = 0; i < vertexattrs.size(); i++) {
		auto [data, type, attr_size] = vertexattrs[i];
		assert(data != nullptr);
		assert(attr_size > 0 && attr_size <= 4); // 0, 1, 2, 3
		vbs.emplace_back(vertexNum * traits<DataType>::size(type) * attr_size, data);
		va.Attach(i, vbs.back().AttrPtr(attr_size, type, false, traits<DataType>::size(type) * attr_size));
	}
}

Mesh::Mesh(BasicPrimitiveType primitiveType, size_t primitiveNum,
	// pointer to data, attr size : 1,2,3,4
	vector<tuple<const float*, size_t>> vertexattrs)
	: Mesh{ primitiveType, primitiveNum, ConvertPack(vertexattrs) }
{
}

Mesh::Mesh(BasicPrimitiveType primitiveType, size_t primitiveNum,
	const void* data, DataType dataType, const std::vector<size_t>& attrsizes)
	: primitiveType{ primitiveType },
	primitiveNum{ primitiveNum }
{
	assert(data != nullptr);
	size_t sumAttrSize = 0;
	for (size_t size : attrsizes) {
		assert(size > 0 && size <= 4);
		sumAttrSize += size;
	}

	size_t vertexNum = traits<BasicPrimitiveType>::point_num(primitiveType);
	vbs.emplace_back(vertexNum* sumAttrSize* traits<DataType>::size(dataType), data);
	const auto& vb = vbs.back();

	size_t offset = 0;
	for (size_t i = 0; i < attrsizes.size(); i++) {
		va.Attach(i, vb.AttrPtr(attrsizes[i], dataType, false,
			sumAttrSize * traits<DataType>::size(dataType),
			offset * traits<DataType>::size(dataType)));
		offset += attrsizes[i];
	}
}

Mesh::Mesh(BasicPrimitiveType primitiveType, size_t primitiveNum,
	const float* data, const std::vector<size_t>& attrsizes)
	: Mesh{ primitiveType,primitiveNum,data,DataType::Float,attrsizes }
{
}

vector<tuple<const void*, DataType, size_t>> Mesh::ConvertPack(const vector<tuple<const float*, size_t>>& vertexattrs) {
	vector<tuple<const void*, DataType, size_t>> rst;
	for (const auto& [data, attrsize] : vertexattrs)
		rst.emplace_back(data, DataType::Float, attrsize);
	return rst;
}

void Mesh::Draw(const Program& program) {
	program.Use();
	va.Bind();
	if (eb)
		gl::DrawElements(primitiveType, primitiveNum * traits<BasicPrimitiveType>::point_num(primitiveType));
	else
		gl::DrawArrays(primitiveType, 0, primitiveNum * traits<BasicPrimitiveType>::point_num(primitiveType));
	VertexArray::BindReset();
}
