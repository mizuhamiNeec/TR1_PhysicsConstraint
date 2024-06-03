#include "Object.h"

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

Object::Object(std::string name, std::string tag, const bool active): name_(std::move(name)), tag_(std::move(tag)), active_(active), parent_(nullptr) {}

void Object::Initialize(const std::string& name) {
	name_ = name;
}

void Object::Update() {
	for (auto& child : children_) {
		child->Update();
	}
}

void Object::Draw() {

}

std::string Object::GetName() {
	return name_;
}
