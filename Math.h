#pragma once

#include <cmath>
#include <memory.h>
#include <limits>

namespace Math {
	const float Pi = 3.1415926535f;

	// �x�����烉�W�A���֕ϊ�
	inline float ToRadians(float degrees) {
		return degrees * Pi / 180.0f;
	}
	// ���W�A������x���֕ϊ�
	inline float ToDegrees(float radians) {
		return radians * 180.0f / Pi;
	}

	bool NearZero(float val, float epsilon = 0.001f);
}

class Vector2 {
public:
	float x;
	float y;

	Vector2() : x(0.0f), y(0.0f) {}
	explicit Vector2(float inX, float inY) :
		x(inX), y(inY) {}

	void Set(float inX, float inY) {
		x = inX;
		y = inY;
	}

	friend Vector2 operator+(const Vector2& a, const Vector2& b) {
		return Vector2(a.x + b.x, a.y + b.y);
	}
	friend Vector2 operator-(const Vector2& a, const Vector2& b) {
		return Vector2(a.x - b.x, a.y - b.y);
	}
	friend Vector2 operator*(const Vector2& a, const Vector2& b) {
		return Vector2(a.x * b.x, a.y * b.y);
	}
	friend Vector2 operator*(const Vector2& vec, const float& scalar) {
		return Vector2(vec.x * scalar, vec.y * scalar);
	}
	friend Vector2 operator*(const float& scalar, const Vector2& vec) {
		return Vector2(scalar * vec.x, scalar * vec.y);
	}
	Vector2& operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}
	Vector2& operator+=(const Vector2& right) {
		x += right.x;
		y += right.y;
		return *this;
	}
	Vector2& operator-=(const Vector2& right) {
		x -= right.x;
		y -= right.y;
		return *this;
	}
	float LengthSq() const {
		return (x * x + y * y);
	}

	// �x�N�g���̒���
	float Length() const {
		return sqrtf(LengthSq());
	}

	// �񎟌��x�N�g���𐳋K������
	void Normalize() {
		float length = Length();
		x /= length;
		y /= length;
	}

	static Vector2 Normalize(const Vector2& vec) {
		Vector2 tmp = vec;
		tmp.Normalize();
		return tmp;
	}
	// �Q�̓񎟌��x�N�g���̓���
	static float Dot(const Vector2& a, const Vector2& b) {
		return (a.x * b.x + a.y * b.y);
	}


private:

};

