#include "Shader.h"

Shader::Shader(const char *vertexPath,const char *fragPath) {
	std::string vertCode;
	std::string fragCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragPath);
		std::cout << std::string(vertexPath) << "\n" << std::string(fragPath) << "\n";
		std::stringstream vShaderStream, fShaderStream;
		
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertCode = vShaderStream.str();
		fragCode = fShaderStream.str();
	}
	catch(std::ifstream::failure &e){
		std::cout << "ERROR::FILE_READING_FAILED" << std::endl;
	}
	
	const char* vShaderCode = vertCode.c_str();
	const char* fShaderCode = fragCode.c_str();

	unsigned int vertex, fragment;
	//
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompilationError(vertex, "SHADER");
	//
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompilationError(fragment, "SHADER");
	//
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompilationError(ID, "PROGRAM");

}

void Shader::use() {
	glUseProgram(ID);

}

void Shader::setBool(const std::string& name, bool value)const{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value)const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value)const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()),value);
}

void Shader::checkCompilationError(unsigned int shader, const std::string& type) {
	int success;
	char infolog[512];
	if (type == "SHADER") {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 512, NULL, infolog);
			std::cout << "OPENGL::ERROR::LINKINGFAILLED::" << std::endl;
		}
		else {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shader, 512, NULL, infolog);
				std::cout << "OPENGL::ERROR::COMPILATIONFAILLED::" << std::endl;
			}
		}
	}

}