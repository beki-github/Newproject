
#pragma once
#include <glad/glad.h>


	// Set up VAO, VBO, EBO with vertex and index data
	void setBufferObjects(GLuint& VAO, GLuint& VBO, GLuint& EBO, const float* vertices, size_t vertices_size, const unsigned int* indices, size_t indices_size);

