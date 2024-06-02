#include "Vec2.h"

#include <cassert>
#include <corecrt_math.h>
#include <stdexcept>

const Vec2 Vec2::zero(0.0f, 0.0f);

/// <summary>
///	ベクトルの長さの2乗を返します
/// </summary>
float Vec2::SqrtLength() const {
	return x * x + y * y;
}

/// <summary>
/// ベクトルの長さを返します
/// </summary>
float Vec2::Length() const {
	const float sqrtLength = SqrtLength();
	if (sqrtLength > 0.0f) {
		return sqrtf(sqrtLength);
	}
	return 0.0f;
}

/// <summary>
/// otherとのDot積を返します
/// </summary>
float Vec2::DotProduct(const Vec2& other) const {
	return x * other.x + y * other.y;
}

/// <summary>
/// otherとのCross積を返します
/// </summary>
float Vec2::CrossProduct(const Vec2& other) const {
	return x * other.y - y * other.x;
}

/// <summary>
///	ノーマライズします
/// </summary>
void Vec2::Normalize() {
	*this = this->Normalized();
}

/// <summary>
/// ノーマライズされた値を返します
/// </summary>
Vec2 Vec2::Normalized() const {
	const float sqrtLength = SqrtLength();
	if (sqrtLength > 0.0f) {
		const float invertLength = 1.0f / sqrtf(sqrtLength);
		return {x * invertLength, y * invertLength};
	}
	return zero;
}

/// <summary>
/// startからendの間を線形補間します
/// </summary>
/// <param name="start">開始位置</param>
/// <param name="end">終了位置</param>
/// <param name="t">0～1の値</param>
Vec2 Vec2::Lerp(const Vec2& start, const Vec2& end, const float t) {
	return {start.x + (end.x - start.x) * t, start.y + (end.y - start.y) * t};
}

/// <summary>
/// 添字演算子
/// </summary>
float& Vec2::operator[](const int index) {
	assert(index <= 1 && index >= 0 && "Index out of range");
	if (index == 0) {
		return x;
	}
	if (index == 1) {
		return y;
	}
	static float ret = 0.0f;
	return ret;
}

/// <summary>
/// 添字演算子
/// </summary>
const float& Vec2::operator[](const int index) const {
	assert(index <= 1 && index >= 0 && "Index out of range");
	if (index == 0) {
		return x;
	}
	if (index == 1) {
		return y;
	}
	static constexpr float ret = 0.0f;
	return ret;
}

/// <summary>
/// スカラー値との加算を行います
/// </summary>
/// <param name="rhs">加算するスカラー値</param>
Vec2 Vec2::operator+(const float& rhs) const {
	return {x + rhs, y + rhs};
}

/// <summary>
/// スカラー値との減算を行います
/// </summary>
/// <param name="rhs">減算するスカラー値</param>
Vec2 Vec2::operator-(const float& rhs) const {
	return {x - rhs, y - rhs};
}

/// <summary>
/// スカラー値との乗算を行います
/// </summary>
/// <param name="rhs">乗算するスカラー値</param>
Vec2 Vec2::operator*(const float& rhs) const {
	return {x * rhs, y * rhs};
}

/// <summary>
/// スカラー値との除算を行います
/// </summary>
/// <param name="rhs">除算するスカラー値</param>
Vec2 Vec2::operator/(const float& rhs) const {
	return {x / rhs, y / rhs};
}

/// <summary>
/// スカラー値を加算して代入します
/// </summary>
/// <param name="rhs">加算するスカラー値</param>
Vec2& Vec2::operator+=(const float& rhs) {
	x += rhs;
	y += rhs;
	return *this;
}

/// <summary>
/// スカラー値を減算して代入します
/// </summary>
/// <param name="rhs">減算するスカラー値</param>
Vec2& Vec2::operator-=(const float& rhs) {
	x -= rhs;
	y -= rhs;
	return *this;
}

/// <summary>
/// スカラー値を乗算して代入します
/// </summary>
/// <param name="rhs">乗算するスカラー値</param>
Vec2& Vec2::operator*=(const float& rhs) {
	x *= rhs;
	y *= rhs;
	return *this;
}

/// <summary>
/// スカラー値を除算して代入します
/// </summary>
/// <param name="rhs">除算するスカラー値</param>
Vec2& Vec2::operator/=(const float& rhs) {
	x /= rhs;
	y /= rhs;
	return *this;
}

/// <summary>
/// 他のVec2との加算を行います
/// </summary>
/// <param name="rhs">加算するVec2</param>
Vec2 Vec2::operator+(const Vec2& rhs) const {
	return {x + rhs.x, y + rhs.y};
}

/// <summary>
/// 他のVec2との減算を行います
/// </summary>
/// <param name="rhs">減算するVec2</param>
Vec2 Vec2::operator-(const Vec2& rhs) const {
	return {x - rhs.x, y - rhs.x};
}

/// <summary>
/// 他のVec2との乗算を行います
/// </summary>
/// <param name="rhs">乗算するVec2</param>
Vec2 Vec2::operator*(const Vec2& rhs) const {
	return {x * rhs.x, y * rhs.y};
}

/// <summary>
/// 他のVec2との除算を行います
/// </summary>
/// <param name="rhs">除算するVec2</param>
Vec2 Vec2::operator/(const Vec2& rhs) const {
	return {x / rhs.x, y / rhs.y};
}

/// <summary>
/// 他のVec2を加算して代入します
/// </summary>
/// <param name="rhs">加算するVec2</param>
Vec2& Vec2::operator+=(const Vec2& rhs) {
	x += rhs.x;
	y += rhs.y;
	return *this;
}

/// <summary>
/// 他のVec2を減算して代入します
/// </summary>
/// <param name="rhs">減算するVec2</param>
Vec2& Vec2::operator-=(const Vec2& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

/// <summary>
/// 他のVec2を乗算して代入します
/// </summary>
/// <param name="rhs">乗算するVec2</param>
Vec2& Vec2::operator*=(const Vec2& rhs) {
	x *= rhs.x;
	y *= rhs.y;
	return *this;
}

/// <summary>
/// 他のVec2を除算して代入します
/// </summary>
/// <param name="rhs">除算するVec2</param>
Vec2& Vec2::operator/=(const Vec2& rhs) {
	x /= rhs.x;
	y *= rhs.y;
	return *this;
}
