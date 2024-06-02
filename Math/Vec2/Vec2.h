#pragma once

struct Vec2 final {
	float x, y;

	Vec2(): x(0.0f), y(0.0f) {}

	Vec2(const float x, const float y): x(x), y(y) {}

	static const Vec2 zero;

	/* -------- メンバ関数 -------- */

	float SqrtLength() const;
	float Length() const;
	float DotProduct(const Vec2& other) const;
	float CrossProduct(const Vec2& other) const;

	void Normalize();
	Vec2 Normalized() const;

	static Vec2 Lerp(const Vec2& start, const Vec2& end, float t);

	/* -------- 演算子 -------- */
	float& operator[](int index);
	const float& operator[](int index) const;

	// スカラー
	Vec2 operator+(const float& rhs) const;
	Vec2 operator-(const float& rhs) const;
	Vec2 operator*(const float& rhs) const;
	Vec2 operator/(const float& rhs) const;

	Vec2& operator+=(const float& rhs);
	Vec2& operator-=(const float& rhs);
	Vec2& operator*=(const float& rhs);
	Vec2& operator/=(const float& rhs);

	// ベクトル
	Vec2 operator+(const Vec2& rhs) const;
	Vec2 operator-(const Vec2& rhs) const;
	Vec2 operator*(const Vec2& rhs) const;
	Vec2 operator/(const Vec2& rhs) const;

	Vec2& operator+=(const Vec2& rhs);
	Vec2& operator-=(const Vec2& rhs);
	Vec2& operator*=(const Vec2& rhs);
	Vec2& operator/=(const Vec2& rhs);
};
