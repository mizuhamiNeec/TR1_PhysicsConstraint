#include "Math/Utils.h"

#include "Math/Vec3/Vec3.h"

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

void DrawLine(const Vec3 start, const Vec3 end, const unsigned int color) {
	Novice::DrawLine(
		static_cast<int>(start.x), static_cast<int>(start.y),
		static_cast<int>(end.x), static_cast<int>(end.y),
		color
	);
}

