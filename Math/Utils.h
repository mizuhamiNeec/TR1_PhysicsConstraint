#pragma once

#include <numbers>

#include "Novice.h"
#include "Vec3/Vec3.h"

template <typename T>
T Clamp(const T& value, const T& min, const T& max);

float Lerp(const float& start, const float& end, const float& t);

constexpr float deg2Rad = static_cast<float>(std::numbers::pi_v<float> / 180.0f);

void DrawArrow(const Vec3 start, const Vec3 end, const unsigned int color);