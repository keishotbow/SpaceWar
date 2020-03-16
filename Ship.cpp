#include "Ship.h"
#include "AnimSpriteComponent.h"
#include "Game.h"
#include "Laser.h"
#include "PowerLaser.h"
#include "MoveComponent.h"
#include "EnemyLaser.h"
#include "CircleComponent.h"

Ship::Ship(Game * game)
	: Actor(game)
	, mRightSpeed(0.0f)
	, mDownSpeed(0.0f)
	, mLaserCooldown(0.0f)
	, mMaxLaserCooldown(0.1f)
	, mPLaserCooldown(0.0f)
	, mMaxPLaserCooldown(1.0f)
	, mHP(100.0f)
	, mAttack(10.0f)
{
	// アニムスプライトコンポーネントを作成
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/Ship01.png"),
		game->GetTexture("Assets/Ship02.png"),
		game->GetTexture("Assets/Ship03.png"),
		game->GetTexture("Assets/Ship04.png"),
	};
	// アニムスプライトコンポーネントを設定
	asc->SetAnimTextures(anims);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(20.0f);
}

void Ship::UpdateActor(float deltaTime) {
	// プレイヤーの船が撃破されたら終了
	if (mHP <= 0.0f) {
		SetState(State::EDead);
	}

	if (GetState() == State::EDead) {
		GetGame()->TerminateGame();
	}

	Actor::UpdateActor(deltaTime);
	// スピードとデルタタイムに基づいて位置を更新
	Vector2 pos = GetPosition();
	pos.x += mRightSpeed * deltaTime;
	pos.y += mDownSpeed * deltaTime;
	// スクリーンの左半分までに位置制限
	if (pos.x < 25.0f) {
		pos.x = 25.0f;
	}
	else if (pos.x > 500.0f) {
		pos.x = 500.0f;
	}
	else if (pos.y < 25.0f) {
		pos.y = 25.0f;
	}
	else if (pos.y > 743.0f) {
		pos.y = 743.0f;
	}
	// 位置をセット
	SetPosition(pos);

	mLaserCooldown -= deltaTime;
	mPLaserCooldown -= deltaTime;
}

void Ship::ProcessKeyboard(const uint8_t * state) {
	mRightSpeed = 0.0f;
	mDownSpeed = 0.0f;
	// 右or左
	if (state[SDL_SCANCODE_D]) {
		mRightSpeed += 250.0f;
	}
	if (state[SDL_SCANCODE_A]) {
		mRightSpeed -= 250.0f;
	}
	// 上or下
	if (state[SDL_SCANCODE_W]) {
		mDownSpeed -= 300.0f * 1.5f;
	}
	if (state[SDL_SCANCODE_S]) {
		mDownSpeed += 300.0f * 1.5f;
	}

	// レーザー攻撃
	if (mLaserCooldown <= 0.0f && state[SDL_SCANCODE_SPACE]) {
		Laser* laser = new Laser(GetGame());
		laser->Init();
		// レーザーのパワー×自機の攻撃力
		float power = laser->GetPower() * mAttack;
		laser->SetPower(power);
		laser->SetPosition(GetPosition() + Vector2(45.0f, 0.0f));
		
		mLaserCooldown = mMaxLaserCooldown;
	}

	// パワーレーザー攻撃
	if (mPLaserCooldown <= 0.0f && state[SDL_SCANCODE_B]) {
		PowerLaser* plaser = new PowerLaser(GetGame());
		plaser->Init();
		// パワーレーザーのパワー×自機の攻撃力
		float power = plaser->GetPower() * mAttack;
		plaser->SetPower(power);
		plaser->SetScale(2.0f);
		plaser->SetPosition(GetPosition() + Vector2(100.0f, 0.0f));
		plaser->SetRotation(GetRotation());
		
		mPLaserCooldown = mMaxPLaserCooldown;
	}
}
