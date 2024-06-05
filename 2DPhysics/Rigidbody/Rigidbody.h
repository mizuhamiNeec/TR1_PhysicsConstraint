#pragma once
#include "Config.h"
#include "2DPhysics/CollisionShapes/CollisionShapes.h"
#include "Math/Vec3/Vec3.h"
#include "Object/Base/Object.h"

class Rigidbody {
public:
	void AddForce(const Vec3 newForce) {
		force_ += newForce;
	}

	void Update(Object* object, CollisionShapes shapes, const float deltaTime) {
		shapes;

		AddForce({ 0.0f,-gravity,0.0f });

		Transform parentTransform = object->GetTransform();

		velocity_ += (force_ / mass_) * deltaTime;

		parentTransform.position += velocity_ * deltaTime;

		object->SetTransform(parentTransform);
		force_ = Vec3::zero;
	}

	Vec3 GetVelocity() const {
		return velocity_;
	}

	void SetVelocity(const Vec3 newVel) {
		velocity_ = newVel;
	}

	float GetReboundCoefficient() const {
		return reboundCoefficient_;
	}

	float GetMass() const {
		return mass_;
	}

	void SetMass(float tmpMass) {
		mass_ = tmpMass;
	}

private:
	Vec3 velocity_; // 剛体の速度ベクトル
	float reboundCoefficient_ = 0.5f;
	float mass_ = 1.0f; // 剛体の重量

	Vec3 force_; // 剛体に与えるフォース
};
