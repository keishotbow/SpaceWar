#pragma once
#include "SpriteComponent.h"
#include <vector>

using namespace std;

class AnimSpriteComponent : public SpriteComponent {
public:
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
	~AnimSpriteComponent();

	void Update(float deltaTime) override;
	void SetAnimTextures(const vector<SDL_Texture*> & textures);
	
	float GetAnimFPS() const { return mAnimFPS; }
	void SetAnimFPS(float fps) { mAnimFPS = fps; }

private:
	vector<SDL_Texture*> mAnimTextures;
	float mCurrFrame;
	float mAnimFPS;

};

