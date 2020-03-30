#include <UGL/Program.h>

#include <iostream>

using namespace Ubpa;
using namespace Ubpa::gl;
using namespace std;

Program::Program(const Shader* vs, const Shader* fs)
	: Obj{ gl::CreateProgram() }
{
	gl::AttachShader(id, vs->id);
	gl::AttachShader(id, fs->id);
	gl::LinkProgram(id);
}

Program::~Program() {
	Clear();
}

Program& Program::operator=(Program&& p) noexcept {
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
