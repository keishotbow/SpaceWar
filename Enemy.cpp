#include "Enemy.h"
#include "Math.h"
#include "MoveComponent.h"
#include "CircleComponent.h"

Enemy::Enemy(Game * game)
	: Actor(game)
	, mHP(0.0f)
	, mAttack(0.0f)
	, mInvisibleTime(0.0f)
	, mIsInvisible(false)
{
	mMove = new MoveComponent(this);
	mMove->SetForwardSpeed(0.0f);
	mMove->SetAngularSpeed(0.0f);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(0.0f);
}

void Enemy::UpdateActor(float deltaTime) {
}
