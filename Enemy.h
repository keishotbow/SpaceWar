#pragma once
#include "Actor.h"

class Enemy : public Actor {
public:
	Enemy(class Game* game);
	virtual void UpdateActor(float deltaTime) override;
	
	float GetHP() const { return mHP; }
	float GetAttack() const { return mAttack; }
	float GetInvisibleTime() const { return mInvisibleTime; }
	bool GetInvisible() const { return mIsInvisible; }
	
	void SetHP(float hp) { mHP = hp; }
	void SetAttack(float attack) { mAttack = attack; }
	void SetInvisibleTime(float time) { mInvisibleTime = time; }
	void SetInvisible(bool isInvisible) { mIsInvisible = isInvisible; }
	
	class MoveComponent* GetMoveComponent() { return mMove; }
	class CircleComponent* GetCircleComponent() { return mCircle; }

protected:
	class MoveComponent* mMove;
	class CircleComponent* mCircle;
	float mHP;
	float mAttack;
	vector<float> mAttackCooldowns;
	float mInvisibleTime; // –³“GŽžŠÔ
	bool mIsInvisible; // –³“G‚©‚Ç‚¤‚©
};