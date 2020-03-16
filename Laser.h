#pragma once
#include "Actor.h"
class Laser :
	public Actor
{
public:
	Laser(class Game* game);
	~Laser();

	virtual bool Init();

	virtual void UpdateActor(float deltaTime) override;

	virtual float GetPower() const { return mPower; }
	virtual void SetPower(float power) { mPower = power; }

	//void SetForwardSpeed(float speed);

protected:
	class CircleComponent* mCircle;
	class MoveComponent* mMove;
	float mDeathTimer;
	float mPower;

};

