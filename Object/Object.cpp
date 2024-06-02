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
