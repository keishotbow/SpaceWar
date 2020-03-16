#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(Actor * owner, int updateOrder)
	: Component(owner, updateOrder)
	, mForwardSpeed(0.0f)
	, mAngularSpeed(0.0f)
{
}

void MoveComponent::Update(float deltaTime) {
	if (!Math::NearZero(mAngularSpeed)) {
		float rotation = mOwner->GetRotation();
		rotation += mAngularSpeed * deltaTime;
		mOwner->SetRotation(rotation);
	}

	if (!Math::NearZero(mForwardSpeed)) {
		Vector2 pos = mOwner->GetPosition();
		pos += mOwner->GetForward() * mForwardSpeed * deltaTime;
		mOwner->SetPosition(pos);
	}
}
