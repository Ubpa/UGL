#include <UGL/Program.h>

#include <UGL/Texture.h>

#include <UGL/UniformBuffer.h>

#include <iostream>

using namespace Ubpa;
using namespace Ubpa::gl;
using namespace std;

Program::Program(const Shader* vs, const Shader* fs, const Shader* gs)
	: Obj{ gl::CreateProgram() }
{
	assert(vs != nullptr && fs != nullptr);
	assert(vs->type == ShaderType::VertexShader);
	assert(fs->type == ShaderType::FragmentShader);
	assert(!gs || gs->type == ShaderType::GeometryShader);
	gl::AttachShader(id, vs->id);
	gl::AttachShader(id, fs->id);
	if (gs != nullptr)
		gl::AttachShader(id, gs->id);
	gl::LinkProgram(id);
}

Program::~Program() {
	Clear();
}
Program::Program(Program&& p) noexcept : Obj{ move(p.id) } {}

Program& Program::operator=(Program&& p) noexcept {
	Clear();
	id = std::move(p.id);
	return *this;
}

void Program::Clear() {
	if (IsValid()) {
		gl::DeleteProgram(id);
		id.Clear();
	}
}

void Program::Param(ProgramParam pname, GLint* params) const {
	assert(IsValid());
	gl::GetProgramiv(id, pname, params);
}

GLint Program::GetUniformLocation(const GLchar* name) const {
	assert(IsValid());
	GLint rst = gl::GetUniformLocation(id, name);
	//assert(rst != -1);
	return rst;
}

bool Program::CheckLinkError() const {
	assert(IsValid());

	GLint success;
	Param(ProgramParam::LinkStatus, &success);
	if (success)
		return true;

	// link fail
	constexpr GLsizei infoLen = 512;
	GLchar infoLog[infoLen];
	gl::GetShaderInfoLog(id, infoLen, NULL, infoLog);
	cerr << "ERROR::Shader::CheckCompileError():" << endl
		<< "  link fail" << endl
		<< "  - info: " << infoLog << endl;
	return false;
}

void Program::Use() const {
	assert(IsValid());
	gl::UseProgram(id);
}

void Program::Active(size_t idx, Texture* tex) {
	Use();
	gl::ActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + idx));
	tex->Bind(); // bind after active
}

void Program::SetTex(const GLchar* name, size_t v) const {
	SetInt(name, static_cast<GLint>(v));
}

void Program::SetBool(const GLchar* name, GLboolean v) const {
	SetInt(name, static_cast<GLint>(v));
}

void Program::SetInt(const GLchar* name, GLint v) const {
	Use();
	auto pos = GetUniformLocation(name);
	if (pos != -1)
		gl::Uniform1i(pos, v);
}

void Program::SetUInt(const GLchar* name, GLuint v) const {
	Use();
	auto pos = GetUniformLocation(name);
	if (pos != -1)
		gl::Uniform1ui(pos, v);
}

void Program::SetFloat(const GLchar* name, GLfloat v) const {
	Use();
	auto pos = GetUniformLocation(name);
	if (pos != -1)
		gl::Uniform1f(pos, v);
}

void Program::SetVecf2(const GLchar* name, const val<GLfloat, 2>& v) const {
	Use();
	auto pos = GetUniformLocation(name);
	if (pos != -1)
		gl::Uniform2f(pos, v[0], v[1]);
}

void Program::SetVecf3(const GLchar* name, const val<GLfloat, 3>& v) const {
	Use();
	auto pos = GetUniformLocation(name);
	if (pos != -1)
		gl::Uniform3f(pos, v[0], v[1], v[2]);
}
;
void Program::SetVecf4(const GLchar* name, const val<GLfloat, 4>& v) const {
	Use();
	auto pos = GetUniformLocation(name);
	if (pos != -1)
		gl::Uniform4f(pos, v[0], v[1], v[2], v[3]);
}

void Program::SetInts(const GLchar* name, GLuint n, const GLint* data) const {
	Use();
	auto pos = GetUniformLocation(name);
	if (pos != -1)
		gl::Uniform1iv(pos, n, data);
}

void Program::SetUInts(const GLchar* name, GLuint n, const GLuint* data) const {
	Use();
	auto pos = GetUniformLocation(name);
	if (pos != -1)
		gl::Uniform1uiv(pos, n, data);
}

void Program::SetFloats(const GLchar* name, GLuint n, const GLfloat* data) const {
	Use();
	auto pos = GetUniformLocation(name);
	if (pos != -1)
		gl::Uniform1fv(pos, n, data);
}

void Program::SetVecf2s(const GLchar* name, GLuint n, const GLfloat* data) const {
	Use();
	auto pos = GetUniformLocation(name);
	if (pos != -1)
		gl::Uniform2fv(pos, n, data);
}
;
void Program::SetVecf3s(const GLchar* name, GLuint n, const GLfloat* data) const {
	Use();
	auto pos = GetUniformLocation(name);
	if (pos != -1)
		gl::Uniform3fv(pos, n, data);
}

void Program::SetVecf4s(const GLchar* name, GLuint n, const GLfloat* data) const {
	Use();
	auto pos = GetUniformLocation(name);
	if (pos != -1)
		gl::Uniform4fv(pos, n, data);
}

void Program::SetMatf4(const GLchar* name, const matf4& mat) const {
	Use();
	auto pos = GetUniformLocation(name);
	if (pos != -1)
		gl::UniformMatrix4fv(pos, 1, GL_FALSE, mat.data());
}

void Program::SetMatf4(const GLchar* name, const transformf& tsfm) const {
	Use();
	auto pos = GetUniformLocation(name);
	if (pos != -1)
		gl::UniformMatrix4fv(pos, 1, GL_FALSE, tsfm.data());
}

void Program::BindUB(const UniformBuffer* ub) {
	Use();
	GLuint idx = gl::GetUniformBlockIndex(id, ub->GetName().c_str());
	gl::UniformBlockBinding(id, idx, static_cast<GLuint>(ub->bindingPoint));
}
