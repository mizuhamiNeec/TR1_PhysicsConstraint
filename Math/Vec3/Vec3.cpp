#include "Vec3.h"

#include <cassert>
#include <corecrt_math.h>
#include <stdexcept>

const Vec3 Vec3::zero(0.0f, 0.0f, 0.0f);

/// <summary>
///	ベクトルの長さの2乗を返します
/// </summary>
float Vec3::SqrtLength() const {
	return x * x + y * y + z * z;
}

/// <summary>
/// ベクトルの長さを返します
/// </summary>
float Vec3::Length() const {
	const float sqrtLength = SqrtLength();
	if (sqrtLength > 0.0f) {
		return sqrtf(sqrtLength);
	}
	return 0.0f;
}

/// <summary>
/// otherとのDot積を返します
/// </summary>
float Vec3::DotProduct(const Vec3& other) const {
	return x * other.x + y * other.y + z * other.z;
}

/// <summary>
/// otherとのCross積を返します
/// </summary>
Vec3 Vec3::CrossProduct(const Vec3& other) const {
	return {y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x};
}

/// <summary>
/// ノーマライズします
/// </summary>
void Vec3::Normalize() {
	*this = this->Normalized();
}

/// <summary>
/// ノーマライズされた値を返します
/// </summary>
Vec3 Vec3::Normalized() const {
	const float sqrtLength = SqrtLength();
	if (sqrtLength > 0.0f) {
		const float invertLength = 1.0f / sqrtf(sqrtLength);
		return {x * invertLength, y * invertLength, z * invertLength};
	}
	return zero;
}

/// <summary>
/// startからendの間を線形補間します
/// </summary>
/// <param name="start">開始位置</param>
/// <param name="end">終了位置</param>
/// <param name="t">0～1の値</param>
Vec3 Vec3::Lerp(const Vec3& start, const Vec3& end, float t) {
	return {
		start.x + (end.x - start.x) * t,
		start.y + (end.y - start.y) * t,
		start.z + (end.z - start.z) * t
	};
}

/// <summary>
/// 添字演算子
/// </summary>
float& Vec3::operator[](const int index) {
	assert(index <= 2 && index >= 0 && "Index out of range");
	if (index == 0) {
		return x;
	}
	if (index == 1) {
		return y;
	}
	if (index == 2) {
		return z;
	}
	static float ret = 0.0f;
	return ret;
}

/// <summary>
/// 添字演算子
/// </summary>
const float& Vec3::operator[](const int index) const {
	assert(index <= 2 && index >= 0 && "Index out of range");
	if (index == 0) {
		return x;
	}
	if (index == 1) {
		return y;
	}
	if (index == 2) {
		return z;
	}
	static constexpr float ret = 0.0f;
	return ret;
}

/// <summary>
/// スカラー値との加算を行います
/// </summary>
/// <param name="rhs">加算するスカラー値</param>
Vec3 Vec3::operator+(const float& rhs) const {
	return {x + rhs, y + rhs, z + rhs};
}

/// <summary>
/// スカラー値との減算を行います
/// </summary>
/// <param name="rhs">減算するスカラー値</param>
Vec3 Vec3::operator-(const float& rhs) const {
	return {x - rhs, y - rhs, z - rhs};
}

/// <summary>
/// スカラー値との乗算を行います
/// </summary>
/// <param name="rhs">乗算するスカラー値</param>
Vec3 Vec3::operator*(const float& rhs) const {
	return {x * rhs, y * rhs, z * rhs};
}

/// <summary>
/// スカラー値との除算を行います
/// </summary>
/// <param name="rhs">除算するスカラー値</param>
Vec3 Vec3::operator/(const float& rhs) const {
	return {x / rhs, y / rhs, z / rhs};
}

/// <summary>
/// スカラー値を加算して代入します
/// </summary>
/// <param name="rhs">加算するスカラー値</param>
Vec3& Vec3::operator+=(const float& rhs) {
	x += rhs;
	y += rhs;
	z += rhs;
	return *this;
}

/// <summary>
/// スカラー値を減算して代入します
/// </summary>
/// <param name="rhs">減算するスカラー値</param>
Vec3& Vec3::operator-=(const float& rhs) {
	x -= rhs;
	y -= rhs;
	z -= rhs;
	return *this;
}

/// <summary>
/// スカラー値を乗算して代入します
/// </summary>
/// <param name="rhs">乗算するスカラー値</param>
Vec3& Vec3::operator*=(const float& rhs) {
	x *= rhs;
	y *= rhs;
	z *= rhs;
	return *this;
}

/// <summary>
/// スカラー値を除算して代入します
/// </summary>
/// <param name="rhs">除算するスカラー値</param>
Vec3& Vec3::operator/=(const float& rhs) {
	x /= rhs;
	y /= rhs;
	z /= rhs;
	return *this;
}

/// <summary>
/// 他のVec3との加算を行います
/// </summary>
/// <param name="rhs">加算するVec3</param>
Vec3 Vec3::operator+(const Vec3& rhs) const {
	return {x + rhs.x, y + rhs.y, z + rhs.z};
}

/// <summary>
/// 他のVec3との減算を行います
/// </summary>
/// <param name="rhs">減算するVec3</param>
Vec3 Vec3::operator-(const Vec3& rhs) const {
	return {x - rhs.x, y - rhs.y, z - rhs.z};
}

/// <summary>
/// 他のVec3との乗算を行います
/// </summary>
/// <param name="rhs">乗算するVec3</param>
Vec3 Vec3::operator*(const Vec3& rhs) const {
	return {x * rhs.x, y * rhs.y, z * rhs.z};
}

/// <summary>
/// 他のVec3との除算を行います
/// </summary>
/// <param name="rhs">除算するVec3</param>
Vec3 Vec3::operator/(const Vec3& rhs) const {
	return {x / rhs.x, y / rhs.y, z / rhs.z};
}

/// <summary>
/// 他のVec3を加算して代入します
/// </summary>
/// <param name="rhs">加算するVec3</param>
Vec3& Vec3::operator+=(const Vec3& rhs) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

/// <summary>
/// 他のVec3を減算して代入します
/// </summary>
/// <param name="rhs">減算するVec3</param>
Vec3& Vec3::operator-=(const Vec3& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

/// <summary>
/// 他のVec3を乗算して代入します
/// </summary>
/// <param name="rhs">乗算するVec3</param>
Vec3& Vec3::operator*=(const Vec3& rhs) {
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	return *this;
}

/// <summary>
/// 他のVec3を除算して代入します
/// </summary>
/// <param name="rhs">除算するVec3</param>
Vec3& Vec3::operator/=(const Vec3& rhs) {
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;
	return *this;
}
