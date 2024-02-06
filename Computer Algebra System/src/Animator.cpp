#include "Animator.h"

void Animator2x2::startAnimation(const Matrix2x2& start, const Matrix2x2& end, Matrix2x2& state, float animationTime)
{
	s_transition = end - start;
	s_t = 0.0f;
	s_animationTime = animationTime;
	s_isPlaying = true;
	s_end = end;
	state = start;
}

void Animator2x2::updateAnimation(Matrix2x2& state, float timeStep)
{
	if (s_isPlaying) {
		s_t += timeStep;
		if (s_t >= s_animationTime) {
			s_isPlaying = false;
			state = s_end;
		}
		else {
			state = state + (timeStep / s_animationTime) * s_transition;
			state.generateFloatData();
		}
	}
}

float Animator2x2::s_t;
float Animator2x2::s_animationTime;
bool Animator2x2::s_isPlaying = false;
Matrix2x2 Animator2x2::s_transition;
Matrix2x2 Animator2x2::s_end;

void Animator3x3::startAnimation(const Matrix3x3& start, const Matrix3x3& end, Matrix3x3& state, float animationTime)
{
	s_transition = end - start;
	s_t = 0.0f;
	s_animationTime = animationTime;
	s_isPlaying = true;
	s_end = end;
	state = start;
}

void Animator3x3::updateAnimation(Matrix3x3& state, float timeStep)
{
	if (s_isPlaying) {
		s_t += timeStep;
		if (s_t >= s_animationTime) {
			s_isPlaying = false;
			state = s_end;
		}
		else {
			state = state + (timeStep / s_animationTime) * s_transition;
			state.generateFloatData();
		}
	}
}

float Animator3x3::s_t;
float Animator3x3::s_animationTime;
bool Animator3x3::s_isPlaying = false;
Matrix3x3 Animator3x3::s_transition;
Matrix3x3 Animator3x3::s_end;

void Animator4x4::startAnimation(const Matrix4x4& start, const Matrix4x4& end, Matrix4x4& state, float animationTime)
{
	s_transition = end - start;
	s_t = 0.0f;
	s_animationTime = animationTime;
	s_isPlaying = true;
	s_end = end;
	state = start;
}

void Animator4x4::updateAnimation(Matrix4x4& state, float timeStep)
{
	if (s_isPlaying) {
		s_t += timeStep;
		if (s_t >= s_animationTime) {
			s_isPlaying = false;
			state = s_end;
		}
		else {
			state = state + (timeStep / s_animationTime) * s_transition;
			state.generateFloatData();
		}
	}
}

float Animator4x4::s_t;
float Animator4x4::s_animationTime;
bool Animator4x4::s_isPlaying = false;
Matrix4x4 Animator4x4::s_transition;
Matrix4x4 Animator4x4::s_end;