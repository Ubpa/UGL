#include <UGL/Shader.h>

#include <iostream>

using namespace Ubpa;
using namespace Ubpa::gl;
using namespace std;

Shader::Shader(Type type, const GLchar* src)
	: type{type}
{
	ID = glCreateShader(static_cast<GLenum>(type));

	if (!IsValid()) {
		cerr << "ERROR::Shader::Shader(Type, const GLchar*):" << endl
			<< "  create shader fail" << endl
			<< "  - path: " << (path->empty() ? "generated by code" : path.get()) << endl;
		return;
	}

	glShaderSource(ID, 1, &src, NULL);
	glCompileShader(ID);

	if (!CheckCompileError())
		Clear();
}

Shader::Shader(Shader&& shader) noexcept
	: ID{ shader.ID }, path{ shader.path }, type{ shader.type }
{
	shader.ID = static_cast<GLuint>(0);
	shader.path->clear();
	shader.type = Type::EMPTY;
}

Shader& Shader::operator=(Shader&& shader) noexcept {
	ID = shader.ID;
	path = shader.path;
	shader.ID = static_cast<GLuint>(0);
	shader.path->clear();
	shader.type = Type::EMPTY;
	return *this;
}

void Shader::Clear() {
	glDeleteShader(ID);
	ID = static_cast<GLuint>(0);
	path->clear();
	type = Type::EMPTY;
}

Shader::~Shader() {
	Clear();
}

bool Shader::CheckCompileError() const {
	assert(IsValid());

	GLint success;
	glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
	if (success)
		return true;

	// compile fail
	constexpr GLsizei infoLen = 512;
	GLchar infoLog[infoLen];
	glGetShaderInfoLog(ID, infoLen, NULL, infoLog);
	cerr << "ERROR::Shader::CheckCompileError():" << endl
		<< "  compile fail" << endl
		<< "  - path: " << (path->empty() ? "generated by code" : path.get()) << endl
		<< "  - info: " << infoLog << endl;
	return false;
}
