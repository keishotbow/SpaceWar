#pragma once
#include "Enemy.h"
#include <vector>

class EnemyBattlePlane : public Enemy {
public:
	EnemyBattlePlane(class Game* game);
	~EnemyBattlePlane();

	void UpdateActor(float deltaTime) override;

private:
	float mAttackInterval; // ˆê‰ñ‚ÌUŒ‚‚Ì’e‚ÌŠÔŠu
	int mBulletNum; // ˆê‰ñ‚ÌUŒ‚‚Åg—p‚·‚é’e–ò”
	vector<class EnemyLaser*> mLasers;
	int mBulletCount;
	float mMaxInvisibleTime;
};