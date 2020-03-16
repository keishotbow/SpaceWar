#pragma once
#include <SDL.h>
#include "Component.h"

class SpriteComponent : public Component {
public:
	// 描画順序(drawOrder)が低いほど遠くに置かれる
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);
	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexWidth() const { return mTexWidth; }
	int GetTexHeight() const { return mTexHeight; }

private:
	SDL_Texture* mTexture; // 描画するテクスチャ
	int mDrawOrder; // 画家アルゴリズムで描画する順序

	int mTexWidth;
	int mTexHeight;

};

