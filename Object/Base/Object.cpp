#include "Object.h"

#include <imgui.h>

#include "Camera.h"
#include "Novice.h"
#include "Math/Mat4.h"

std::vector<std::shared_ptr<Object>> Object::GetChildren() {
	return children_;
}

void Object::SetParent(const std::shared_ptr<Object>& parentObject) {
	parent_ = parentObject;
}

Transform Object::GetTransform() const {
	return transform_;
}

void Object::SetTransform(const Transform& transform) {
	transform_ = transform;
}

Object::Object(std::string name, std::string tag, const bool active): name_(std::move(name)), tag_(std::move(tag)),
                                                                      active_(active), parent_(nullptr) {}

void Object::Initialize(const std::string& name) {
	name_ = name;
}

void Object::Update() {
	for (auto& child : children_) {
		child->Update();
	}
}

void Object::Draw(const Camera& camera) {
	camera;
}

void Object::Details() {
	ImGui::Begin("Details");
	if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {
		ImGui::DragFloat3("Location ", &transform_.position.x, 0.5f);
		ImGui::SameLine();
		if (ImGui::ArrowButton("LocReset", ImGuiDir_Left)) {
			transform_.position = Vec3::zero;
		}

		ImGui::DragFloat3("Rotation ", &transform_.rotation.x, 0.01f);
		ImGui::SameLine();
		if (ImGui::ArrowButton("RotReset", ImGuiDir_Left)) {
			transform_.rotation = Vec3::zero;
		}

		Vec3 initScale = transform_.scale;

		// DragFloat3を使用してscaleを編集
		if (ImGui::DragFloat3("Scale", &transform_.scale.x, 0.01f)) {
			if (maintainAspectRatio && initScale.x != 0.0f && initScale.y != 0.0f && initScale.z != 0.0f) {
				// 比率を維持するための処理
				float ratioX = transform_.scale.x / initScale.x;
				float ratioY = transform_.scale.y / initScale.y;
				float ratioZ = transform_.scale.z / initScale.z;

				// 変化した方向を検出
				Vec3 dir = transform_.scale - initScale;

				// 変化した比率を決定
				float ratio = 1.0f;
				if (dir.x != 0.0f) ratio = ratioX;
				else if (dir.y != 0.0f) ratio = ratioY;
				else if (dir.z != 0.0f) ratio = ratioZ;

				// スケールを更新
				transform_.scale.x = initScale.x * ratio;
				transform_.scale.y = initScale.y * ratio;
				transform_.scale.z = initScale.z * ratio;
			}
		}

		ImGui::SameLine(0, 9);

		if (ImGui::Checkbox("##AspectRatio", &maintainAspectRatio)) {
		}

		ImGui::SameLine();
		if (ImGui::ArrowButton("ScaleReset", ImGuiDir_Left)) {
			transform_.scale = Vec3::one;
		}
	}

	ImGui::End();
}

std::string Object::GetName() {
	return name_;
}
