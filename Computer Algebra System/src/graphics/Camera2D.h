#ifndef CAMERA_2D
#define CAMERA_2D

#include "Camera.h"
#include "../maths/Vec4.h"
#include "../maths/Vec3.h"
#include "../maths/Vec2.h"

class Camera2D : public Camera{
public:
	Camera2D(const FloatVec3& position);

	virtual void update(float deltaTime) override;
	void onScroll(float offset) override;
	void onMouseClick(int button, int action) override;

private:
	Vec4 screenToWorldSpace(const Vec2& _screenCoords);

	const float m_speed;
	Vec3 m_lastMousePosition;
};

class Camera3D : public Camera {
public:
	Camera3D(const FloatVec3& position);

	virtual void update(float deltaTime) override;
	void onScroll(float offset) override;
	void onMouseClick(int button, int action) override;

private:
	Vec4 screenToWorldSpace(const Vec2& _screenCoords);

	float yAngle;
	float xAngle;
	float distanceFromOrigin;
	const float m_speed;
	Vec2 m_lastMousePosition;

};

#endif