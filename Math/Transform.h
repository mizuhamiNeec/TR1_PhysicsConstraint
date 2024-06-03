#pragma once
#include "Vec3/Vec3.h"

struct Transform {
	Vec3 position;
	Vec3 rotation;
	Vec3 scale;

	Transform(Vec3 position, Vec3 rotation, Vec3 scale) : position(position), rotation(rotation), scale(scale) {}
	Transform() {
		position = Vec3::zero;
		rotation = Vec3::zero;
		scale = Vec3::one;
	}
};
