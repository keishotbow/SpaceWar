#pragma once
#include "Component.h"
class MoveComponent : public Component {
public:
	MoveComponent(class Actor* owner, int updateOrder=10);

	void Update(float deltaTime) override;
	
	float GetForwardSpeed() const { return mForwardSpeed; }
	float GetAngularSpeed() const { return mAngularSpeed; }

	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }

private:
	float mForwardSpeed;
	float mAngularSpeed;
};

