#pragma once
#include "Math/Mat4.h"
#include "Object/Object.h"

enum class FovAxis {
	Horizontal,
	Vertical
};

class Camera : public Object {
public:
	Mat4 getViewMatrix() const;
	void SetViewMatrix(const Mat4& viewMatrix);

	Mat4 GetProjectionMatrix() const;
	void SetProjectionMatrix(const Mat4& projectionMatrix);

	Camera(std::string name = "Camera", std::string tag = "", bool active = true, ProjectionMode projectionMode = ProjectionMode::Perspective, FovAxis fovAxis = FovAxis::Vertical, float fov = 90.0f);
	void Update() override;

private:
	Mat4 viewMatrix_;
	Mat4 projectionMatrix_;

	ProjectionMode projection_;
	FovAxis fovAxis_;
	float fov_;
};

