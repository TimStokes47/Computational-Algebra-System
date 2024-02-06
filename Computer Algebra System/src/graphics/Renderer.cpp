#include "Renderer.h"
#include "GL/glew.h"
#include "../maths/Vec2.h"

unsigned int Renderer::generateVertexArray(float* vertices, unsigned int verticesSize, unsigned int* indices, unsigned int indicesSize) {
	unsigned int vertexArray;
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	unsigned int vertexBuffer, elementBuffer;
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &elementBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	return vertexArray;
}



unsigned int Renderer2D::generateUnitSquare()
{
	float vertices[] = {
		-1.0f,  1.0f,  0.0f, 0.0f, 0.0f, 1.0f,
		 1.0f,  1.0f,  0.0f, 0.0f, 0.0f, 1.0f,
		 1.0f, -1.0f,  0.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f, 0.0f, 1.0f
	};

	unsigned int indices[] = {
		2, 1, 0,
		3, 2, 0
	};

	return Renderer::generateVertexArray(vertices, sizeof(vertices), indices, sizeof(indices));
}

unsigned int Renderer2D::generateGrid()
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	for (int i = 0; i < 400; i++) {
		vertices.push_back(-100.0f);
		vertices.push_back((float)(i));
		vertices.push_back(0.0f);
		vertices.push_back(1.0f);
		vertices.push_back(1.0f);
		vertices.push_back(1.0f);

		vertices.push_back(100.0f);
		vertices.push_back((float)(i));
		vertices.push_back(0.0f);
		vertices.push_back(1.0f);
		vertices.push_back(1.0f);
		vertices.push_back(1.0f);

		indices.push_back(2 * i);
		indices.push_back(2 * i + 1);
	}

	for (int i = 0; i < 400; i++) {
		vertices.push_back((float)(i));
		vertices.push_back(-100.0f);
		vertices.push_back(0.0f);
		vertices.push_back(1.0f);
		vertices.push_back(1.0f);
		vertices.push_back(1.0f);

		vertices.push_back((float)(i));
		vertices.push_back(100.0f);
		vertices.push_back(0.0f);
		vertices.push_back(1.0f);
		vertices.push_back(1.0f);
		vertices.push_back(1.0f);

		indices.push_back(2 * i);
		indices.push_back(2 * i + 1);
	}

	return Renderer::generateVertexArray(vertices.data(), vertices.size(), indices.data(), indices.size());
}

unsigned int Renderer2D::generateRay(const Vec2& vector)
{
	float vertices[] = {
		-vector.x() * 100.0f, -vector.y() * 100.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		vector.x() * 100.0f, vector.y() * 100.0f, 0.0f, 1.0f, 1.0f, 1.0f
	};

	unsigned int indices[] = { 0, 1 };

	return Renderer::generateVertexArray(vertices, sizeof(vertices), indices, sizeof(indices));
}

unsigned int Renderer3D::generateUnitCube()
{
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	unsigned int indices[] = {
		5, 4, 3, 2, 1, 0,
		6,7,8,9,10,11,
		12,13,14,15,16,17,
		23,22,21,20,19,18,
		24,25,26,27,28,29,
		35,34,33,32,31,30
	};

	return Renderer::generateVertexArray(vertices, sizeof(vertices), indices, sizeof(indices));
}
