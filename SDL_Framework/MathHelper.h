#pragma once
#include <math.h>

namespace SDLFramework {
//macros
#define PI 3.1415926535
#define DEG_TO_RAD PI / 180.0f

	struct Vector2 {
		float x;
		float y;

		Vector2(float _x = 0.0f, float _y = 0.0f) : x{ _x }, y{ _y } {

		}

		float Magnitude() {
			//Pythagorean's Theorum
			return (float)sqrt(x * x + y * y);
		}

		//Works on a single vector level
		float MagnitudeSqr() {
			return x * x + y * y;
		}

		Vector2 Normalized() {
			float mag = Magnitude();
			return Vector2(x / mag, y / mag);
		}
	};

	inline Vector2 operator+ (const Vector2& lhs, const Vector2& rhs) {
		return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	inline Vector2 operator-(const Vector2& lhs, const Vector2& rhs) {
		return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	inline Vector2 operator*(const Vector2& lhs, float rhs) {
		return Vector2(lhs.x * rhs, lhs.y * rhs);
	}

	inline Vector2 operator*(float lhs, const Vector2& rhs) {
		return Vector2(lhs * rhs.x, lhs * rhs.y);
	}

	//VECTORS STOP HERE ---------------------------------->

	//Performing linear interpolation
	//Used to create smooth movement in games
	inline Vector2 Lerp(const Vector2& start, const Vector2& end, float time) {
		if (time <= 0.0f) {
			return start;
		}

		if (time >= 1.0f) {
			return end;
		}

		Vector2 dir = (end - start).Normalized();
		float mag = (end - start).Magnitude();

		return start + dir * mag * time;
	}

	//Rotating the angle of a vector while keeping its magnitude the same
	inline Vector2 RotateVector(const Vector2& vec, float& angle) {
		//convert degrees to radians
		float radAngle = (float)(angle * DEG_TO_RAD);

		return Vector2((float)vec.x * cos(radAngle) - vec.y * sin(radAngle), //Rotated X Position
						(float)vec.x * sin(radAngle) + vec.y * cos(radAngle)); //Rotated Y Postion 
	}

	//Requires us to have 2 vectors
	inline float Dot(const Vector2& vec1, const Vector2& vec2) {
		return vec1.x * vec2.x + vec1.y * vec2.y;
	}

	inline float Clamp(const float& value, const float& min, const float& max) {
		if (value > max) {
			return max;
		}
		if (value < min) {
			return min;
		}

		return value;
	}

	const Vector2 Vec2_Zero = { 0.0f, 0.0f };
	const Vector2 Vec2_One = { 1.0f, 1.0f };
	//The inverse of Vec2_Up is -Vec2_Up
	const Vector2 Vec2_Up = { 0.0f, 1.0f };
	const Vector2 Vec2_Right = { 1.0f, 0.0f };
}