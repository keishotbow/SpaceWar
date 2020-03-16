#pragma once
#include "SpriteComponent.h"
#include "Math.h"
#include <vector>

using namespace std;

class BGSpriteComponent : public SpriteComponent {
public:
	// 背景なので優先的に描画
	BGSpriteComponent(class Actor* owner, int drawOrder = 10);
	// 更新と描画は親からオーバーライド
	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;
	// 背景用のテクスチャをセットする
	void SetBGTextures(const vector<SDL_Texture*>& textures);
	// 画面サイズとスクロール速度の設定と取得
	void SetScreenSize(const Vector2& size) { mScreenSize = size; }
	void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
	float GetScrollSpeed() const { return mScrollSpeed; }

private:
	// 個々の背景画像とオフセットをカプセル化する構造体
	struct BGTexture {
		SDL_Texture* mTexture;
		Vector2 mOffset;
	};

	vector<BGTexture> mBGTextures;
	Vector2 mScreenSize;
	float mScrollSpeed;
};

