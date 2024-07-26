//
// * ENGINE-X
//
// + Types.h
// representations of: 2D vector with floats, 2D vector with integers and RBGA color as four bytes
//
#include "Game/Public/Utils.h"

#pragma once

//-----------------------------------------------------------------
//-----------------------------------------------------------------

struct exVector2
{
	float x, y;

	exVector2 operator+(const exVector2& other) {
		return exVector2{ this->x + other.x, this->y + other.y };
	}
	exVector2 operator-(const exVector2& other) {
		return exVector2{ this->x - other.x, this->y - other.y };
	}
	exVector2 operator*(const float scale) {
		return exVector2{ this->x * scale, this->y * scale };
	}
	exVector2 operator/(const float scale) {
		return exVector2{ this->x / scale, this->y / scale };
	}

	exVector2 operator+=(const exVector2& other) {
		return exVector2{ this->x += other.x, this->y += other.y };
	}
	exVector2 operator-=(const exVector2& other) {
		return exVector2{ this->x -= other.x, this->y -= other.y };
	}

	float magnitude() const {
		return sqrt(x * x + y * y);
	}
	exVector2 normalized() const{
		return exVector2{ x / magnitude(), y / magnitude() };
	}
	float dot(const exVector2& other) {
		return x* other.x + y * other.y;
	}

};

//-----------------------------------------------------------------
//-----------------------------------------------------------------

struct exIntegerVector2
{
	int x, y;
};

//-----------------------------------------------------------------
//-----------------------------------------------------------------

struct exColor
{
	unsigned char mColor[4];
};
