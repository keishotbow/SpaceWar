#include "Laser.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CircleComponent.h"
#include "Game.h"
#include "EnemyBattlePlane.h"

Laser::Laser(Game * game)
	: Actor(game)
	, mDeathTimer(2.0f)
	, mPower(1.0f)
{
	mMove = new MoveComponent(this);
	mCircle = new CircleComponent(this);
}

Laser::~Laser() {
}

bool Laser::Init() {
	SpriteComponent* laser = new SpriteComponent(this);
	laser->SetTexture(GetGame()->GetTexture("Assets/Laser.png"));

	mMove->SetForwardSpeed(800.0f);
	mCircle->SetRadius(11.0f);

	return true;
}

void Laser::UpdateActor(float deltaTime) {
	mDeathTimer -= deltaTime;
	if(mDeathTimer <= 0.0f
		|| GetPosition().x >= static_cast<float>(GetGame()->GetWindowWidth()) ){
		//SDL_Log("mDeathTimer <= 0.0f");
		SetState(State::EDead);
	}
	else {
		// •¨‘Ì‚É“–‚½‚Á‚½Žž‚Ì‹““®‚ð‘‚­
		for (auto enemy : GetGame()->GetEBPs()) {
			if(Intersect(*mCircle, *(enemy->GetCircleComponent()))){
				SetState(State::EDead);
				float remainHP = enemy->GetHP() - GetPower();
				enemy->SetHP(remainHP);
				//SDL_Log("remain HP: %f", enemy->GetHP());
				break;
			}
		}
	}
}

//void Laser::SetForwardSpeed(float speed) {
//	mMove->SetForwardSpeed(speed);
//}
