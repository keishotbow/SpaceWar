#include "AnimSpriteComponent.h"

AnimSpriteComponent::AnimSpriteComponent(Actor * owner, int drawOrder) 
	: SpriteComponent(owner, drawOrder)
	, mCurrFrame(0.0f)
	, mAnimFPS(24.0f)
{
}

AnimSpriteComponent::~AnimSpriteComponent() {
}

void AnimSpriteComponent::Update(float deltaTime) {
	SpriteComponent::Update(deltaTime);

	if (mAnimTextures.size() > 0) {
		// FPSとデルタタイムに基づいてカレントフレームを更新する
		mCurrFrame += mAnimFPS * deltaTime;

		// 必要に応じてカレントフレームを巻き戻す
		while (mCurrFrame >= mAnimTextures.size()) {
			mCurrFrame -= mAnimTextures.size();
		}

		// 現時点のテクスチャを設定する
		SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
	}
}

void AnimSpriteComponent::SetAnimTextures(const vector<SDL_Texture*>& textures) {
	mAnimTextures = textures;
	if (mAnimTextures.size() > 0) {
		// 最初のフレームをアクティブテクスチャにセットする
		mCurrFrame = 0.0f;
		SetTexture(mAnimTextures[0]);
	}
}
