#pragma once
#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
public:
	// ID reference for the Vertex Array Object
	GLuint ID;
	VAO();
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	// Binds the VAO
	void bind();
	// Unbinds the VAO
	void unbind();
	// Deletes the VAO
	void Delete();
};
#endif