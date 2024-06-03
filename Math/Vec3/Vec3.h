#pragma once

struct Vec3 final {
	float x, y, z;

	Vec3() : x(0.0f), y(0.0f), z(0.0f) {}

	Vec3(const float x, const float y, const float z) : x(x), y(y), z(z) {}

	static const Vec3 zero;
	static const Vec3 one;

	/* -------- メンバ関数 -------- */

	float SqrtLength() const;
	float Length() const;
	float DotProduct(const Vec3& other) const;
	Vec3 CrossProduct(const Vec3& other) const;

	void Normalize();
	Vec3 Normalized() const;

	static Vec3 Lerp(const Vec3& start, const Vec3& end, float t);

	/* -------- 演算子 -------- */
	float& operator[](int index);
	const float& operator[](int index) const;

	// スカラー
	Vec3 operator+(const float& rhs) const;
	Vec3 operator-(const float& rhs) const;
	Vec3 operator*(const float& rhs) const;
	Vec3 operator/(const float& rhs) const;

	Vec3& operator+=(const float& rhs);
	Vec3& operator-=(const float& rhs);
	Vec3& operator*=(const float& rhs);
	Vec3& operator/=(const float& rhs);

	// ベクトル
	Vec3 operator+(const Vec3& rhs) const;
	Vec3 operator-(const Vec3& rhs) const;
	Vec3 operator*(const Vec3& rhs) const;
	Vec3 operator/(const Vec3& rhs) const;

	Vec3& operator+=(const Vec3& rhs);
	Vec3& operator-=(const Vec3& rhs);
	Vec3& operator*=(const Vec3& rhs);
	Vec3& operator/=(const Vec3& rhs);
};
