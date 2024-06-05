#pragma once
#include <imgui.h>

#include "Camera.h"
#include "Novice.h"
#include "2DPhysics/Rigidbody/Rigidbody.h"
#include "Base/Object.h"
#include "Math/Utils.h"

constexpr float deltaTime = 1.0f / 60.0f;

class Circle final : public Object {
public:
	~Circle() override;
	float GetRadius() const {
		return circleRadius_;
	}

	bool IsCollide(const Circle& other) const {
		float distance = this->transform_.position.Distance(other.transform_.position);
		float radiusSum = this->circleRadius_ * this->transform_.scale.x + other.circleRadius_ * other.transform_.scale.x;
		return distance < radiusSum;
	}

	Circle(const std::string& name = "Circle", const std::string& tag = "", bool active = true, float radius = 32.0f);
	void Initialize(const std::string& name) override;

	void ResolveCollision(Circle& other);

	void Update() override {
		rb_.Update(this, collisionShapes_, deltaTime);

		for (auto& child : children_) {
			if (auto circleChild = dynamic_cast<Circle*>(child.get())) {
				if (IsCollide(*circleChild)) {
					ResolveCollision(*circleChild);
				}

				for (auto& otherChild : children_) {
					if (circleChild != otherChild.get()) {
						if (auto otherCircleChild = dynamic_cast<Circle*>(otherChild.get())) {
							if (circleChild->IsCollide(*otherCircleChild)) {
								circleChild->ResolveCollision(*otherCircleChild);
							}
						}
					}
				}
			}
			child->Update();
		}
	}

	void Draw(const Camera& camera) override {
		const Vec3 viewpos = camera.WorldToScreen(transform_.position);
		const Vec3 viewVel = camera.WorldToScreen(transform_.position + rb_.GetVelocity());
		float fixedRadius = circleRadius_ * camera.GetZoom();

		if (viewport.IsOverlappingCircle({ viewpos.x,viewpos.y }, fixedRadius)) {
			Novice::DrawEllipse(
				static_cast<int>(viewpos.x), static_cast<int>(viewpos.y),
				static_cast<int>(fixedRadius * transform_.scale.x), static_cast<int>(fixedRadius * transform_.scale.y),
				transform_.rotation.z,
				0x000000FF,
				kFillModeWireFrame
			);

			Vec3 lineEnd = { fixedRadius, 0.0f, 0.0f };

			Novice::DrawLine(
				static_cast<int>(viewpos.x), static_cast<int>(viewpos.y),
				static_cast<int>(viewpos.x + (lineEnd.x * transform_.scale.x * cos(transform_.rotation.z) - lineEnd.y *
					transform_.scale.y * sin(transform_.rotation.z))),
				static_cast<int>(viewpos.y + (lineEnd.x * transform_.scale.x * sin(transform_.rotation.z) + lineEnd.y *
					transform_.scale.y * cos(transform_.rotation.z))),
				RED
			);
		}

		DrawArrow(viewpos, viewVel, 0xFFFF00FF);

		for (auto& child : children_) {
			child->Draw(camera);
		}
	}

	void Details() override {
		Object::Details();

		if (ImGui::CollapsingHeader("Circle", ImGuiTreeNodeFlags_DefaultOpen)) {
			ImGui::DragFloat("Radius", &circleRadius_, 0.5f);
		}

		if (ImGui::CollapsingHeader("Rigidbody", ImGuiTreeNodeFlags_DefaultOpen)) {
			Vec3 tmpVel = rb_.GetVelocity();
			ImGui::DragFloat3("Velocity", &tmpVel.x, 1.0f);
			rb_.SetVelocity(tmpVel);

			ImGui::SameLine();
			if (ImGui::ArrowButton("##VelReset", ImGuiDir_Left)) {
				rb_.SetVelocity(Vec3::zero);
			}

			float tmpMass = rb_.GetMass();
			if (ImGui::DragFloat("Mass", &tmpMass, 0.01f)) {
				rb_.SetMass(tmpMass);
			}
		}
	}

private:
	float circleRadius_ = 32.0f;

	Rigidbody rb_;
	CollisionShapes collisionShapes_;
};
