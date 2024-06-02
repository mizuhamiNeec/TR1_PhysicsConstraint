#pragma once
#include <memory>
#include <vector>

#include "Math/Transform.h"

class Object {
public:
	std::vector<std::shared_ptr<Object>> GetChildren();
	void SetParent(const std::shared_ptr<Object>& parentObject);
	Transform GetTransform() const;
	void SetTransform(const Transform& transform);

protected:
	Transform transform_;
	std::shared_ptr<Object> parent_;
	std::vector<std::shared_ptr<Object>> children_;
};
