#include "Camera.h"

#include <imgui.h>
#include <string>
#include <utility>

#include "Config.h"

Camera::Camera(std::string name, std::string tag, const bool active) {
	name_ = std::move(name);
	tag_ = std::move(tag);
	active_ = active;
}

Vec3 Camera::WorldToScreen(Vec3 world) const {
	world -= transform_.position;

	float angle = transform_.rotation.z;

	// 回転している場合は追加で計算する
	if (angle != 0.0f) {
		const float sin = sinf(angle);
		const float cos = cosf(angle);

		world = {
			world.x * cos - world.y * sin,
			world.x * sin + world.y * cos,
			world.z
		};
	}

	// スクリーン座標に変換
	Vec3 positionOnScr;
	positionOnScr.x = world.x * zoom_ + static_cast<float>(kClientWidth * 0.5f);
	positionOnScr.y = static_cast<float>(kClientHeight * 0.5f) - world.y * zoom_;

	// こねこねした値を返す
	return positionOnScr;
}

void Camera::Details() {
	Object::Details();

	ImGui::Begin("Details");

	if (ImGui::CollapsingHeader("Camera Settings", ImGuiTreeNodeFlags_DefaultOpen)) {
		ImGui::DragFloat("Zoom", &zoom_, 0.1f);
	}

	ImGui::End();
}

float Camera::GetZoom() const {
	return zoom_;
}
