#include "PowerLaser.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CircleComponent.h"
#include "Game.h"
#include "EnemyBattlePlane.h"

PowerLaser::PowerLaser(Game * game)
	: Laser(game)
{
}

bool PowerLaser::Init() {
	SpriteComponent* laser = new SpriteComponent(this);
	laser->SetTexture(GetGame()->GetTexture("Assets/PowerLaser.png"));

	mMove->SetForwardSpeed(600.0f);
	mMove->SetAngularSpeed(0.0f);
	mCircle->SetRadius(22.0f);

	SetPower(GetPower() * 5.0f);

	return true;
}

void PowerLaser::UpdateActor(float deltaTime) {
	mDeathTimer -= deltaTime;
	if (mDeathTimer <= 0.0f) {
		SetState(State::EDead);
	}
	else {
		// •¨‘Ì‚É“–‚½‚Á‚½Žž‚Ìˆ—
		for (auto ebp : GetGame()->GetEBPs()) {
			if (Intersect(*mCircle, *(ebp->GetCircleComponent()))) {
				// SetState(State::EDead);

				// –³“GŽžŠÔ‚Å‚È‚¢‚È‚ç—^ƒ_ƒ[ƒW
				if (!ebp->GetInvisible()) {
					float remainHP = ebp->GetHP() - GetPower();
					ebp->SetHP(remainHP);
					ebp->SetInvisible(true);
				}
			}
		}
	}
}
