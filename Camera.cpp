#include "Camera.h"

#include <utility>

#include "config.h"
#include "Math/Utils.h"

Mat4 Camera::getViewMatrix() const { return viewMatrix_; }

void Camera::SetViewMatrix(const Mat4& viewMatrix) { viewMatrix_ = viewMatrix; }

Mat4 Camera::GetProjectionMatrix() const { return projectionMatrix_; }

void Camera::SetProjectionMatrix(const Mat4& projectionMatrix) { projectionMatrix_ = projectionMatrix; }

Camera::Camera(std::string name, std::string tag, bool active, ProjectionMode projectionMode, FovAxis fovAxis,
	float fov) {
	name_ = std::move(name);
	tag_ = std::move(tag);
	active_ = active;
	projection_ = projectionMode;
	fovAxis_ = fovAxis;
	fov_ = fov;
}

void Camera::Update() {
	Mat4 cameraMat = Mat4::Affine(transform_.scale, transform_.rotation, transform_.position);
	Mat4 viewMat = cameraMat.Inverse();
	Mat4 projectionMat = Mat4::PerspectiveFovMat(fov_ * deg2Rad, static_cast<float>(kClientWidth) / static_cast<float>(kClientHeight), 0.1f, 100.0f, TODO);

	Mat4 worldViewProjMat = viewMat * projectionMat;

	viewMatrix_ = Mat4::ViewportMat(0, 0, static_cast<float>(kClientWidth), static_cast<float>(kClientHeight), 0.0f, 1.0f);
	projectionMatrix_ = worldViewProjMat;


	Object::Update();
}
