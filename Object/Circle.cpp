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
