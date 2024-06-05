#pragma once
#include "Object/Base/Object.h"

enum class ProjectionMode {
	Perspective,
	Orthographic
};

class Camera : public Object {
public:
	Camera(std::string name = "Camera", std::string tag = "", bool active = true);
	Vec3 WorldToScreen(Vec3 world) const;

	void Details() override;

	float GetZoom() const;

private:
	float zoom_ = 1.0f;
};
