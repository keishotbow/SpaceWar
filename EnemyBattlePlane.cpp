#include "EnemyBattlePlane.h"
#include "Game.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "AnimSpriteComponent.h"
#include "CircleComponent.h"
#include "EnemyLaser.h"
#include "Ship.h"
#include "Game.h"
#include <time.h>

EnemyBattlePlane::EnemyBattlePlane(Game * game)
	: Enemy(game)
	, mAttackInterval(0.15f)
	, mBulletNum(5)
	, mBulletCount(0)
	, mMaxInvisibleTime(0.05f)
{
	// 攻撃間隔の設定
	float cumInterval = 0.0f;
	for (int i = 0; i < mBulletNum; i++) {
		cumInterval += mAttackInterval;
		mAttackCooldowns.emplace_back(cumInterval);
	}

	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	vector<SDL_Texture*> anims = {
		GetGame()->GetTexture("Assets/Enemy01.png"),
		GetGame()->GetTexture("Assets/Enemy02.png"),
		GetGame()->GetTexture("Assets/Enemy03.png"),
		GetGame()->GetTexture("Assets/Enemy04.png"),
		GetGame()->GetTexture("Assets/Enemy05.png"),
		GetGame()->GetTexture("Assets/Enemy06.png"),
	};
	asc->SetAnimTextures(anims);
	SetScale(1.2f);
	mCircle->SetRadius(GetScale() * 13.0f);

	//SpriteComponent* sc = new SpriteComponent(this);
	//sc->SetTexture(GetGame()->GetTexture("Assets/enemy.png"));

	// ランダムなy位置から出現
	mMove->SetForwardSpeed(-150.0f);
	srand((unsigned int)time(NULL));
	int random = rand() % 3 + 1;
	if (random == 1) {
		SetPosition(Vector2(1300.0f, GetGame()->GetWindowHeight() * 0.2f));
	}
	else if (random == 2) {
		SetPosition(Vector2(1300.0f, GetGame()->GetWindowHeight() * 0.5f));
	}
	else {
		SetPosition(Vector2(1300.0f, GetGame()->GetWindowHeight() * 0.8f));
	}

	// 初期ステータス設定
	SetHP(100);
	SetAttack(10);
	SetInvisible(false);
	SetInvisibleTime(mMaxInvisibleTime);

	game->AddEBP(this);
}

EnemyBattlePlane::~EnemyBattlePlane() {
	GetGame()->RemoveEBP(this);
}

void EnemyBattlePlane::UpdateActor(float deltaTime) {
	if (GetPosition().x <= -300 || mHP <= 0.0f) {
		SetState(State::EDead);
	}

	// 無敵時間の場合
	if (GetInvisible()) {
		float remainInvisibleTime = GetInvisibleTime() - deltaTime;
		SetInvisibleTime(remainInvisibleTime);
		if (GetInvisibleTime() <= 0.0f) {
			SetInvisible(false);
			SetInvisibleTime(mMaxInvisibleTime);
		}
		else {
			return;
		}
	}

	// プレイヤーの船と衝突したらプレイヤーにダメージ
	Ship* ship = GetGame()->GetShip();
	if (Intersect(*ship->GetCircle(), *mCircle)) {
		ship->SetHP(ship->GetHP() - mAttack);
	}

	// 敵戦闘機の攻撃
	for (auto & coolDown : mAttackCooldowns) {
		coolDown -= deltaTime;
	}
	if (mAttackCooldowns[mBulletCount] <= 0.0f) {
		mLasers.emplace_back(new EnemyLaser(GetGame()));
		Vector2 dir = ship->GetPosition() - GetPosition();
		mLasers[mBulletCount]->Init();
		
		// レーザーがプレイヤーに当たった時のダメージ計算
		float laserPower = mLasers[mBulletCount]->GetPower();
		mLasers[mBulletCount]->SetPower(laserPower * mAttack);

		mLasers[mBulletCount]->SetScale(0.4f);
		mLasers[mBulletCount]->SetPosition(GetPosition());
		mLasers[mBulletCount]->SetRotation(atan2f(dir.y, -dir.x));
		mAttackCooldowns[mBulletCount] = 2.0f;
		mBulletCount++;
		if (mBulletCount >= mBulletNum) {
			mBulletCount = 0;
			mLasers.clear();
			float cumInterval = 0.0f;
			for (int i = 0; i < mBulletNum; i++) {
				cumInterval += mAttackInterval;
				mAttackCooldowns.emplace_back(cumInterval);
			}
		}
	}
}
