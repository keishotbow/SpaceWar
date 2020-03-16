#pragma once
#include "Actor.h"

class Ship : public Actor {
public:
	Ship(class Game* game);
	void UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const uint8_t* state);
	
	float GetRightSpeed() const { return mRightSpeed; }
	float GetDownSpeed() const { return mDownSpeed; }
	float GetHP() const { return mHP; }
	float GetAttack() const { return mAttack; }

	void SetHP(float hp) { mHP = hp; }
	void SetAttack(float attack) { mAttack = attack; }

	class CircleComponent* GetCircle() { return mCircle; }

private:
	class CircleComponent* mCircle;

	float mRightSpeed;
	float mDownSpeed;

	float mLaserCooldown;
	float mMaxLaserCooldown;

	float mPLaserCooldown;
	float mMaxPLaserCooldown;

	float mHP;
	float mAttack;
};

