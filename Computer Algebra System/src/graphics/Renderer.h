#ifndef RENDERER_H
#define RENDERER_H

class Vec2;

class Renderer {
public:
	static unsigned int generateVertexArray(float* vertices, unsigned int verticesSize, unsigned int* indices, unsigned int indicesSize);
};

class Renderer2D {
public:
	static unsigned int generateUnitSquare();
	static unsigned int generateGrid();
	static unsigned int generateRay(const Vec2& vector);
};

class Renderer3D {
public:
	static unsigned int generateUnitCube();
};

#endif