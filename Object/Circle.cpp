#include "Circle.h"

Circle::~Circle() {
}

Circle::Circle(const std::string& name, const std::string& tag, const bool active, const float radius) {
	name_ = name;
	tag_ = tag;
	active_ = active;
	circleRadius_ = radius;
}

void Circle::Initialize(const std::string& name) {
	Object::Initialize(name);
}

void Circle::ResolveCollision(Circle& other) {
	Vec3 normal = (other.transform_.position - this->transform_.position).Normalized();
	float relativeVelocity = (other.rb_.GetVelocity() - this->rb_.GetVelocity()).DotProduct(normal);

	// 侵入深度を計算
	float distance = (other.transform_.position - this->transform_.position).Length();
	float penetrationDepth = (this->circleRadius_ + other.circleRadius_) - distance;

	// 侵入している場合の位置補正
	if (penetrationDepth > 0) {
		Vec3 correction = normal * (penetrationDepth / (this->rb_.GetMass() + other.rb_.GetMass()));
		this->transform_.position -= correction * (other.rb_.GetMass() / (this->rb_.GetMass() + other.rb_.GetMass()));
		other.transform_.position += correction * (this->rb_.GetMass() / (this->rb_.GetMass() + other.rb_.GetMass()));
	}

	if (relativeVelocity > 0) {
		return;
	}

	float e = min(this->rb_.GetReboundCoefficient(), other.rb_.GetReboundCoefficient());
	float j = -(1 + e) * relativeVelocity;
	j /= 1 / this->rb_.GetMass() + 1 / other.rb_.GetMass();

	Vec3 impulse = normal * j;
	this->rb_.SetVelocity(this->rb_.GetVelocity() - impulse / this->rb_.GetMass());
	other.rb_.SetVelocity(other.rb_.GetVelocity() + impulse / other.rb_.GetMass());
}
