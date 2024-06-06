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
		float radiusSum = this->circleRadius_ * this->transform_.scale.x + other.circleRadius_ * other.transform_.scale.
				x;
		return distance < radiusSum;
	}

	Circle(const std::string& name = "Circle", const std::string& tag = "", bool active = true, float radius = 32.0f);
	void Initialize(const std::string& name) override;

	void ResolveCollision(Circle& other);

	void Update() override {
		if (isStatic) {
			rb_.SetVelocity({0.0f, 0.0f, 0.0f});
		} else {
			rb_.Update(this, collisionShapes_, deltaTime);
			ApplyDistanceConstraint();

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
			}
		}

		for (auto& child : children_) {
			child->Update();
		}
	}

	void Draw(const Camera& camera) override {
		const Vec3 viewpos = camera.WorldToScreen(transform_.position);
		const Vec3 viewVel = camera.WorldToScreen(transform_.position + rb_.GetVelocity());
		float fixedRadius = circleRadius_ * camera.GetZoom();

		if (viewport.IsOverlappingCircle({viewpos.x, viewpos.y}, fixedRadius)) {
			Novice::DrawEllipse(
				static_cast<int>(viewpos.x), static_cast<int>(viewpos.y),
				static_cast<int>(fixedRadius * transform_.scale.x), static_cast<int>(fixedRadius * transform_.scale.y),
				transform_.rotation.z,
				0x000000FF,
				kFillModeWireFrame
			);

			Vec3 lineEnd = {fixedRadius, 0.0f, 0.0f};

			if (bDrawDebug) {
				Novice::DrawLine(
					static_cast<int>(viewpos.x), static_cast<int>(viewpos.y),
					static_cast<int>(viewpos.x + (lineEnd.x * transform_.scale.x * cos(transform_.rotation.z) - lineEnd.
						y *
						transform_.scale.y * sin(transform_.rotation.z))),
					static_cast<int>(viewpos.y + (lineEnd.x * transform_.scale.x * sin(transform_.rotation.z) + lineEnd.
						y *
						transform_.scale.y * cos(transform_.rotation.z))),
					RED
				);
			}
		}

		if (bDrawDebug) {
			DrawLine(viewpos, viewVel, 0xFFFF00FF);

			for (auto& child : children_) {
				DrawLine(viewpos, camera.WorldToScreen(child->GetTransform().position), 0x00FF00FF);
			}
		}

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
			if (ImGui::Checkbox("IsStatic", &isStatic)) {
			}

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

		if (ImGui::CollapsingHeader("Distance Constraint", ImGuiTreeNodeFlags_DefaultOpen)) {
			if (ImGui::DragFloat("MaxDistance", &maxDistanceToParent_, 0.1f)) {
			}

			if (ImGui::DragFloat("ReductionFactor", &reductionFactor, 0.001f)) {
			}
		}
	}

	Rigidbody GetRigidbody() const {
		return rb_;
	}

	bool GetStatic() const {
		return isStatic;
	}

	void ApplyDistanceConstraint() {
		if (parent_) {
			if (auto p = dynamic_cast<Circle*>(parent_.get())) {
				Vec3 direction = transform_.position - parent_->GetTransform().position;
				float currentDistance = direction.Length();
				if (currentDistance > maxDistanceToParent_) {
					Vec3 normal = direction.Normalized();
					Vec3 correction = normal * (currentDistance - maxDistanceToParent_);
					transform_.position -= correction * 0.5f;

					if (!p->GetStatic()) {
						parent_->SetTransform(
							{
								{parent_->GetTransform().position + correction * 0.5f},
								parent_->GetTransform().rotation,
								parent_->GetTransform().scale
							}
						);
					}
				}
				if (currentDistance > 0.0f) {
					// Avoid division by zero
					Vec3 relativeVelocity = rb_.GetVelocity() - p->GetRigidbody().GetVelocity();
					Vec3 velocityAlongNormal = direction.Normalized() * relativeVelocity.DotProduct(
						direction.Normalized());
					rb_.SetVelocity(rb_.GetVelocity() - velocityAlongNormal * reductionFactor);
					p->GetRigidbody().SetVelocity(
						p->GetRigidbody().GetVelocity() + velocityAlongNormal * reductionFactor);
				}
			}
		}
	}

private:
	float circleRadius_ = 32.0f;

	Rigidbody rb_;
	CollisionShapes collisionShapes_;

	float maxDistanceToParent_ = 0.0f;

	bool isStatic = false;
};
