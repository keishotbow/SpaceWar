#pragma once
#include "Laser.h"

class PowerLaser : public Laser {
public:
	PowerLaser(class Game* game);

	bool Init() override;
	void UpdateActor(float deltaTime) override;

};

