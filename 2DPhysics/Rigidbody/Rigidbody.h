#pragma once
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

		Transform parentTransform = object->GetTransform();

		velocity_ += (force_ / mass_) * deltaTime;

		parentTransform.position += velocity_ * deltaTime;

		object->SetTransform(parentTransform);
		force_ = Vec3::zero;
	}

	void SetVelocity(const Vec3 newVelocity) {
		velocity_ = newVelocity;
	}

private:
	Vec3 velocity_; // 剛体の速度ベクトル
	float mass_ = 1.0f; // 剛体の重量

	Vec3 force_; // 剛体に与えるフォース
};
