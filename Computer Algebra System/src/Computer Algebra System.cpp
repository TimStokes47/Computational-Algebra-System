// Computer Algebra System.cpp : Defines the entry point for the application.
//

/*

#include "Computer Algebra System.h"
#include "maths/Vec4.h"
#include "maths/Utility.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include "maths/Matrix4x4.h"
#include <array>

using namespace std;

int main()
{
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(960, 540, "CAS", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glewInit();

	float vertices[] = {
		-0.5f,  0.5f,  0.0f,
		 0.5f,  0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f,
		-0.5f, -0.5f,  0.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	unsigned int vertexArrayObject;
	glGenVertexArrays(1, &vertexArrayObject);
	
	unsigned int vertexBuffer, elementBuffer;
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &elementBuffer);

	glBindVertexArray(vertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glClearColor(0.3f, 0.2f, 0.3f, 1.0f);

	std::ifstream vertexShaderFile, fragmentShaderFile;
	vertexShaderFile.open("../../../shaders/Vertex Shader.vs");
	fragmentShaderFile.open("../../../shaders/Fragment Shader.fs");

	if (!(vertexShaderFile.is_open() && fragmentShaderFile.is_open())) {
		std::cout << "File not found";
	}
	std::stringstream vertexStream, fragmentStream;
	vertexStream << vertexShaderFile.rdbuf();
	fragmentStream << fragmentShaderFile.rdbuf();
	std::string vertexShaderSrc = vertexStream.str();
	const char* vertexSrc = vertexShaderSrc.c_str();
	std::string fragmentShaderSrc = fragmentStream.str();
	const char* fragmentSrc = fragmentShaderSrc.c_str();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
	glCompileShader(vertexShader);
	int success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);
	glCompileShader(fragmentShader);

	unsigned int program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	while (!glfwWindowShouldClose(window)) {
		glBindVertexArray(vertexArrayObject);
		glUseProgram(program);

		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}
*/