#include "EnemyLaser.h"
#include "AnimSpriteComponent.h"
#include "CircleComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include <vector>
#include <SDL.h>
#include "Ship.h"

using namespace std;

EnemyLaser::EnemyLaser(class Game* game)
	: Laser(game)
{
	SetPower(1.0f);
}

bool EnemyLaser::Init() {
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	vector<SDL_Texture*> anims = {
		GetGame()->GetTexture("Assets/beam01.png"),
		GetGame()->GetTexture("Assets/beam02.png"),
		GetGame()->GetTexture("Assets/beam03.png")
	};
	asc->SetAnimTextures(anims);

	mMove->SetForwardSpeed(-500.0f);
	mMove->SetAngularSpeed(0.0f);
	mCircle->SetRadius(11.0f);

	return true;
}

void EnemyLaser::UpdateActor(float deltaTime) {
	float w = static_cast<float>(GetGame()->GetWindowWidth());
	float h = static_cast<float>(GetGame()->GetWindowHeight());
	Vector2 pos = GetPosition();
	if (pos.x <= 0.0f || pos.x >= w
		|| pos.y >= h || pos.y <= 0.0f) {
		SetState(State::EDead);
	}

	Ship* ship = GetGame()->GetShip();
	if (Intersect(*mCircle, *ship->GetCircle())) {
		ship->SetHP(ship->GetHP() - mPower);
		SetState(State::EDead);
	}
}
