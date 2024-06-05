#pragma once
#include <imgui.h>

#include "Camera.h"
#include "Novice.h"
#include "2DPhysics/Rigidbody/Rigidbody.h"
#include "Base/Object.h"

constexpr float deltaTime = 1.0f / 60.0f;

class Circle final : public Object {
public:
	~Circle() override;
	Circle(const std::string& name = "Circle", const std::string& tag = "", bool active = true, float radius = 32.0f);
	void Initialize(const std::string& name) override;

	void Update() override {
		rb_.Update(this, collisionShapes_, deltaTime);
	}

	void Draw(const Camera& camera) override {
		const Vec3 viewpos = camera.WorldToScreen(transform_.position);
		float fixedRadius = circleRadius_ * camera.GetZoom();

		Novice::DrawEllipse(
			static_cast<int>(viewpos.x), static_cast<int>(viewpos.y),
			static_cast<int>(fixedRadius * transform_.scale.x), static_cast<int>(fixedRadius * transform_.scale.y),
			transform_.rotation.z,
			0x000000FF,
			kFillModeSolid
		);

		Vec3 lineEnd = {fixedRadius, 0.0f, 0.0f};

		Novice::DrawLine(
			static_cast<int>(viewpos.x), static_cast<int>(viewpos.y),
			static_cast<int>(viewpos.x + (lineEnd.x * transform_.scale.x * cos(transform_.rotation.z) - lineEnd.y *
				transform_.scale.y * sin(transform_.rotation.z))),
			static_cast<int>(viewpos.y + (lineEnd.x * transform_.scale.x * sin(transform_.rotation.z) + lineEnd.y *
				transform_.scale.y * cos(transform_.rotation.z))),
			RED
		);
	}

	void Details() override {
		Object::Details();

		ImGui::DragFloat("Radius", &circleRadius_, 0.5f);
	}

private:
	float circleRadius_ = 32.0f;

	Rigidbody rb_;
	CollisionShapes collisionShapes_;
};
