#pragma once
#include <cmath>

class Vector2 {

public :
	int x{ 0 };
	int y{ 0 };

	Vector2() = default;
	Vector2(int newX, int newY) : x(newX), y(newY) {}

	Vector2 operator + (const Vector2 other) const
	{
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator - (const Vector2 other) const
	{
		return Vector2(x - other.x, y - other.y);
	}

	Vector2 operator * (const Vector2 other) const
	{
		return Vector2(x * other.x, y * other.y);
	}

	Vector2 operator / (const Vector2 other) const
	{
		return Vector2(x / other.x, y / other.y);
	}

	Vector2 operator += (const Vector2 other) const
	{
		return Vector2(x + other.x, y + other.y);
	}
};