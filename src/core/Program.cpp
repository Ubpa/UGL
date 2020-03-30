#include <UGL/Program.h>

#include <iostream>

using namespace Ubpa;
using namespace Ubpa::gl;
using namespace std;


Program::Program(const GLchar* vs_src, const GLchar* fs_src) : Program{
	Shader{ShaderType::VertexShader, vs_src},
	Shader{ShaderType::FragmentShader, fs_src}
} {}

Program::Program(Shader&& vs_, Shader&& fs_)
	: vs{ move(vs_) },
	fs{ move(fs_) },
	gs{ ShaderType::GeometryShader },
	id{ gl::CreateProgram() }
{
	gl::AttachShader(id.get(), vs->id.get());
	gl::AttachShader(id.get(), fs->id.get());
	gl::LinkProgram(id.get());
}

void Program::Param(ProgramParam pname, GLint* params) const {
	assert(IsValid());
	gl::GetProgramiv(id.get(), pname, params);
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
	gl::GetShaderInfoLog(id.get(), infoLen, NULL, infoLog);
	cerr << "ERROR::Shader::CheckCompileError():" << endl
		<< "  link fail" << endl
		<< "  - vs path: " << (vs->path->empty() ? "generated by code / empty" : vs->path.get()) << endl
		<< "  - fs path: " << (fs->path->empty() ? "generated by code / empty" : vs->path.get()) << endl
		<< "  - gs path: " << (gs->path->empty() ? "generated by code / empty" : vs->path.get()) << endl
		<< "  - info: " << infoLog << endl;
	return false;
}

void Program::Use() const {
	assert(IsValid());
	gl::UseProgram(id.get());
}
