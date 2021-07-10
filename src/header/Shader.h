#pragma once

#include <string>
#include <unordered_map>

class Shader {

private:
	unsigned int m_Program;
	std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	Shader();
	Shader(const std::string vertexShaderFile, const std::string fragmentShaderFile);
	~Shader();

	void InitShaders(const std::string vertexShaderFile, const std::string fragmentShaderFile);
	std::string ReadFile(const std::string& shaderFile);
	void CompileShader(const unsigned int shaderID);
	unsigned int CreateProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

	unsigned int GetProgramID() const { return m_Program; }
	void Bind()   const;
	void Unbind() const;

	void SetUniform1i(const std::string& name, int value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMatrix4fv(const std::string& name, int count, unsigned int transpose, float* value);
	int GetUniformLocation(const std::string& name);

	void DeleteProgram() const;
};