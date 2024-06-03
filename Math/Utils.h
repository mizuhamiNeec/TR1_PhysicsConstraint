#pragma once

#include <numbers>

template <typename T>
T Clamp(const T& value, const T& min, const T& max) {
	if (value < min) {
		return min;
	}
	if (value > max) {
		return max;
	}
	return value;
}

float Lerp(const float& start, const float& end, const float& t) {
	return start + (end - start) * t;
}

constexpr float deg2Rad = static_cast<float>(std::numbers::pi_v<float> / 180.0f);