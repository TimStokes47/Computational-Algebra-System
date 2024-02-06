#pragma once

#include "maths/Matrix2x2.h"
#include "maths/Matrix3x3.h"
#include "maths/Matrix4x4.h"

class Animator2x2 {
public:
	static void startAnimation(const Matrix2x2& start, const Matrix2x2& end, Matrix2x2& state, float animationTime);
	static void updateAnimation(Matrix2x2& state, float timeStep);

private:
	static float s_t;
	static float s_animationTime;
	static bool s_isPlaying;

	static Matrix2x2 s_end;
	static Matrix2x2 s_transition;
};

class Animator3x3 {
public:
	static void startAnimation(const Matrix3x3& start, const Matrix3x3& end, Matrix3x3& state, float animationTime);
	static void updateAnimation(Matrix3x3& state, float timeStep);

private:
	static float s_t;
	static float s_animationTime;
	static bool s_isPlaying;

	static Matrix3x3 s_end;
	static Matrix3x3 s_transition;
};

class Animator4x4 {
public:
	static void startAnimation(const Matrix4x4& start, const Matrix4x4& end, Matrix4x4& state, float animationTime);
	static void updateAnimation(Matrix4x4& state, float timeStep);

private:
	static float s_t;
	static float s_animationTime;
	static bool s_isPlaying;

	static Matrix4x4 s_end;
	static Matrix4x4 s_transition;
};