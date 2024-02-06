#ifndef CAMERA_H
#define CAMERA_H

#include "../InputReciever.h"
#include "../Input.h"
#include "../maths/Augmented Matrix4x4.h"
#include "../maths/FloatVec3.h"

class Camera : public InputReciever {
public:
	Camera(const FloatVec3& position)
		: m_position(position), m_viewDirection(0.0f, 0.0f, -1.0f), m_up(0.0f, 1.0f, 0.0f)
	{
		float aspectRatio = 960.0f / 540.0f;
		m_lookAt = Matrix4x4::lookAt(m_position, m_position + m_viewDirection, m_up);
		m_projection = Matrix4x4::perspectiveProject(aspectRatio, 0.6f, 0.1f, 100.0f);
		Matrix4x4 identity = Matrix4x4::identity();
		AugmentedMatrix4x4 augmented(m_projection, identity);
		augmented.reduceLeft();
		m_projectionInverse = augmented.getRight();
		Input::registerReciever(this);

	}
	virtual ~Camera() {
		Input::deregisterReciever(this);
	}

	Matrix4x4 const& getLookAtMatrix() const { return m_lookAt; }
	Matrix4x4 const& getProjectionMatrix() const { return m_projection; }

	virtual void update(float deltaTime) = 0;

protected:
	FloatVec3 m_viewDirection;
	FloatVec3 m_up;
	FloatVec3 m_position;

	Matrix4x4 m_lookAt;
	Matrix4x4 m_projection;
	Matrix4x4 m_projectionInverse;
};

#endif