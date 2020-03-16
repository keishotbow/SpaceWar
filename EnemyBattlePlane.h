#pragma once
#include "Enemy.h"
#include <vector>

class EnemyBattlePlane : public Enemy {
public:
	EnemyBattlePlane(class Game* game);
	~EnemyBattlePlane();

	void UpdateActor(float deltaTime) override;

private:
	float mAttackInterval; // ���̍U���̒e�̊Ԋu
	int mBulletNum; // ���̍U���Ŏg�p����e��
	vector<class EnemyLaser*> mLasers;
	int mBulletCount;
	float mMaxInvisibleTime;
};