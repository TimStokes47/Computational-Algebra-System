#include "Camera2D.h"
#include "../Input.h"
#include "../maths/FloatVec4.h"
#include "../maths/FloatMatrix4x4.h"
#include <iostream>

Camera2D::Camera2D(const FloatVec3& position)
	: Camera(position), m_speed(5.0f)
{
}

void Camera2D::update(float deltaTime) {
	if (Input::isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
		Vec3 position = screenToWorldSpace(Input::getMousePosition());
		Vec3 delta = position - m_lastMousePosition;
		m_lastMousePosition = position;

		m_position[0] = m_position[0] - 0.1f * delta[0] / 960.0f * 540;
		m_position[1] = m_position[1] + 0.1f * delta[1];

		m_lookAt = Matrix4x4::lookAt(m_position, m_position + m_viewDirection, m_up);
	}
}

void Camera2D::onScroll(float offset) {
	m_position[2] = m_position[2] - offset;
	m_lookAt = Matrix4x4::lookAt(m_position, m_position + m_viewDirection, m_up);
	m_lookAt.generateFloatData();
}

void Camera2D::onMouseClick(int button, int action) {
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		m_lastMousePosition = screenToWorldSpace(Input::getMousePosition());
	}
}

Vec4 Camera2D::screenToWorldSpace(const Vec2& _screenCoords) {
	Vec4 screenCoords(_screenCoords.x(), _screenCoords.y(), -1.0f, 1.0f);
	Vec4 coords = m_projectionInverse * screenCoords;
	//std::cout << coords << "\n";
	return coords;
}

Camera3D::Camera3D(const FloatVec3& position)
	: Camera(position), m_speed(5.0f), distanceFromOrigin(position.z()), xAngle(0.0f), yAngle(0.0f)
{
}

void Camera3D::update(float deltaTime) {
	if (Input::isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
		Vec2 mousePosition = Input::getMousePosition();
		Vec2 deltaMousePosition = mousePosition - m_lastMousePosition;
		m_lastMousePosition = mousePosition;

		yAngle -= deltaMousePosition.x() / 200.0f;
		xAngle -= deltaMousePosition.y() / 200.0f;
		if (xAngle > 1.57) xAngle = 1.57;
		if (xAngle < -1.57) xAngle = -1.57;
		
		FloatVec4 position(0.0f, 0.0f, distanceFromOrigin, 1.0f);
		position = FloatMatrix4x4::rotateX(xAngle) * position;
		position = FloatMatrix4x4::rotateY(yAngle) * position;
		m_position = FloatVec3(position[0], position[1], position[2]);

		m_lookAt = Matrix4x4::lookAt(m_position, FloatVec3(0.0f, 0.0f, 0.0f), m_up);
	}
}

void Camera3D::onScroll(float offset) {
	distanceFromOrigin -= offset;

	FloatVec4 position(0.0f, 0.0f, distanceFromOrigin, 1.0f);
	position = FloatMatrix4x4::rotateX(xAngle) * position;
	position = FloatMatrix4x4::rotateY(yAngle) * position;
	m_position = FloatVec3(position[0], position[1], position[2]);

	m_lookAt = Matrix4x4::lookAt(m_position, FloatVec3(0.0f, 0.0f, 0.0f), m_up);
}

void Camera3D::onMouseClick(int button, int action) {
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		m_lastMousePosition = Input::getMousePosition();
	}
}

Vec4 Camera3D::screenToWorldSpace(const Vec2& _screenCoords) {
	Vec4 screenCoords(_screenCoords.x(), _screenCoords.y(), -1.0f, 1.0f);
	Vec4 coords = m_projectionInverse * screenCoords;
	//std::cout << coords << "\n";
	return coords;
}