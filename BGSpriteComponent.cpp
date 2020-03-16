#include "BGSpriteComponent.h"
#include "Actor.h"
#include <SDL.h>

BGSpriteComponent::BGSpriteComponent(Actor * owner, int drawOrder)
	: SpriteComponent(owner, drawOrder)
	, mScrollSpeed(0.0f)
{
}

void BGSpriteComponent::Update(float deltaTime) {
	SpriteComponent::Update(deltaTime);
	for (auto& bg : mBGTextures) {
		// xオフセットを更新する
		bg.mOffset.x += mScrollSpeed * deltaTime;
		// 画面外に出たらオフセットを最後の背景テクスチャの右にリセット
		if (bg.mOffset.x < -mScreenSize.x) {
			bg.mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
		}
	}
}

void BGSpriteComponent::Draw(SDL_Renderer * renderer) {
	// 全背景テクスチャを描画
	for (auto& bg : mBGTextures) {
		SDL_Rect r;
		// スクリーンサイズ領域を推定
		r.w = static_cast<int>(mScreenSize.x);
		r.h = static_cast<int>(mScreenSize.y);
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2 + bg.mOffset.x);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2 + bg.mOffset.y);

		// 背景を描画
		SDL_RenderCopy(renderer, bg.mTexture, nullptr, &r);
	}
}

void BGSpriteComponent::SetBGTextures(const vector<SDL_Texture*>& textures) {
	int count = 0;
	for (auto tex : textures) {
		BGTexture temp;
		temp.mTexture = tex;
		// それぞれのテクスチャは画面幅分のオフセットを持つ
		temp.mOffset.x = count * mScreenSize.x;
		temp.mOffset.y = 0;
		mBGTextures.emplace_back(temp);
		count++;
	}
}
