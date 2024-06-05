#pragma once
#include <format>
#include <memory>
#include <string>
#include <vector>
#include "Math/Transform.h"

class Camera;

class Object : public std::enable_shared_from_this<Object> {
public:
	virtual ~Object() = default;
	Object(std::string name = "Object", std::string tag = "", bool active = true);

	virtual void Initialize(const std::string& name);
	virtual void Update();
	virtual void Draw(const Camera& camera);
	virtual void Details();

	std::vector<std::shared_ptr<Object>> GetChildren();
	Transform GetTransform() const;
	void SetTransform(const Transform& transform);
	std::string GetName();

	void SetParent(const std::shared_ptr<Object>& parentObject);

	void AddChild(const std::shared_ptr<Object>& child) {
		child->SetParent(shared_from_this());
		children_.push_back(child);
	}

	void RemoveChild(const std::shared_ptr<Object>& child) {
		std::erase(children_, child);
		child->SetParent(nullptr);
	}

protected:
	Transform transform_;
	std::string name_;
	std::string tag_;
	bool active_;
	std::shared_ptr<Object> parent_;
	std::vector<std::shared_ptr<Object>> children_;

	bool maintainAspectRatio = false;
};
