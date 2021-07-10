#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>

Shader::Shader()
	: m_Program(0)
{
}

Shader::Shader(const std::string vertexShaderFile, const std::string fragmentShaderFile)
	: m_Program(0)
{
	m_Program = CreateProgram(ReadFile(vertexShaderFile), ReadFile(fragmentShaderFile));
}

Shader::~Shader() {
	glDeleteProgram(m_Program);
}

void Shader::InitShaders(const std::string vertexShaderFile, const std::string fragmentShaderFile) {
	m_Program = CreateProgram(ReadFile(vertexShaderFile), ReadFile(fragmentShaderFile));
}

std::string Shader::ReadFile(const std::string& shaderFile) {

	std::ifstream file(shaderFile);
	std::string line;
	std::stringstream ss;

	if (!(file.is_open())) {
		std::cout << "Could not open " << shaderFile << "!\n";
		return "";
	}

	while (getline(file, line))
		ss << line << '\n';

	file.close();

	return ss.str();
}

void Shader::CompileShader(const unsigned int shaderID) {	// Compiles shader and checks if the compilation was successful

	glCompileShader(shaderID);

	int success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE) {
		int logLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
		char* message = new char[logLength];
		glGetShaderInfoLog(shaderID, logLength, &logLength, message);
		std::cout << "ERROR COMPILING SHADER: " << message << std::endl;

		glDeleteShader(shaderID);
		delete[] message;
	}
}

unsigned int Shader::CreateProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {

	unsigned int program = glCreateProgram();
	unsigned int vertexShader, fragmentShader;

	const char* vertexSource = vertexShaderSource.c_str();
	const char* fragmentSource = fragmentShaderSource.c_str();

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	CompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	CompileShader(fragmentShader);

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}

void Shader::Bind() const {
	glUseProgram(m_Program);
}

void Shader::Unbind() const {
	glUseProgram(0);
}

void Shader::SetUniform1i(const std::string& name, int value) {
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniformMatrix4fv(const std::string& name, int count, unsigned int transpose, float* value) {
	glUniformMatrix4fv(GetUniformLocation(name), count, transpose, value);
}

int Shader::GetUniformLocation(const std::string& name) {

	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	int location = glGetUniformLocation(m_Program, name.c_str());

	if (location == -1)
		std::cout << "Error! Uniform " << name << " does not exit in shader!\n";

	m_UniformLocationCache[name] = location;

	return location;
}

void Shader::DeleteProgram() const {
	glDeleteProgram(m_Program);
}