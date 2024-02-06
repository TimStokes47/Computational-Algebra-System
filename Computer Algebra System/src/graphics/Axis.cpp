#include "Axis.h"
#include "Renderer.h"

void Axis2D::generateVertexArrays() {
	float xVert[] = {
		-100.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		100.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	};
	float yVert[] = {
		0.0f, 100.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, -100.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	};

	float zVert[] = {
		0.0f, 0.0f, 100.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, -100.0f, 1.0f, 1.0f, 1.0f
	};

	unsigned int indices[] = { 0, 1 };

	m_xAxis = Renderer::generateVertexArray(xVert, sizeof(xVert), indices, sizeof(indices));
	m_yAxis = Renderer::generateVertexArray(yVert, sizeof(yVert), indices, sizeof(indices));
	m_zAxis = Renderer::generateVertexArray(zVert, sizeof(zVert), indices, sizeof(indices));
}

void Axis2D::render() {

}

unsigned int Axis2D::m_xAxis;
unsigned int Axis2D::m_yAxis;
unsigned int Axis2D::m_zAxis;