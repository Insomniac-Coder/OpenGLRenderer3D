#include "shader.h"
#include <fstream>

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);
static GLuint CreateShader(const std::string& text, GLenum ShaderType);

Shader::Shader(const std::string& fileName){
	program = glCreateProgram();
	shaders[0] = CreateShader(LoadShader(fileName + ".vert"), GL_VERTEX_SHADER);
	shaders[1] = CreateShader(LoadShader(fileName + ".frag"), GL_FRAGMENT_SHADER);

	for (short i = 0; i < SHADER_NUMBER; i++) {
		glAttachShader(program, shaders[i]);
	}

	glBindAttribLocation(program, 0, "position");

	glLinkProgram(program);
	CheckShaderError(program, GL_LINK_STATUS, true, "Error: Program linking failed! : ");

	glValidateProgram(program);
	CheckShaderError(program, GL_VALIDATE_STATUS, true, "Error: Program validation failed! : ");

}

Shader::~Shader() {
	for (short i = 0; i < SHADER_NUMBER; i++) {
		glDetachShader(program, shaders[i]);
		glDeleteShader(shaders[i]);
	}

	glDeleteProgram(program);
}

void Shader::Bind() {
	glUseProgram(program);
}
static GLuint CreateShader(const std::string& text, GLenum ShaderType) {
	GLuint shader = glCreateShader(ShaderType);

	if (shader == 0)
		std::cerr << "Shader creation failed!" << std::endl;
	
	const GLchar* ShaderSourcestring[1];
	ShaderSourcestring[0]= text.c_str();
	GLint ShaderSourcestringLength[1];
	ShaderSourcestringLength[0] = text.length();
	
	glShaderSource(shader, 1, ShaderSourcestring, ShaderSourcestringLength);
	glCompileShader(shader);
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed! : ");

	return shader;
}

static std::string LoadShader(const std::string& fileName) {
	std::ifstream file;
	file.open((fileName).c_str());
	std::string output;
	std::string line;


	if (file.is_open()) {
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else{
		std::cerr << "Unable to Load Shader!! " << fileName << std::endl;
	}

	return output;
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage) {
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram) {
		glGetProgramiv(shader, flag, &success);
	}
	else {
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE) {
		if (isProgram) {
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else {
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}
		std::cerr << errorMessage << ": '" << error << "'" << std:: endl;
	}

}