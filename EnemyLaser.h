#pragma once
#include "Laser.h"
class EnemyLaser : public Laser {
public:
	EnemyLaser(class Game* game);

	bool Init() override;
	void UpdateActor(float deltaTime) override;

};

