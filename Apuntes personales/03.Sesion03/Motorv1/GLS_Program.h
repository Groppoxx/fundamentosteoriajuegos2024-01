#pragma once
#include <GL/glew.h>
#include <string>

using namespace std;

class GLS_Program
{
private:
	GLuint programID;
	GLuint vertexShaderID;
	GLuint fragmentShaderID;
	int numAttributes;

	void compileShader(const string& filePath, GLuint id);
public:
	GLS_Program();
	~GLS_Program();

	void compileShaders(const string& vertexShaderFilePath, 
		const string& fragmentShaderFilePath);
	void linkShaders();
	void addAttribute(const string attributeName);
	void use();
	void unuse();
	GLuint getUniformLocation(const string& uniformName);
};

